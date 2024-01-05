/**
 * SPDX-License-Identifier: (WTFPL OR CC0-1.0) AND Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/wgl.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif



int GLAD_WGL_VERSION_1_0 = 0;
int GLAD_WGL_ARB_buffer_region = 0;
int GLAD_WGL_ARB_context_flush_control = 0;
int GLAD_WGL_ARB_create_context = 0;
int GLAD_WGL_ARB_create_context_no_error = 0;
int GLAD_WGL_ARB_create_context_profile = 0;
int GLAD_WGL_ARB_create_context_robustness = 0;
int GLAD_WGL_ARB_extensions_string = 0;
int GLAD_WGL_ARB_framebuffer_sRGB = 0;
int GLAD_WGL_ARB_make_current_read = 0;
int GLAD_WGL_ARB_multisample = 0;
int GLAD_WGL_ARB_pbuffer = 0;
int GLAD_WGL_ARB_pixel_format = 0;
int GLAD_WGL_ARB_pixel_format_float = 0;
int GLAD_WGL_ARB_render_texture = 0;
int GLAD_WGL_ARB_robustness_application_isolation = 0;
int GLAD_WGL_ARB_robustness_share_group_isolation = 0;
int GLAD_WGL_ATI_render_texture_rectangle = 0;
int GLAD_WGL_EXT_colorspace = 0;
int GLAD_WGL_EXT_create_context_es2_profile = 0;
int GLAD_WGL_EXT_create_context_es_profile = 0;
int GLAD_WGL_EXT_depth_float = 0;
int GLAD_WGL_EXT_display_color_table = 0;
int GLAD_WGL_EXT_extensions_string = 0;
int GLAD_WGL_EXT_framebuffer_sRGB = 0;
int GLAD_WGL_EXT_make_current_read = 0;
int GLAD_WGL_EXT_multisample = 0;
int GLAD_WGL_EXT_pbuffer = 0;
int GLAD_WGL_EXT_pixel_format = 0;
int GLAD_WGL_EXT_pixel_format_packed_float = 0;
int GLAD_WGL_EXT_swap_control = 0;
int GLAD_WGL_EXT_swap_control_tear = 0;
int GLAD_WGL_NV_multigpu_context = 0;
int GLAD_WGL_NV_render_depth_texture = 0;
int GLAD_WGL_NV_render_texture_rectangle = 0;



PFNWGLBINDDISPLAYCOLORTABLEEXTPROC glad_wglBindDisplayColorTableEXT = NULL;
PFNWGLBINDTEXIMAGEARBPROC glad_wglBindTexImageARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC glad_wglChoosePixelFormatARB = NULL;
PFNWGLCHOOSEPIXELFORMATEXTPROC glad_wglChoosePixelFormatEXT = NULL;
PFNWGLCREATEBUFFERREGIONARBPROC glad_wglCreateBufferRegionARB = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC glad_wglCreateContextAttribsARB = NULL;
PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC glad_wglCreateDisplayColorTableEXT = NULL;
PFNWGLCREATEPBUFFERARBPROC glad_wglCreatePbufferARB = NULL;
PFNWGLCREATEPBUFFEREXTPROC glad_wglCreatePbufferEXT = NULL;
PFNWGLDELETEBUFFERREGIONARBPROC glad_wglDeleteBufferRegionARB = NULL;
PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC glad_wglDestroyDisplayColorTableEXT = NULL;
PFNWGLDESTROYPBUFFERARBPROC glad_wglDestroyPbufferARB = NULL;
PFNWGLDESTROYPBUFFEREXTPROC glad_wglDestroyPbufferEXT = NULL;
PFNWGLGETCURRENTREADDCARBPROC glad_wglGetCurrentReadDCARB = NULL;
PFNWGLGETCURRENTREADDCEXTPROC glad_wglGetCurrentReadDCEXT = NULL;
PFNWGLGETEXTENSIONSSTRINGARBPROC glad_wglGetExtensionsStringARB = NULL;
PFNWGLGETEXTENSIONSSTRINGEXTPROC glad_wglGetExtensionsStringEXT = NULL;
PFNWGLGETPBUFFERDCARBPROC glad_wglGetPbufferDCARB = NULL;
PFNWGLGETPBUFFERDCEXTPROC glad_wglGetPbufferDCEXT = NULL;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC glad_wglGetPixelFormatAttribfvARB = NULL;
PFNWGLGETPIXELFORMATATTRIBFVEXTPROC glad_wglGetPixelFormatAttribfvEXT = NULL;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC glad_wglGetPixelFormatAttribivARB = NULL;
PFNWGLGETPIXELFORMATATTRIBIVEXTPROC glad_wglGetPixelFormatAttribivEXT = NULL;
PFNWGLGETSWAPINTERVALEXTPROC glad_wglGetSwapIntervalEXT = NULL;
PFNWGLLOADDISPLAYCOLORTABLEEXTPROC glad_wglLoadDisplayColorTableEXT = NULL;
PFNWGLMAKECONTEXTCURRENTARBPROC glad_wglMakeContextCurrentARB = NULL;
PFNWGLMAKECONTEXTCURRENTEXTPROC glad_wglMakeContextCurrentEXT = NULL;
PFNWGLQUERYPBUFFERARBPROC glad_wglQueryPbufferARB = NULL;
PFNWGLQUERYPBUFFEREXTPROC glad_wglQueryPbufferEXT = NULL;
PFNWGLRELEASEPBUFFERDCARBPROC glad_wglReleasePbufferDCARB = NULL;
PFNWGLRELEASEPBUFFERDCEXTPROC glad_wglReleasePbufferDCEXT = NULL;
PFNWGLRELEASETEXIMAGEARBPROC glad_wglReleaseTexImageARB = NULL;
PFNWGLRESTOREBUFFERREGIONARBPROC glad_wglRestoreBufferRegionARB = NULL;
PFNWGLSAVEBUFFERREGIONARBPROC glad_wglSaveBufferRegionARB = NULL;
PFNWGLSETPBUFFERATTRIBARBPROC glad_wglSetPbufferAttribARB = NULL;
PFNWGLSWAPINTERVALEXTPROC glad_wglSwapIntervalEXT = NULL;


static void glad_wgl_load_WGL_ARB_buffer_region(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_ARB_buffer_region) return;
    glad_wglCreateBufferRegionARB = (PFNWGLCREATEBUFFERREGIONARBPROC) load(userptr, "wglCreateBufferRegionARB");
    glad_wglDeleteBufferRegionARB = (PFNWGLDELETEBUFFERREGIONARBPROC) load(userptr, "wglDeleteBufferRegionARB");
    glad_wglRestoreBufferRegionARB = (PFNWGLRESTOREBUFFERREGIONARBPROC) load(userptr, "wglRestoreBufferRegionARB");
    glad_wglSaveBufferRegionARB = (PFNWGLSAVEBUFFERREGIONARBPROC) load(userptr, "wglSaveBufferRegionARB");
}
static void glad_wgl_load_WGL_ARB_create_context(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_ARB_create_context) return;
    glad_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) load(userptr, "wglCreateContextAttribsARB");
}
static void glad_wgl_load_WGL_ARB_extensions_string(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_ARB_extensions_string) return;
    glad_wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) load(userptr, "wglGetExtensionsStringARB");
}
static void glad_wgl_load_WGL_ARB_make_current_read(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_ARB_make_current_read) return;
    glad_wglGetCurrentReadDCARB = (PFNWGLGETCURRENTREADDCARBPROC) load(userptr, "wglGetCurrentReadDCARB");
    glad_wglMakeContextCurrentARB = (PFNWGLMAKECONTEXTCURRENTARBPROC) load(userptr, "wglMakeContextCurrentARB");
}
static void glad_wgl_load_WGL_ARB_pbuffer(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_ARB_pbuffer) return;
    glad_wglCreatePbufferARB = (PFNWGLCREATEPBUFFERARBPROC) load(userptr, "wglCreatePbufferARB");
    glad_wglDestroyPbufferARB = (PFNWGLDESTROYPBUFFERARBPROC) load(userptr, "wglDestroyPbufferARB");
    glad_wglGetPbufferDCARB = (PFNWGLGETPBUFFERDCARBPROC) load(userptr, "wglGetPbufferDCARB");
    glad_wglQueryPbufferARB = (PFNWGLQUERYPBUFFERARBPROC) load(userptr, "wglQueryPbufferARB");
    glad_wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC) load(userptr, "wglReleasePbufferDCARB");
}
static void glad_wgl_load_WGL_ARB_pixel_format(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_ARB_pixel_format) return;
    glad_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) load(userptr, "wglChoosePixelFormatARB");
    glad_wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC) load(userptr, "wglGetPixelFormatAttribfvARB");
    glad_wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC) load(userptr, "wglGetPixelFormatAttribivARB");
}
static void glad_wgl_load_WGL_ARB_render_texture(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_ARB_render_texture) return;
    glad_wglBindTexImageARB = (PFNWGLBINDTEXIMAGEARBPROC) load(userptr, "wglBindTexImageARB");
    glad_wglReleaseTexImageARB = (PFNWGLRELEASETEXIMAGEARBPROC) load(userptr, "wglReleaseTexImageARB");
    glad_wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC) load(userptr, "wglSetPbufferAttribARB");
}
static void glad_wgl_load_WGL_EXT_display_color_table(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_EXT_display_color_table) return;
    glad_wglBindDisplayColorTableEXT = (PFNWGLBINDDISPLAYCOLORTABLEEXTPROC) load(userptr, "wglBindDisplayColorTableEXT");
    glad_wglCreateDisplayColorTableEXT = (PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC) load(userptr, "wglCreateDisplayColorTableEXT");
    glad_wglDestroyDisplayColorTableEXT = (PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC) load(userptr, "wglDestroyDisplayColorTableEXT");
    glad_wglLoadDisplayColorTableEXT = (PFNWGLLOADDISPLAYCOLORTABLEEXTPROC) load(userptr, "wglLoadDisplayColorTableEXT");
}
static void glad_wgl_load_WGL_EXT_extensions_string(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_EXT_extensions_string) return;
    glad_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) load(userptr, "wglGetExtensionsStringEXT");
}
static void glad_wgl_load_WGL_EXT_make_current_read(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_EXT_make_current_read) return;
    glad_wglGetCurrentReadDCEXT = (PFNWGLGETCURRENTREADDCEXTPROC) load(userptr, "wglGetCurrentReadDCEXT");
    glad_wglMakeContextCurrentEXT = (PFNWGLMAKECONTEXTCURRENTEXTPROC) load(userptr, "wglMakeContextCurrentEXT");
}
static void glad_wgl_load_WGL_EXT_pbuffer(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_EXT_pbuffer) return;
    glad_wglCreatePbufferEXT = (PFNWGLCREATEPBUFFEREXTPROC) load(userptr, "wglCreatePbufferEXT");
    glad_wglDestroyPbufferEXT = (PFNWGLDESTROYPBUFFEREXTPROC) load(userptr, "wglDestroyPbufferEXT");
    glad_wglGetPbufferDCEXT = (PFNWGLGETPBUFFERDCEXTPROC) load(userptr, "wglGetPbufferDCEXT");
    glad_wglQueryPbufferEXT = (PFNWGLQUERYPBUFFEREXTPROC) load(userptr, "wglQueryPbufferEXT");
    glad_wglReleasePbufferDCEXT = (PFNWGLRELEASEPBUFFERDCEXTPROC) load(userptr, "wglReleasePbufferDCEXT");
}
static void glad_wgl_load_WGL_EXT_pixel_format(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_EXT_pixel_format) return;
    glad_wglChoosePixelFormatEXT = (PFNWGLCHOOSEPIXELFORMATEXTPROC) load(userptr, "wglChoosePixelFormatEXT");
    glad_wglGetPixelFormatAttribfvEXT = (PFNWGLGETPIXELFORMATATTRIBFVEXTPROC) load(userptr, "wglGetPixelFormatAttribfvEXT");
    glad_wglGetPixelFormatAttribivEXT = (PFNWGLGETPIXELFORMATATTRIBIVEXTPROC) load(userptr, "wglGetPixelFormatAttribivEXT");
}
static void glad_wgl_load_WGL_EXT_swap_control(GLADuserptrloadfunc load, void *userptr) {
    if(!GLAD_WGL_EXT_swap_control) return;
    glad_wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC) load(userptr, "wglGetSwapIntervalEXT");
    glad_wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) load(userptr, "wglSwapIntervalEXT");
}



static int glad_wgl_has_extension(HDC hdc, const char *ext) {
    const char *terminator;
    const char *loc;
    const char *extensions;

    if(wglGetExtensionsStringEXT == NULL && wglGetExtensionsStringARB == NULL)
        return 0;

    if(wglGetExtensionsStringARB == NULL || hdc == INVALID_HANDLE_VALUE)
        extensions = wglGetExtensionsStringEXT();
    else
        extensions = wglGetExtensionsStringARB(hdc);

    if(extensions == NULL || ext == NULL)
        return 0;

    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL)
            break;

        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0'))
        {
            return 1;
        }
        extensions = terminator;
    }

    return 0;
}

static GLADapiproc glad_wgl_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_wgl_find_extensions_wgl(HDC hdc) {
    GLAD_WGL_ARB_buffer_region = glad_wgl_has_extension(hdc, "WGL_ARB_buffer_region");
    GLAD_WGL_ARB_context_flush_control = glad_wgl_has_extension(hdc, "WGL_ARB_context_flush_control");
    GLAD_WGL_ARB_create_context = glad_wgl_has_extension(hdc, "WGL_ARB_create_context");
    GLAD_WGL_ARB_create_context_no_error = glad_wgl_has_extension(hdc, "WGL_ARB_create_context_no_error");
    GLAD_WGL_ARB_create_context_profile = glad_wgl_has_extension(hdc, "WGL_ARB_create_context_profile");
    GLAD_WGL_ARB_create_context_robustness = glad_wgl_has_extension(hdc, "WGL_ARB_create_context_robustness");
    GLAD_WGL_ARB_extensions_string = glad_wgl_has_extension(hdc, "WGL_ARB_extensions_string");
    GLAD_WGL_ARB_framebuffer_sRGB = glad_wgl_has_extension(hdc, "WGL_ARB_framebuffer_sRGB");
    GLAD_WGL_ARB_make_current_read = glad_wgl_has_extension(hdc, "WGL_ARB_make_current_read");
    GLAD_WGL_ARB_multisample = glad_wgl_has_extension(hdc, "WGL_ARB_multisample");
    GLAD_WGL_ARB_pbuffer = glad_wgl_has_extension(hdc, "WGL_ARB_pbuffer");
    GLAD_WGL_ARB_pixel_format = glad_wgl_has_extension(hdc, "WGL_ARB_pixel_format");
    GLAD_WGL_ARB_pixel_format_float = glad_wgl_has_extension(hdc, "WGL_ARB_pixel_format_float");
    GLAD_WGL_ARB_render_texture = glad_wgl_has_extension(hdc, "WGL_ARB_render_texture");
    GLAD_WGL_ARB_robustness_application_isolation = glad_wgl_has_extension(hdc, "WGL_ARB_robustness_application_isolation");
    GLAD_WGL_ARB_robustness_share_group_isolation = glad_wgl_has_extension(hdc, "WGL_ARB_robustness_share_group_isolation");
    GLAD_WGL_ATI_render_texture_rectangle = glad_wgl_has_extension(hdc, "WGL_ATI_render_texture_rectangle");
    GLAD_WGL_EXT_colorspace = glad_wgl_has_extension(hdc, "WGL_EXT_colorspace");
    GLAD_WGL_EXT_create_context_es2_profile = glad_wgl_has_extension(hdc, "WGL_EXT_create_context_es2_profile");
    GLAD_WGL_EXT_create_context_es_profile = glad_wgl_has_extension(hdc, "WGL_EXT_create_context_es_profile");
    GLAD_WGL_EXT_depth_float = glad_wgl_has_extension(hdc, "WGL_EXT_depth_float");
    GLAD_WGL_EXT_display_color_table = glad_wgl_has_extension(hdc, "WGL_EXT_display_color_table");
    GLAD_WGL_EXT_extensions_string = glad_wgl_has_extension(hdc, "WGL_EXT_extensions_string");
    GLAD_WGL_EXT_framebuffer_sRGB = glad_wgl_has_extension(hdc, "WGL_EXT_framebuffer_sRGB");
    GLAD_WGL_EXT_make_current_read = glad_wgl_has_extension(hdc, "WGL_EXT_make_current_read");
    GLAD_WGL_EXT_multisample = glad_wgl_has_extension(hdc, "WGL_EXT_multisample");
    GLAD_WGL_EXT_pbuffer = glad_wgl_has_extension(hdc, "WGL_EXT_pbuffer");
    GLAD_WGL_EXT_pixel_format = glad_wgl_has_extension(hdc, "WGL_EXT_pixel_format");
    GLAD_WGL_EXT_pixel_format_packed_float = glad_wgl_has_extension(hdc, "WGL_EXT_pixel_format_packed_float");
    GLAD_WGL_EXT_swap_control = glad_wgl_has_extension(hdc, "WGL_EXT_swap_control");
    GLAD_WGL_EXT_swap_control_tear = glad_wgl_has_extension(hdc, "WGL_EXT_swap_control_tear");
    GLAD_WGL_NV_multigpu_context = glad_wgl_has_extension(hdc, "WGL_NV_multigpu_context");
    GLAD_WGL_NV_render_depth_texture = glad_wgl_has_extension(hdc, "WGL_NV_render_depth_texture");
    GLAD_WGL_NV_render_texture_rectangle = glad_wgl_has_extension(hdc, "WGL_NV_render_texture_rectangle");
    return 1;
}

static int glad_wgl_find_core_wgl(void) {
    int major = 1, minor = 0;
    GLAD_WGL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadWGLUserPtr(HDC hdc, GLADuserptrloadfunc load, void *userptr) {
    int version;
    wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) load(userptr, "wglGetExtensionsStringARB");
    wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC) load(userptr, "wglGetExtensionsStringEXT");
    if(wglGetExtensionsStringARB == NULL && wglGetExtensionsStringEXT == NULL) return 0;
    version = glad_wgl_find_core_wgl();


    if (!glad_wgl_find_extensions_wgl(hdc)) return 0;
    glad_wgl_load_WGL_ARB_buffer_region(load, userptr);
    glad_wgl_load_WGL_ARB_create_context(load, userptr);
    glad_wgl_load_WGL_ARB_extensions_string(load, userptr);
    glad_wgl_load_WGL_ARB_make_current_read(load, userptr);
    glad_wgl_load_WGL_ARB_pbuffer(load, userptr);
    glad_wgl_load_WGL_ARB_pixel_format(load, userptr);
    glad_wgl_load_WGL_ARB_render_texture(load, userptr);
    glad_wgl_load_WGL_EXT_display_color_table(load, userptr);
    glad_wgl_load_WGL_EXT_extensions_string(load, userptr);
    glad_wgl_load_WGL_EXT_make_current_read(load, userptr);
    glad_wgl_load_WGL_EXT_pbuffer(load, userptr);
    glad_wgl_load_WGL_EXT_pixel_format(load, userptr);
    glad_wgl_load_WGL_EXT_swap_control(load, userptr);


    return version;
}

int gladLoadWGL(HDC hdc, GLADloadfunc load) {
    return gladLoadWGLUserPtr(hdc, glad_wgl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}
 


#ifdef __cplusplus
}
#endif
