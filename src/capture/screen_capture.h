#ifndef SCREEN_CAPTURE_H
#define SCREEN_CAPTURE_H

#include "../../include/lembang_opcast.h"

typedef struct {
    Display *display;
    Window root;
    int width;
    int height;
    XImage *image;
} ScreenCapture;

// Initialize screen capture
LembangStatus screen_capture_init(ScreenCapture *capture);

// Capture single frame
LembangStatus screen_capture_frame(ScreenCapture *capture, unsigned char **buffer);

// Clean up resources
void screen_capture_cleanup(ScreenCapture *capture);

#endif // SCREEN_CAPTURE_H
