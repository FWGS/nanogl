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

#ifndef __GLESINTERFACE_H__
#define __GLESINTERFACE_H__


#if !defined (__WINS__)
    #if	defined(__TARGET_FPU_VFP)
        #pragma softfp_linkage
    #endif
#endif
struct GlESInterface
    {

    int (*eglChooseConfig) (int dpy, const int *attrib_list, int *configs, int config_size, int *num_config);
	int (*eglCopyBuffers) (int dpy, int surface, void* target);
    int (*eglCreateContext) (int dpy, int config, int share_list, const int *attrib_list);
    int (*eglCreatePbufferSurface) (int dpy, int config, const int *attrib_list);
    int (*eglCreatePixmapSurface) (int dpy, int config, void* pixmap, const int *attrib_list);
    int (*eglCreateWindowSurface) (int dpy, int config, void* window, const int *attrib_list);
    int (*eglDestroyContext) (int dpy, int ctx);
    int (*eglDestroySurface) (int dpy, int surface);
    int (*eglGetConfigAttrib) (int dpy, int config, int attribute, int *value);
    int (*eglGetConfigs) (int dpy, int *configs, int config_size, int *num_config);
    int (*eglGetCurrentContext) (void);
    int (*eglGetCurrentDisplay) (void);
    int (*eglGetCurrentSurface) (int readdraw);
    int (*eglGetDisplay) (int display);
    int (*eglGetError) (void);

    void (*(*eglGetProcAddress) (const char *procname))(...);

    int (*eglInitialize) (int dpy, int *major, int *minor);
    int (*eglMakeCurrent) (int dpy, int draw, int read, int ctx);
    int (*eglQueryContext) (int dpy, int ctx, int attribute, int *value);
    const char * (*eglQueryString) (int dpy, int name);
    int (*eglQuerySurface) (int dpy, int surface, int attribute, int *value);
    int (*eglSwapBuffers) (int dpy, int draw);
    int (*eglTerminate) (int dpy);
    int (*eglWaitGL) (void);
    int (*eglWaitNative) (int engine);	

    void (*glActiveTexture) (unsigned int texture);
    void (*glAlphaFunc) (unsigned int func, float ref);
    void (*glAlphaFuncx) (unsigned int func, int ref);
    void (*glBindTexture) (unsigned int target, unsigned int texture);
    void (*glBlendFunc) (unsigned int sfactor, unsigned int dfactor);
    void (*glClear) (unsigned int mask);
    void (*glClearColor) (float red, float green, float blue, float alpha);
    void (*glClearColorx) (int red, int green, int blue, int alpha);
    void (*glClearDepthf) (float depth);
    void (*glClearDepthx) (int depth);
    void (*glClearStencil) (int s);
    void (*glClientActiveTexture) (unsigned int texture);
    void (*glColor4f) (float red, float green, float blue, float alpha);
    void (*glColor4x) (int red, int green, int blue, int alpha);    
    void (*glColorMask) (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
    void (*glColorPointer) (int size, unsigned int type, int stride, const void *pointer);
	void (*glCompressedTexImage2D) (unsigned int target, int level, unsigned int internalformat, int width, int height, int border, int imageSize, const void *data);
	void (*glCompressedTexSubImage2D) (unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void *data);
	void (*glCopyTexImage2D) (unsigned int target, int level, unsigned int internalformat, int x, int y, int width, int height, int border);
	void (*glCopyTexSubImage2D) (unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height);
	void (*glCullFace) (unsigned int mode);
    void (*glDeleteTextures) (int n, const unsigned int *textures);
    void (*glDepthFunc) (unsigned int func);
    void (*glDepthMask) (unsigned char flag);
    void (*glDepthRangef) (float zNear, float zFar);
    void (*glDepthRangex) (int zNear, int zFar);
    void (*glDisable) (unsigned int cap);
    void (*glDisableClientState) (unsigned int array);
    void (*glDrawArrays) (unsigned int mode, int first, int count);
    void (*glDrawElements) (unsigned int mode, int count, unsigned int type, const void *indices);
    void (*glEnable) (unsigned int cap);
    void (*glEnableClientState) (unsigned int array);
    void (*glFinish) (void);
    void (*glFlush) (void);
    void (*glFogf) (unsigned int pname, float param);
   	void (*glFogfv) (unsigned int pname, const float *params);
    void (*glFogx) (unsigned int pname, int param);
    void (*glFogxv) (unsigned int pname, const int *params);
    void (*glFrontFace) (unsigned int mode);
    void (*glFrustumf) (float left, float right, float bottom, float top, float zNear, float zFar);
	void (*glFrustumx) (int left, int right, int bottom, int top, int zNear, int zFar);
    void (*glGenTextures) (int n, unsigned int *textures);
    unsigned int (*glGetError) (void);
   	void (*glGetIntegerv) (unsigned int pname, int *params);
    const unsigned char * (*glGetString) (unsigned int name);
    void (*glHint) (unsigned int target, unsigned int mode);
	void (*glLightModelf) (unsigned int pname, float param);
    void (*glLightModelfv) (unsigned int pname, const float *params);
    void (*glLightModelx) (unsigned int pname, int param);
    void (*glLightModelxv) (unsigned int pname, const int *params);
    void (*glLightf) (unsigned int light, unsigned int pname, float param);
    void (*glLightfv) (unsigned int light, unsigned int pname, const float *params);
    void (*glLightx) (unsigned int light, unsigned int pname, int param);
    void (*glLightxv) (unsigned int light, unsigned int pname, const int *params);
    void (*glLineWidth) (float width);
    void (*glLineWidthx) (int width);
    void (*glLoadIdentity) (void);
    void (*glLoadMatrixf) (const float *m);
    void (*glLoadMatrixx) (const int *m);
    void (*glLogicOp) (unsigned int opcode);
    void (*glMaterialf) (unsigned int face, unsigned int pname, float param);     
    void (*glMaterialfv) (unsigned int face, unsigned int pname, const float *params);
    void (*glMaterialx) (unsigned int face, unsigned int pname, int param);
    void (*glMaterialxv) (unsigned int face, unsigned int pname, const int *params);
    void (*glMatrixMode) (unsigned int mode);
    void (*glMultMatrixf) (const float *m);
    void (*glMultMatrixx) (const int *m);
    void (*glMultiTexCoord4f) (unsigned int target, float s, float t, float r, float q);  
    void (*glMultiTexCoord4x) (unsigned int target, int s, int t, int r, int q);
    void (*glNormal3f) (float nx, float ny, float nz);
    void (*glNormal3x) (int nx, int ny, int nz);
    void (*glNormalPointer) (unsigned int type, int stride, const void *pointer);
    void (*glOrthof) (float left, float right, float bottom, float top, float zNear, float zFar);
    void (*glOrthox) (int left, int right, int bottom, int top, int zNear, int zFar);
    void (*glPixelStorei) (unsigned int pname, int param);
    void (*glPointSize) (float size);
    void (*glPointSizex) (int size);
    void (*glPolygonOffset) (float factor, float units);
    void (*glPolygonOffsetx) (int factor, int units);
    void (*glPopMatrix) (void);
    void (*glPushMatrix) (void);
    unsigned int (*glQueryMatrixxOES) (int mantissa[16], int exponent[16]);
    void (*glReadPixels) (int x, int y, int width, int height, unsigned int format, unsigned int type, void *pixels);
    void (*glRotatef) (float angle, float x, float y, float z);
    void (*glRotatex) (int angle, int x, int y, int z);
    void (*glSampleCoverage) (float value, unsigned char invert);
    void (*glSampleCoveragex) (int value, unsigned char invert);
    void (*glScalef) (float x, float y, float z);
    void (*glScalex) (int x, int y, int z);
    void (*glScissor) (int x, int y, int width, int height);
    void (*glShadeModel) (unsigned int mode);
    void (*glStencilFunc) (unsigned int func, int ref, unsigned int mask);
    void (*glStencilMask) (unsigned int mask);
    void (*glStencilOp) (unsigned int fail, unsigned int zfail, unsigned int zpass);
    void (*glTexCoordPointer) (int size, unsigned int type, int stride, const void *pointer);
    void (*glTexEnvf) (unsigned int target, unsigned int pname, float param);
    void (*glTexEnvfv) (unsigned int target, unsigned int pname, const float *params);
    void (*glTexEnvx) (unsigned int target, unsigned int pname, int param);
    void (*glTexEnvxv) (unsigned int target, unsigned int pname, const int *params);
    void (*glTexImage2D) (unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels);
    void (*glTexParameterf) (unsigned int target, unsigned int pname, float param);
    void (*glTexParameterx) (unsigned int target, unsigned int pname, int param);
    void (*glTexSubImage2D) (unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void *pixels);
    void (*glTranslatef) (float x, float y, float z);
    void (*glTranslatex) (int x, int y, int z);
    void (*glVertexPointer) (int size, unsigned int type, int stride, const void *pointer);
    void (*glViewport) (int x, int y, int width, int height);
    int (*eglSwapInterval) (int dpy, int interval);
    void (*glBindBuffer) (unsigned int target, unsigned int buffer);
    void (*glBufferData) (unsigned int target, int size, const void *data, unsigned int usage);
    void (*glBufferSubData) (unsigned int target, int offset,int size, const void *data);
    void (*glClipPlanef) (unsigned int plane, const float *equation);
    void (*glClipPlanex) (unsigned int plane, const int *equation);
    void (*glColor4ub) (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
    void (*glDeleteBuffers) (int n, const unsigned int *buffers);
    void (*glGenBuffers) (int n, unsigned int *buffers);
    void (*glGetBooleanv) (unsigned int pname, unsigned char *params);
    void (*glGetBufferParameteriv) (unsigned int target, unsigned int pname, int *params);
    void (*glGetClipPlanef) (unsigned int pname, float eqn[4]);
    void (*glGetClipPlanex) (unsigned int pname, int eqn[4]);
    void (*glGetFixedv) (unsigned int pname, int *params);
    void (*glGetFloatv) (unsigned int pname, float *params);
    void (*glGetLightfv) (unsigned int light, unsigned int pname, float *params);
    void (*glGetLightxv) (unsigned int light, unsigned int pname, int *params);
    void (*glGetMaterialfv) (unsigned int face, unsigned int pname, float *params);
    void (*glGetMaterialxv) (unsigned int face, unsigned int pname, int *params);
    void (*glGetPointerv) (unsigned int pname, void **params);
    void (*glGetTexEnvfv) (unsigned int env, unsigned int pname, float *params);
    void (*glGetTexEnviv) (unsigned int env, unsigned int pname, int *params);
    void (*glGetTexEnvxv) (unsigned int env, unsigned int pname, int *params);	
    void (*glGetTexParameterfv) (unsigned int target, unsigned int pname, float *params);
    void (*glGetTexParameteriv) (unsigned int target, unsigned int pname, int *params);
    void (*glGetTexParameterxv) (unsigned int target, unsigned int pname, int *params);
    unsigned char (*glIsBuffer) (unsigned int buffer);
    unsigned char (*glIsEnabled) (unsigned int cap);
    unsigned char (*glIsTexture) (unsigned int texture);
    void (*glPointParameterf) (unsigned int pname, float param);
    void (*glPointParameterfv) (unsigned int pname, const float *params);	
    void (*glPointParameterx) (unsigned int pname, int param);
    void (*glPointParameterxv) (unsigned int pname, const int *params);
    void (*glPointSizePointerOES) (unsigned int type, int stride, const void *pointer);
    void (*glTexEnvi) (unsigned int target, unsigned int pname, int param);
    void (*glTexEnviv) (unsigned int target, unsigned int pname, const int *params);
    void (*glTexParameterfv) (unsigned int target, unsigned int pname, const float *params);
    void (*glTexParameteri) (unsigned int target, unsigned int pname, int param);
    void (*glTexParameteriv) (unsigned int target, unsigned int pname, const int *params);
    void (*glTexParameterxv) (unsigned int target, unsigned int pname, const int *params);

    int (*eglBindTexImage) (int dpy, int surface, int buffer);
    int (*eglReleaseTexImage) (int dpy, int surface, int buffer);
    int (*eglSurfaceAttrib) (int dpy, int surface, int attribute, int value);

    };
#if !defined (__WINS__)
    #if	defined(__TARGET_FPU_VFP)
        #pragma no_softfp_linkage
    #endif
#endif


#endif
