#include "stream_manager.h"

LembangStatus stream_manager_init(StreamManager *manager, const char *url) {
    manager->rtmp = RTMP_Alloc();
    RTMP_Init(manager->rtmp);
    
    if (!RTMP_SetupURL(manager->rtmp, (char*)url)) {
        return LEMBANG_ERROR_INIT;
    }
    
    RTMP_EnableWrite(manager->rtmp);
    
    if (!RTMP_Connect(manager->rtmp, NULL) || !RTMP_ConnectStream(manager->rtmp, 0)) {
        return LEMBANG_ERROR_INIT;
    }
    
    manager->is_streaming = 1;
    manager->url = strdup(url);
    
    return LEMBANG_SUCCESS;
}

LembangStatus stream_manager_send_video(StreamManager *manager, 
                                      uint8_t *data, int size, 
                                      int timestamp) {
    if (!manager->is_streaming) {
        return LEMBANG_ERROR_STREAM;
    }
    
    RTMPPacket packet = {0};
    RTMPPacket_Reset(&packet);
    RTMPPacket_Alloc(&packet, size);
    
    packet.m_packetType = RTMP_PACKET_TYPE_VIDEO;
    packet.m_nChannel = 0x04;
    packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
    packet.m_nTimeStamp = timestamp;
    packet.m_nInfoField2 = manager->rtmp->m_stream_id;
    packet.m_nBodySize = size;
    memcpy(packet.m_body, data, size);
    
    if (!RTMP_SendPacket(manager->rtmp, &packet, 0)) {
        RTMPPacket_Free(&packet);
        return LEMBANG_ERROR_STREAM;
    }
    
    RTMPPacket_Free(&packet);
    return LEMBANG_SUCCESS;
}

LembangStatus stream_manager_send_audio(StreamManager *manager, 
                                      uint8_t *data, int size, 
                                      int timestamp) {
    if (!manager->is_streaming) {
        return LEMBANG_ERROR_STREAM;
    }
    
    RTMPPacket packet = {0};
    RTMPPacket_Reset(&packet);
    RTMPPacket_Alloc(&packet, size);
    
    packet.m_packetType = RTMP_PACKET_TYPE_AUDIO;
    packet.m_nChannel = 0x04;
    packet.m_headerType = RTMP_PACKET_SIZE_LARGE;
    packet.m_nTimeStamp = timestamp;
    packet.m_nInfoField2 = manager->rtmp->m_stream_id;
    packet.m_nBodySize = size;
    memcpy(packet.m_body, data, size);
    
    if (!RTMP_SendPacket(manager->rtmp, &packet, 0)) {
        RTMPPacket_Free(&packet);
        return LEMBANG_ERROR_STREAM;
    }
    
    RTMPPacket_Free(&packet);
    return LEMBANG_SUCCESS;
}

void stream_manager_cleanup(StreamManager *manager) {
    if (manager->rtmp) {
        RTMP_Close(manager->rtmp);
        RTMP_Free(manager->rtmp);
    }
    if (manager->url) {
        free(manager->url);
    }
    manager->is_streaming = 0;
}
