#ifndef LEMBANG_OPCAST_H
#define LEMBANG_OPCAST_H

// Version information
#define LEMBANG_OPCAST_VERSION_MAJOR 0
#define LEMBANG_OPCAST_VERSION_MINOR 1
#define LEMBANG_OPCAST_VERSION_PATCH 0

// Include all necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <gtk/gtk.h>

// Application status codes
typedef enum {
    LEMBANG_SUCCESS = 0,
    LEMBANG_ERROR_INIT = -1,
    LEMBANG_ERROR_CAPTURE = -2,
    LEMBANG_ERROR_ENCODE = -3,
    LEMBANG_ERROR_STREAM = -4
} LembangStatus;

// Configuration structure
typedef struct {
    int screen_width;
    int screen_height;
    int fps;
    char output_format[32];
    int audio_enabled;
    char stream_url[256];
} LembangConfig;

#endif // LEMBANG_OPCAST_H
