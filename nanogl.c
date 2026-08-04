/*
Copyright (C) 2007-2009 Olli Hinkka

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#define LOG_TAG "nanoGL"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <cutils/log.h>

#include "nanogl.h"
#include "glesinterface.h"
#include "gl.h"
#include "nanogl_private.h"

#define DEBUG_NANO 0

#ifdef __ANDROID__
	#include <android/log.h>
	#define LOG __android_log_print
	#define LOGI( ... ) __android_log_print( ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__ )
	#define LOGD( ... ) if( DEBUG_NANO ) \
		__android_log_print( ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__ )
	#define LOGE( ... ) __android_log_print( ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__ )
	#define LOGW( ... ) __android_log_print( ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__ )
#elif !defined( _MSC_VER )
	#define LOGI( ... )		     \
		printf( "I: " __VA_ARGS__ ); \
		printf( "\n" )
	#define LOGD( ... )			     \
		if( DEBUG_NANO )		     \
		{				     \
			printf( "D: " __VA_ARGS__ ); \
			printf( "\n" );		     \
		}
	#define LOGE( ... )		     \
		printf( "E: " __VA_ARGS__ ); \
		printf( "\n" )
	#define LOGW( ... )		     \
		printf( "W: " __VA_ARGS__ ); \
		printf( "\n" )
#else
	#define LOGI printf
	#define LOGD printf
	#define LOGE printf
	#define LOGW printf
#endif

#ifdef _WIN32
	#include <windows.h>
	#define loadDriver( x )     LoadLibraryA( x )
	#define procAddress( x, y ) ((void *) GetProcAddress((HINSTANCE)x, y ))
	#define freeDriver( x )     FreeLibrary((HINSTANCE)x )
	#define GL_LIB   "opengl32.dll"
	#define GLES_LIB "GLESv1_CM.dll"
	#define EGL_LIB  "EGL.dll"
#else
	#include <dlfcn.h>
	#define loadDriver( x )     dlopen( x, RTLD_NOW | RTLD_LOCAL )
	#define procAddress( x, y ) dlsym( x, y )
	#define freeDriver( x )     dlclose( x )
	#define GL_LIB   "libGL.so.1"
	#define GLES_LIB "libGLESv1_CM.so"
	#define EGL_LIB  "libEGL.so"
#endif

static char const *const gl_names[] = {
#include "funcnames.h"
NULL };

GlESInterface *glEsImpl = NULL;

char *nano_extensions_string = NULL;

#ifdef WIN32
static void APIENTRY gl_unimplemented( GLenum none )
{
#ifndef USE_CORE_PROFILE
	LOGE( "Called unimplemented OpenGL ES API\n" );
#endif
}

#else // make glGetString not crash
static const char *APIENTRY gl_unimplemented( GLenum none )
{
#ifndef USE_CORE_PROFILE
	LOGE( "Called unimplemented OpenGL ES API\n" );
#endif
	return "";
}
#endif

// defined by the consumer application
void *GL_GetProcAddress( const char *name );

int nanoGL_Init( void )
{
	// load GL API calls
	char const *const *api = gl_names;
	int count = 0;

	// alloc space
	if( !glEsImpl )
		glEsImpl = malloc( sizeof( GlESInterface ));
	memset( glEsImpl, 0, sizeof( GlESInterface ));

	// nanoGL interface pointer
	void **ptr = (void **)( glEsImpl );

	while( *api )
	{
		void *f;

		f = GL_GetProcAddress( *api );

#ifdef USE_CORE_PROFILE
		// Hack: try ARB and EXT suffix
		if( f == NULL )
		{
			char namearb[256];
			snprintf( namearb, 256, "%sARB", *api );
			f = GL_GetProcAddress( namearb );
		}
		if( f == NULL )
		{
			char namearb[256];
			snprintf( namearb, 256, "%sEXT", *api );
			f = GL_GetProcAddress( namearb );
		}
#endif

		if( f == NULL )
		{
			LOGW( "<%s> not found.", *api );
			f = (void *)gl_unimplemented;
		}
		else
		{
			LOGD( "<%s> @ 0x%p\n", *api, f );
			count++;
		}

		*ptr++ = f;
		api++;
	}

	InitGLStructs();

	free( nano_extensions_string );
	nano_extensions_string = NULL;

	// just a lazy sanity check
	if( count < 10 )
		return 0;

	const char *ext = (const char *)glEsImpl->glGetString( GL_EXTENSIONS );
	const char *add = "GL_ARB_multitexture EXT_texture_env_add";

	if( !ext )
		ext = "";

	size_t extlen = strlen( ext );
	size_t addlen = strlen( add );
	size_t len = extlen + addlen + 2;

	nano_extensions_string = malloc( len );
	if( !nano_extensions_string )
		return 0;

	strcpy( nano_extensions_string, ext );
	nano_extensions_string[extlen] = ' ';
	strcpy( &nano_extensions_string[extlen+1], add );

	// it has loaded something, maybe it will work
	return 1;
}

void nanoGL_Destroy( void )
{
	LOGD( "nanoGL_Destroy" );
	free( glEsImpl );
	glEsImpl = NULL;
	free( nano_extensions_string );
	nano_extensions_string = NULL;
}
