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

#ifdef SOFTFP_LINK
#define S __attribute__((pcs("aapcs")))
#else
#define S
#endif

struct GlESInterface
    {

    int (*eglChooseConfig) (int dpy, const int *attrib_list, int *configs, int config_size, int *num_config) S;
	int (*eglCopyBuffers) (int dpy, int surface, void* target) S;
    int (*eglCreateContext) (int dpy, int config, int share_list, const int *attrib_list) S;
    int (*eglCreatePbufferSurface) (int dpy, int config, const int *attrib_list) S;
    int (*eglCreatePixmapSurface) (int dpy, int config, void* pixmap, const int *attrib_list) S;
    int (*eglCreateWindowSurface) (int dpy, int config, void* window, const int *attrib_list) S;
    int (*eglDestroyContext) (int dpy, int ctx) S;
    int (*eglDestroySurface) (int dpy, int surface) S;
    int (*eglGetConfigAttrib) (int dpy, int config, int attribute, int *value) S;
    int (*eglGetConfigs) (int dpy, int *configs, int config_size, int *num_config) S;
    int (*eglGetCurrentContext) (void) S;
    int (*eglGetCurrentDisplay) (void) S;
    int (*eglGetCurrentSurface) (int readdraw) S;
    int (*eglGetDisplay) (int display) S;
    int (*eglGetError) (void) S;

    void (*(*eglGetProcAddress) (const char *procname))(...) S;

    int (*eglInitialize) (int dpy, int *major, int *minor) S;
    int (*eglMakeCurrent) (int dpy, int draw, int read, int ctx) S;
    int (*eglQueryContext) (int dpy, int ctx, int attribute, int *value) S;
    const char * (*eglQueryString) (int dpy, int name) S;
    int (*eglQuerySurface) (int dpy, int surface, int attribute, int *value) S;
    int (*eglSwapBuffers) (int dpy, int draw) S;
    int (*eglTerminate) (int dpy) S;
    int (*eglWaitGL) (void) S;
    int (*eglWaitNative) (int engine) S;
    void (*glActiveTexture) (unsigned int texture) S;
    void (*glAlphaFunc) (unsigned int func, float ref) S;
    void (*glAlphaFuncx) (unsigned int func, int ref) S;
    void (*glBindTexture) (unsigned int target, unsigned int texture) S;
    void (*glBlendFunc) (unsigned int sfactor, unsigned int dfactor) S;
    void (*glClear) (unsigned int mask) S;
    void (*glClearColor) (float red, float green, float blue, float alpha) S;
    void (*glClearColorx) (int red, int green, int blue, int alpha) S;
    void (*glClearDepthf) (float depth) S;
    void (*glClearDepthx) (int depth) S;
    void (*glClearStencil) (int s) S;
    void (*glClientActiveTexture) (unsigned int texture) S;
    void (*glColor4f) (float red, float green, float blue, float alpha) S;
    void (*glColor4x) (int red, int green, int blue, int alpha) S;
    void (*glColorMask) (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) S;
    void (*glColorPointer) (int size, unsigned int type, int stride, const void *pointer) S;
	void (*glCompressedTexImage2D) (unsigned int target, int level, unsigned int internalformat, int width, int height, int border, int imageSize, const void *data) S;
	void (*glCompressedTexSubImage2D) (unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void *data) S;
	void (*glCopyTexImage2D) (unsigned int target, int level, unsigned int internalformat, int x, int y, int width, int height, int border) S;
	void (*glCopyTexSubImage2D) (unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) S;
	void (*glCullFace) (unsigned int mode) S;
    void (*glDeleteTextures) (int n, const unsigned int *textures) S;
    void (*glDepthFunc) (unsigned int func) S;
    void (*glDepthMask) (unsigned char flag) S;
    void (*glDepthRangef) (float zNear, float zFar) S;
    void (*glDepthRangex) (int zNear, int zFar) S;
    void (*glDisable) (unsigned int cap) S;
    void (*glDisableClientState) (unsigned int array) S;
    void (*glDrawArrays) (unsigned int mode, int first, int count) S;
    void (*glDrawElements) (unsigned int mode, int count, unsigned int type, const void *indices) S;
    void (*glEnable) (unsigned int cap) S;
    void (*glEnableClientState) (unsigned int array) S;
    void (*glFinish) (void) S;
    void (*glFlush) (void) S;
    void (*glFogf) (unsigned int pname, float param) S;
	void (*glFogfv) (unsigned int pname, const float *params) S;
    void (*glFogx) (unsigned int pname, int param) S;
    void (*glFogxv) (unsigned int pname, const int *params) S;
    void (*glFrontFace) (unsigned int mode) S;
    void (*glFrustumf) (float left, float right, float bottom, float top, float zNear, float zFar) S;
	void (*glFrustumx) (int left, int right, int bottom, int top, int zNear, int zFar) S;
    void (*glGenTextures) (int n, unsigned int *textures) S;
    unsigned int (*glGetError) (void) S;
	void (*glGetIntegerv) (unsigned int pname, int *params) S;
    const unsigned char * (*glGetString) (unsigned int name) S;
    void (*glHint) (unsigned int target, unsigned int mode) S;
	void (*glLightModelf) (unsigned int pname, float param) S;
    void (*glLightModelfv) (unsigned int pname, const float *params) S;
    void (*glLightModelx) (unsigned int pname, int param) S;
    void (*glLightModelxv) (unsigned int pname, const int *params) S;
    void (*glLightf) (unsigned int light, unsigned int pname, float param) S;
    void (*glLightfv) (unsigned int light, unsigned int pname, const float *params) S;
    void (*glLightx) (unsigned int light, unsigned int pname, int param) S;
    void (*glLightxv) (unsigned int light, unsigned int pname, const int *params) S;
    void (*glLineWidth) (float width) S;
    void (*glLineWidthx) (int width) S;
    void (*glLoadIdentity) (void) S;
    void (*glLoadMatrixf) (const float *m) S;
    void (*glLoadMatrixx) (const int *m) S;
    void (*glLogicOp) (unsigned int opcode) S;
    void (*glMaterialf) (unsigned int face, unsigned int pname, float param) S;
    void (*glMaterialfv) (unsigned int face, unsigned int pname, const float *params) S;
    void (*glMaterialx) (unsigned int face, unsigned int pname, int param) S;
    void (*glMaterialxv) (unsigned int face, unsigned int pname, const int *params) S;
    void (*glMatrixMode) (unsigned int mode) S;
    void (*glMultMatrixf) (const float *m) S;
    void (*glMultMatrixx) (const int *m) S;
    void (*glMultiTexCoord4f) (unsigned int target, float s, float t, float r, float q) S;
    void (*glMultiTexCoord4x) (unsigned int target, int s, int t, int r, int q) S;
    void (*glNormal3f) (float nx, float ny, float nz) S;
    void (*glNormal3x) (int nx, int ny, int nz) S;
    void (*glNormalPointer) (unsigned int type, int stride, const void *pointer) S;
    void (*glOrthof) (float left, float right, float bottom, float top, float zNear, float zFar) S;
    void (*glOrthox) (int left, int right, int bottom, int top, int zNear, int zFar) S;
    void (*glPixelStorei) (unsigned int pname, int param) S;
    void (*glPointSize) (float size) S;
    void (*glPointSizex) (int size) S;
    void (*glPolygonOffset) (float factor, float units) S;
    void (*glPolygonOffsetx) (int factor, int units) S;
    void (*glPopMatrix) (void) S;
    void (*glPushMatrix) (void) S;
    unsigned int (*glQueryMatrixxOES) (int mantissa[16], int exponent[16]) S;
    void (*glReadPixels) (int x, int y, int width, int height, unsigned int format, unsigned int type, void *pixels) S;
    void (*glRotatef) (float angle, float x, float y, float z) S;
    void (*glRotatex) (int angle, int x, int y, int z) S;
    void (*glSampleCoverage) (float value, unsigned char invert) S;
    void (*glSampleCoveragex) (int value, unsigned char invert) S;
    void (*glScalef) (float x, float y, float z) S;
    void (*glScalex) (int x, int y, int z) S;
    void (*glScissor) (int x, int y, int width, int height) S;
    void (*glShadeModel) (unsigned int mode) S;
    void (*glStencilFunc) (unsigned int func, int ref, unsigned int mask) S;
    void (*glStencilMask) (unsigned int mask) S;
    void (*glStencilOp) (unsigned int fail, unsigned int zfail, unsigned int zpass) S;
    void (*glTexCoordPointer) (int size, unsigned int type, int stride, const void *pointer) S;
    void (*glTexEnvf) (unsigned int target, unsigned int pname, float param) S;
    void (*glTexEnvfv) (unsigned int target, unsigned int pname, const float *params) S;
    void (*glTexEnvx) (unsigned int target, unsigned int pname, int param) S;
    void (*glTexEnvxv) (unsigned int target, unsigned int pname, const int *params) S;
    void (*glTexImage2D) (unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels) S;
    void (*glTexParameterf) (unsigned int target, unsigned int pname, float param) S;
    void (*glTexParameterx) (unsigned int target, unsigned int pname, int param) S;
    void (*glTexSubImage2D) (unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void *pixels) S;
    void (*glTranslatef) (float x, float y, float z) S;
    void (*glTranslatex) (int x, int y, int z) S;
    void (*glVertexPointer) (int size, unsigned int type, int stride, const void *pointer) S;
    void (*glViewport) (int x, int y, int width, int height) S;
    int (*eglSwapInterval) (int dpy, int interval) S;
    void (*glBindBuffer) (unsigned int target, unsigned int buffer) S;
    void (*glBufferData) (unsigned int target, int size, const void *data, unsigned int usage) S;
    void (*glBufferSubData) (unsigned int target, int offset,int size, const void *data) S;
    void (*glClipPlanef) (unsigned int plane, const float *equation) S;
    void (*glClipPlanex) (unsigned int plane, const int *equation) S;
    void (*glColor4ub) (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) S;
    void (*glDeleteBuffers) (int n, const unsigned int *buffers) S;
    void (*glGenBuffers) (int n, unsigned int *buffers) S;
    void (*glGetBooleanv) (unsigned int pname, unsigned char *params) S;
    void (*glGetBufferParameteriv) (unsigned int target, unsigned int pname, int *params) S;
    void (*glGetClipPlanef) (unsigned int pname, float eqn[4]) S;
    void (*glGetClipPlanex) (unsigned int pname, int eqn[4]) S;
    void (*glGetFixedv) (unsigned int pname, int *params) S;
    void (*glGetFloatv) (unsigned int pname, float *params) S;
    void (*glGetLightfv) (unsigned int light, unsigned int pname, float *params) S;
    void (*glGetLightxv) (unsigned int light, unsigned int pname, int *params) S;
    void (*glGetMaterialfv) (unsigned int face, unsigned int pname, float *params) S;
    void (*glGetMaterialxv) (unsigned int face, unsigned int pname, int *params) S;
    void (*glGetPointerv) (unsigned int pname, void **params) S;
    void (*glGetTexEnvfv) (unsigned int env, unsigned int pname, float *params) S;
    void (*glGetTexEnviv) (unsigned int env, unsigned int pname, int *params) S;
    void (*glGetTexEnvxv) (unsigned int env, unsigned int pname, int *params) S;
    void (*glGetTexParameterfv) (unsigned int target, unsigned int pname, float *params) S;
    void (*glGetTexParameteriv) (unsigned int target, unsigned int pname, int *params) S;
    void (*glGetTexParameterxv) (unsigned int target, unsigned int pname, int *params) S;
    unsigned char (*glIsBuffer) (unsigned int buffer) S;
    unsigned char (*glIsEnabled) (unsigned int cap) S;
    unsigned char (*glIsTexture) (unsigned int texture) S;
    void (*glPointParameterf) (unsigned int pname, float param) S;
    void (*glPointParameterfv) (unsigned int pname, const float *params) S;
    void (*glPointParameterx) (unsigned int pname, int param) S;
    void (*glPointParameterxv) (unsigned int pname, const int *params) S;
    void (*glPointSizePointerOES) (unsigned int type, int stride, const void *pointer) S;
    void (*glTexEnvi) (unsigned int target, unsigned int pname, int param) S;
    void (*glTexEnviv) (unsigned int target, unsigned int pname, const int *params) S;
    void (*glTexParameterfv) (unsigned int target, unsigned int pname, const float *params) S;
    void (*glTexParameteri) (unsigned int target, unsigned int pname, int param) S;
    void (*glTexParameteriv) (unsigned int target, unsigned int pname, const int *params) S;
    void (*glTexParameterxv) (unsigned int target, unsigned int pname, const int *params) S;

    int (*eglBindTexImage) (int dpy, int surface, int buffer) S;
    int (*eglReleaseTexImage) (int dpy, int surface, int buffer) S;
    int (*eglSurfaceAttrib) (int dpy, int surface, int attribute, int value) S;

    };
#if !defined (__WINS__)
    #if	defined(__TARGET_FPU_VFP)
        #pragma no_softfp_linkage
    #endif
#endif


#endif
