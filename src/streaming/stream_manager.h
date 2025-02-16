#ifndef STREAM_MANAGER_H
#define STREAM_MANAGER_H

#include "../../include/lembang_opcast.h"
#include <librtmp/rtmp.h>

typedef struct {
    RTMP *rtmp;
    char *url;
    int is_streaming;
} StreamManager;

LembangStatus stream_manager_init(StreamManager *manager, const char *url);
LembangStatus stream_manager_send_video(StreamManager *manager, 
                                      uint8_t *data, int size, 
                                      int timestamp);
LembangStatus stream_manager_send_audio(StreamManager *manager, 
                                      uint8_t *data, int size, 
                                      int timestamp);
void stream_manager_cleanup(StreamManager *manager);

#endif // STREAM_MANAGER_H
