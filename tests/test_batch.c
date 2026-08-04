#include <stdio.h>
#include <string.h>
#include "gl.h"
#include "glesinterface.h"
#include "nanogl.h"

#define MAX_DRAWS 8
#define MAX_INDICES 64

static struct
{
	GLenum mode;
	GLsizei count;
	GLushort indices[MAX_INDICES];
} draws[MAX_DRAWS];
static int numdraws;

static void APIENTRY StubNop( void )
{
}

static const GLubyte *APIENTRY StubGetString( GLenum name )
{
	return (const GLubyte *)"GL_IMG_ray_tracing"; // PowerVR Wizard might've died but it still lives in our hearts
}

static void APIENTRY StubDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid *indices )
{
	if( numdraws >= MAX_DRAWS || count > MAX_INDICES || type != GL_UNSIGNED_SHORT )
	{
		numdraws = MAX_DRAWS + 1;
		return;
	}
	draws[numdraws].mode = mode;
	draws[numdraws].count = count;
	memcpy( draws[numdraws].indices, indices, count * sizeof( GLushort ));
	numdraws++;
}

void *GL_GetProcAddress( const char *name )
{
	if( !strcmp( name, "glDrawElements" ))
		return (void *)StubDrawElements;
	if( !strcmp( name, "glGetString" ))
		return (void *)StubGetString;
	return (void *)StubNop;
}

static int CheckDraw( int draw, GLenum mode, GLsizei count, const GLushort *expect )
{
	if( draw >= numdraws )
		return 1;
	if( draws[draw].mode != mode || draws[draw].count != count )
		return 1;
	if( memcmp( draws[draw].indices, expect, count * sizeof( GLushort )))
		return 1;
	return 0;
}

static void EmitVertices( int n )
{
	for( int i = 0; i < n; i++ )
		pglVertex3f( (GLfloat)i, 0.0f, 0.0f );
}

static int Test_ExtensionsString( void )
{
	const char *ext = (const char *)pglGetString( GL_EXTENSIONS );

	if( !strstr( ext, "GL_IMG_ray_tracing" ) || !strstr( ext, "GL_ARB_multitexture" ))
		return 1;
	return 0;
}

static int Test_TwoQuads( void )
{
	static const GLushort expect[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7};

	numdraws = 0;
	pglBegin( GL_QUADS );
	EmitVertices( 8 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 1 )
		return 1;
	return CheckDraw( 0, GL_TRIANGLES, 12, expect );
}

static int Test_Lines( void )
{
	static const GLushort expect[] = {0, 1, 2, 3};

	numdraws = 0;
	pglBegin( GL_LINES );
	EmitVertices( 4 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 1 )
		return 1;
	return CheckDraw( 0, GL_LINES, 4, expect );
}

static int Test_LineStrip( void )
{
	static const GLushort expect[] = {0, 1, 1, 2, 2, 3};

	numdraws = 0;
	pglBegin( GL_LINE_STRIP );
	EmitVertices( 4 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 1 )
		return 1;
	return CheckDraw( 0, GL_LINES, 6, expect );
}

static int Test_LineLoop( void )
{
	static const GLushort expect[] = {0, 1, 1, 2, 2, 0};

	numdraws = 0;
	pglBegin( GL_LINE_LOOP );
	EmitVertices( 3 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 1 )
		return 1;
	return CheckDraw( 0, GL_LINES, 6, expect );
}

static int Test_ClassChangeFlush( void )
{
	static const GLushort expectquad[] = {0, 1, 2, 0, 2, 3};
	static const GLushort expectline[] = {0, 1};

	numdraws = 0;
	pglBegin( GL_QUADS );
	EmitVertices( 4 );
	pglEnd();
	pglBegin( GL_LINES );
	EmitVertices( 2 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 2 )
		return 1;
	return CheckDraw( 0, GL_TRIANGLES, 6, expectquad ) | CheckDraw( 1, GL_LINES, 2, expectline );
}

static int Test_OddLinesVertexDropped( void )
{
	static const GLushort expect[] = {0, 1, 2, 3};

	numdraws = 0;
	pglBegin( GL_LINES );
	EmitVertices( 3 );
	pglEnd();
	pglBegin( GL_LINES );
	EmitVertices( 2 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 1 )
		return 1;
	return CheckDraw( 0, GL_LINES, 4, expect );
}

static int Test_Points( void )
{
	static const GLushort expect[] = {0, 1, 2};

	numdraws = 0;
	pglBegin( GL_POINTS );
	EmitVertices( 3 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 1 )
		return 1;
	return CheckDraw( 0, GL_POINTS, 3, expect );
}

static int Test_UnsupportedBlockDiscarded( void )
{
	static const GLushort expect[] = {0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7};

	numdraws = 0;
	pglBegin( GL_QUADS );
	EmitVertices( 4 );
	pglEnd();
	pglBegin( GL_QUAD_STRIP );
	EmitVertices( 4 );
	pglEnd();
	pglBegin( GL_QUADS );
	EmitVertices( 4 );
	pglEnd();
	nanoGL_Flush();

	if( numdraws != 1 )
		return 1;
	return CheckDraw( 0, GL_TRIANGLES, 12, expect );
}

#define RUN_TEST( fn ) do { if( fn()) { printf( "FAIL: " #fn "\n" ); ret++; } } while( 0 )

int main( void )
{
	int ret = 0;

	if( !nanoGL_Init())
	{
		printf( "FAIL: nanoGL_Init\n" );
		return 1;
	}

	RUN_TEST( Test_ExtensionsString );
	RUN_TEST( Test_TwoQuads );
	RUN_TEST( Test_Lines );
	RUN_TEST( Test_LineStrip );
	RUN_TEST( Test_LineLoop );
	RUN_TEST( Test_ClassChangeFlush );
	RUN_TEST( Test_OddLinesVertexDropped );
	RUN_TEST( Test_Points );
	RUN_TEST( Test_UnsupportedBlockDiscarded );

	nanoGL_Destroy();

	return ret;
}
