#include "video_encoder.h"

LembangStatus video_encoder_init(VideoEncoder *encoder, const char *filename, 
                                int width, int height, int fps) {
    avformat_alloc_output_context2(&encoder->format_ctx, NULL, NULL, filename);
    if (!encoder->format_ctx) {
        return LEMBANG_ERROR_INIT;
    }

    const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    encoder->stream = avformat_new_stream(encoder->format_ctx, codec);
    encoder->codec_ctx = avcodec_alloc_context3(codec);
    
    // Set encoding parameters
    encoder->codec_ctx->width = width;
    encoder->codec_ctx->height = height;
    encoder->codec_ctx->time_base = (AVRational){1, fps};
    encoder->codec_ctx->framerate = (AVRational){fps, 1};
    encoder->codec_ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    
    // Initialize frame and packet
    encoder->frame = av_frame_alloc();
    encoder->packet = av_packet_alloc();
    encoder->frame_count = 0;
    
    // Initialize scaler
    encoder->sws_ctx = sws_getContext(width, height, AV_PIX_FMT_RGB24,
                                     width, height, AV_PIX_FMT_YUV420P,
                                     SWS_BICUBIC, NULL, NULL, NULL);
    
    return LEMBANG_SUCCESS;
}

LembangStatus video_encoder_encode_frame(VideoEncoder *encoder, uint8_t *rgb_data) {
    // Convert RGB to YUV
    const int in_linesize[1] = { encoder->codec_ctx->width * 3 };
    sws_scale(encoder->sws_ctx, (const uint8_t * const *)&rgb_data, in_linesize,
              0, encoder->codec_ctx->height, encoder->frame->data, 
              encoder->frame->linesize);
    
    encoder->frame->pts = encoder->frame_count++;
    
    // Encode frame
    int ret = avcodec_send_frame(encoder->codec_ctx, encoder->frame);
    if (ret < 0) {
        return LEMBANG_ERROR_ENCODE;
    }
    
    while (ret >= 0) {
        ret = avcodec_receive_packet(encoder->codec_ctx, encoder->packet);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            break;
        }
        av_packet_unref(encoder->packet);
    }
    
    return LEMBANG_SUCCESS;
}

void video_encoder_cleanup(VideoEncoder *encoder) {
    sws_freeContext(encoder->sws_ctx);
    av_frame_free(&encoder->frame);
    av_packet_free(&encoder->packet);
    avcodec_free_context(&encoder->codec_ctx);
    avformat_free_context(encoder->format_ctx);
}
