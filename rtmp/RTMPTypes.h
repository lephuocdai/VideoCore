/*
 
 Video Core
 Copyright (C) 2014 James G. Hurley
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
 
 */
#ifndef videocore_RTMPTypes_h
#define videocore_RTMPTypes_h

#include <stdint.h>

static const size_t kRTMPDefaultChunkSize = 128;
static const size_t kRTMPSignatureSize = 1536;

typedef enum {
    kClientStateNone=0,
    kClientStateConnected,
    kClientStateHandshake0,
    kClientStateHandshake1s0,    // waiting for s0
    kClientStateHandshake1s1,
    kClientStateHandshake2,
    kClientStateHandshakeComplete,
    kClientStateFCPublish,
    kClientStateReady,
    kClientStateSessionStarted,
    kClientStateError,
    kClientStateNotConnected
} ClientState_t;


#pragma pack(push, 1)

typedef struct {
    int data : 24;
} int24_t;

typedef struct {
    
    int24_t timestamp;
    int24_t msg_length;
    int8_t msg_type_id;
    int msg_stream_id;
    
} RTMPChunk_0;
#define RTMP_CHUNK_TYPE_0 0x0
typedef struct {
    int24_t delta;
    int24_t msg_length;
    int8_t  msg_type_id;
} RTMPChunk_1;
#define RTMP_CHUNK_TYPE_1 0x40

typedef struct {
    int24_t delta;
} RTMPChunk_2;
#define RTMP_CHUNK_TYPE_2 0x80

#define RTMP_CHUNK_TYPE_3 0xC0

#pragma pack(pop)

/* offsets for packed values */
#define FLV_AUDIO_SAMPLESSIZE_OFFSET 1
#define FLV_AUDIO_SAMPLERATE_OFFSET  2
#define FLV_AUDIO_CODECID_OFFSET     4

#define FLV_VIDEO_FRAMETYPE_OFFSET   4

/* bitmasks to isolate specific values */
#define FLV_AUDIO_CHANNEL_MASK    0x01
#define FLV_AUDIO_SAMPLESIZE_MASK 0x02
#define FLV_AUDIO_SAMPLERATE_MASK 0x0c
#define FLV_AUDIO_CODECID_MASK    0xf0

#define FLV_VIDEO_CODECID_MASK    0x0f
#define FLV_VIDEO_FRAMETYPE_MASK  0xf0

#define AMF_END_OF_OBJECT         0x09

enum {
    FLV_HEADER_FLAG_HASVIDEO = 1,
    FLV_HEADER_FLAG_HASAUDIO = 4,
};

enum {
    FLV_TAG_TYPE_AUDIO  = 0x08,
    FLV_TAG_TYPE_VIDEO  = 0x09,
    FLV_TAG_TYPE_META   = 0x12,
    FLV_TAG_TYPE_INVOKE = 0x14
};

// RTMP header type is 1 byte
enum {
    RTMP_HEADER_TYPE_FULL      = 0x0, // RTMPChunk_0
    RTMP_HEADER_TYPE_NO_MSGID  = 0x1, // RTMPChunk_1
    RTMP_HEADER_TYPE_TIMESTAMP = 0x2, // RTMPChunk_2
    RTMP_HEADER_TYPE_ONLY      = 0x3, // no chunk
};

enum {
    RTMP_PT_CHUNK_SIZE   = 0x1,
    RTMP_PT_BYTES_READ   = 0x3,
    RTMP_PT_PING         = 0x4,
    RTMP_PT_SERVER_BW    = 0x5,
    RTMP_PT_CLIENT_BW    = 0x6,
    RTMP_PT_AUDIO        = 0x8,
    RTMP_PT_VIDEO        = 0x9,
    RTMP_PT_FLEX_STREAM  = 0xF,
    RTMP_PT_FLEX_OBJECT  = 0x10,
    RTMP_PT_FLEX_MESSAGE = 0x11,
    RTMP_PT_NOTIFY       = 0x12,
    RTMP_PT_SHARED_OBJ   = 0x13,
    RTMP_PT_INVOKE       = 0x14,
    RTMP_PT_METADATA     = 0x16,
};

enum {
    AMF_DATA_TYPE_NUMBER      = 0x00,
    AMF_DATA_TYPE_BOOL        = 0x01,
    AMF_DATA_TYPE_STRING      = 0x02,
    AMF_DATA_TYPE_OBJECT      = 0x03,
    AMF_DATA_TYPE_NULL        = 0x05,
    AMF_DATA_TYPE_UNDEFINED   = 0x06,
    AMF_DATA_TYPE_REFERENCE   = 0x07,
    AMF_DATA_TYPE_MIXEDARRAY  = 0x08,
    AMF_DATA_TYPE_OBJECT_END  = 0x09,
    AMF_DATA_TYPE_ARRAY       = 0x0a,
    AMF_DATA_TYPE_DATE        = 0x0b,
    AMF_DATA_TYPE_LONG_STRING = 0x0c,
    AMF_DATA_TYPE_UNSUPPORTED = 0x0d,
};

enum {
    FLV_MONO   = 0,
    FLV_STEREO = 1,
};

enum {
    FLV_SAMPLESSIZE_8BIT  = 0,
    FLV_SAMPLESSIZE_16BIT = 1 << FLV_AUDIO_SAMPLESSIZE_OFFSET,
};

enum {
    FLV_SAMPLERATE_SPECIAL = 0, /**< signifies 5512Hz and 8000Hz in the case of NELLYMOSER */
    FLV_SAMPLERATE_11025HZ = 1 << FLV_AUDIO_SAMPLERATE_OFFSET,
    FLV_SAMPLERATE_22050HZ = 2 << FLV_AUDIO_SAMPLERATE_OFFSET,
    FLV_SAMPLERATE_44100HZ = 3 << FLV_AUDIO_SAMPLERATE_OFFSET,
};

enum {
    FLV_CODECID_PCM                  = 0,
    FLV_CODECID_ADPCM                = 1 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_MP3                  = 2 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_PCM_LE               = 3 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_NELLYMOSER_8KHZ_MONO = 5 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_NELLYMOSER           = 6 << FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_AAC                  = 10<< FLV_AUDIO_CODECID_OFFSET,
    FLV_CODECID_SPEEX                = 11<< FLV_AUDIO_CODECID_OFFSET,
};

enum {
    FLV_CODECID_H263    = 2,
    FLV_CODECID_SCREEN  = 3,
    FLV_CODECID_VP6     = 4,
    FLV_CODECID_VP6A    = 5,
    FLV_CODECID_SCREEN2 = 6,
    FLV_CODECID_H264    = 7,
};

enum {
    FLV_FRAME_KEY        = 1 << FLV_VIDEO_FRAMETYPE_OFFSET,
    FLV_FRAME_INTER      = 2 << FLV_VIDEO_FRAMETYPE_OFFSET,
    FLV_FRAME_DISP_INTER = 3 << FLV_VIDEO_FRAMETYPE_OFFSET,
};

enum {
    kControlChannelStreamId = 0x03,
    kAudioChannelStreamId = 0x04,
    kVideoChannelStreamId = 0x06
};


#endif
