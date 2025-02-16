#include "audio_capture.h"

LembangStatus audio_capture_init(AudioCapture *capture) {
    // Set up PulseAudio sample specifications
    capture->sample_spec.format = PA_SAMPLE_S16LE;
    capture->sample_spec.channels = 2;
    capture->sample_spec.rate = 44100;
    
    // Buffer for 100ms of audio
    capture->buffer_size = (capture->sample_spec.rate * 2 * 2) / 10;
    capture->buffer = malloc(capture->buffer_size);
    
    int error;
    capture->pa_handle = pa_simple_new(
        NULL,                    // Use default server
        "Lembang-Opcast",       // Application name
        PA_STREAM_RECORD,       // Recording stream
        NULL,                    // Use default device
        "Audio Capture",         // Stream description
        &capture->sample_spec,   // Sample format
        NULL,                    // Use default channel map
        NULL,                    // Use default buffering attributes
        &error                   // Error code
    );
    
    if (!capture->pa_handle) {
        return LEMBANG_ERROR_INIT;
    }
    
    return LEMBANG_SUCCESS;
}

LembangStatus audio_capture_frame(AudioCapture *capture) {
    int error;
    if (pa_simple_read(capture->pa_handle, capture->buffer, 
                       capture->buffer_size, &error) < 0) {
        return LEMBANG_ERROR_CAPTURE;
    }
    return LEMBANG_SUCCESS;
}

void audio_capture_cleanup(AudioCapture *capture) {
    if (capture->pa_handle) {
        pa_simple_free(capture->pa_handle);
    }
    if (capture->buffer) {
        free(capture->buffer);
    }
}
