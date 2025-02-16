#ifndef VIDEO_ENCODER_H
#define VIDEO_ENCODER_H

#include "../../include/lembang_opcast.h"
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

typedef struct {
    AVFormatContext *format_ctx;
    AVCodecContext *codec_ctx;
    AVStream *stream;
    AVFrame *frame;
    AVPacket *packet;
    struct SwsContext *sws_ctx;
    int frame_count;
} VideoEncoder;

LembangStatus video_encoder_init(VideoEncoder *encoder, const char *filename, 
                                int width, int height, int fps);
LembangStatus video_encoder_encode_frame(VideoEncoder *encoder, uint8_t *rgb_data);
void video_encoder_cleanup(VideoEncoder *encoder);

#endif // VIDEO_ENCODER_H
