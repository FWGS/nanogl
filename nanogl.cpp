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
#include <dlfcn.h>

//#include <cutils/log.h>
#include <android/log.h>

#include "nanogl.h"
#include "glesinterface.h"
#include "gl.h"

#define LOG __android_log_print
#define DEBUG_NANO 0

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) if (DEBUG_NANO) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG,__VA_ARGS__)

#define GL_ENTRY(_r, _api, ...) #_api,

static char const * const gl_names[] = {
    #include "gl_entries.in"
    NULL
};

//const char * driver;

static void* glesLib = NULL;

GlESInterface* glEsImpl = NULL;

extern void InitGLStructs();

static void gl_unimplemented() { 
	LOGE ("Called unimplemented OpenGL ES API\n"); 
}


static int CreateGlEsInterface( const char * name, void * lib, void * lib1, void * default_func )
{
	// alloc space
	if ( !glEsImpl )
		glEsImpl = (GlESInterface *) malloc(sizeof(GlESInterface)); 

	if (!glEsImpl) {
        return 0;
    }

	// load GL API calls
	char const * const * api;
	api = gl_names;

	// nanoGL interface pointer
	void ** ptr = (void **)(glEsImpl);

	while (*api) 
	{
		void * f;
		
		f = dlsym(lib, *api); // ltry ibGLESxx_CM.so

		if (f == NULL) {
			LOGW( "<%s> not found in %s. Trying libEGL.so.", *api, name); //driver);
			
			// try lib1
			if ( lib1 ) {
				f = dlsym(lib1, *api); // libEGL.so
				
				if ( f == NULL ) {
					LOGE ( "<%s> not found in libEGL.so", *api);
					f = default_func; //(void*)gl_unimplemented;
				}
				else {
					LOGD ("<%s> @ 0x%p\n", *api, f);
				}
			}
			else 
				f = default_func;
		}
		else {
			LOGD ("<%s> @ 0x%p\n", *api, f);
		}
			
	    *ptr++ = f;
        api++;
    }

	return 1;
}

// Load using the dynamic loader
static int loadDriver(const char * name) {
	glesLib = dlopen(name, RTLD_NOW | RTLD_LOCAL);
	int rc = (glesLib) ? 1 : 0;
	return rc;
}

/**
 * Init
 */
int nanoGL_Init()
{
	const char * lib1 = "libGLESv1_CM.so"; 	// Has both gl* & egl* funcs SDK < 1.5
	const char * lib2 = "libGLESv2.so"; 	// Only gl* funcs SDK >= 1.5
	const char * lib3 = "libEGL.so"; 		// Only egl* funcs SDK >= 1.5
	const char * driver;
	
	// load lib
	LOGI("nanoGL: Init loading driver %s\n", lib1);
	//LOG (ANDROID_LOG_DEBUG, LOG_TAG, "nanoGL: Init loading driver %s\n", lib1);

	if ( ! loadDriver(lib1) ) 
	{
		LOGE("Failed to load driver %s. Trying %s\n", lib1, lib2);

		if ( ! loadDriver(lib2) ) {
			LOGE ("Failed to load  %s.\n", lib2);
			return 0;
		}
		else
			driver = lib2;
	}
	else
		driver = lib1;

	void * eglLib;
	
	//if ( strcmp(driver, lib2) == 0 ) {
		LOGD ("**** Will Load EGL subs from %s ****", lib3);
		
		eglLib = dlopen(lib3, RTLD_NOW | RTLD_LOCAL);
		
		if ( ! eglLib ) {
			LOGE ( "Failed to load %s", lib3);
		}
	//}
	
	// Load API gl* for 1.5+  else egl* gl* 
	//if (CreateGlEsInterface(driver, glesLib, eglLib, NULL) == -1)
	if ( !CreateGlEsInterface(driver, glesLib, eglLib, (void *) gl_unimplemented) == -1)
    {
		// release lib
		LOGE ( "CreateGlEsInterface failed.");

		dlclose(glesLib);
	    return 0;
    }

	// Init nanoGL
	InitGLStructs();
	return 1;
}

void nanoGL_Destroy()
{
	LOGD ("nanoGL_Destroy");
	
	if (glEsImpl) {
        free( glEsImpl); 
        glEsImpl = NULL;
    }
	
	// release lib
	dlclose(glesLib);
}
    
