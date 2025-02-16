#include "screen_capture.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

LembangStatus screen_capture_init(ScreenCapture *capture) {
    capture->display = XOpenDisplay(NULL);
    if (!capture->display) {
        return LEMBANG_ERROR_INIT;
    }

    capture->root = DefaultRootWindow(capture->display);
    XWindowAttributes attributes;
    XGetWindowAttributes(capture->display, capture->root, &attributes);
    
    capture->width = attributes.width;
    capture->height = attributes.height;
    
    return LEMBANG_SUCCESS;
}

LembangStatus screen_capture_frame(ScreenCapture *capture, unsigned char **buffer) {
    capture->image = XGetImage(capture->display, capture->root, 0, 0,
                              capture->width, capture->height,
                              AllPlanes, ZPixmap);
    
    if (!capture->image) {
        return LEMBANG_ERROR_CAPTURE;
    }
    
    *buffer = (unsigned char *)capture->image->data;
    return LEMBANG_SUCCESS;
}

void screen_capture_cleanup(ScreenCapture *capture) {
    if (capture->image) {
        XDestroyImage(capture->image);
    }
    if (capture->display) {
        XCloseDisplay(capture->display);
    }
}
