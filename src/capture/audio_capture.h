#ifndef AUDIO_CAPTURE_H
#define AUDIO_CAPTURE_H

#include "../../include/lembang_opcast.h"
#include <pulse/simple.h>
#include <pulse/error.h>

typedef struct {
    pa_simple *pa_handle;
    pa_sample_spec sample_spec;
    int buffer_size;
    uint8_t *buffer;
} AudioCapture;

LembangStatus audio_capture_init(AudioCapture *capture);
LembangStatus audio_capture_frame(AudioCapture *capture);
void audio_capture_cleanup(AudioCapture *capture);

#endif // AUDIO_CAPTURE_H
