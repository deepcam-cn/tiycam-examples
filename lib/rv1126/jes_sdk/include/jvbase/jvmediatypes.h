/*
 * jvmediatypes.h
 *
 *  Created on: 2019年2月16日
 *      Author: Administrator
 */

#ifndef SOURCE_JVBASE_JVMEDIATYPES_H_
#define SOURCE_JVBASE_JVMEDIATYPES_H_

#include <stdint.h>

//视频编码类型, 和O帧一致
typedef enum{
	JVMEDIA_VIDEO_TYPE_RAW=0,	//未编码
	JVMEDIA_VIDEO_TYPE_H264,
	JVMEDIA_VIDEO_TYPE_H265,
	JVMEDIA_VIDEO_TYPE_MJPEG,
	JVMEDIA_VIDEO_TYPE_UNKNOWN,
}JVMediaVideotype_e;


//帧类型, 和云视通帧类型兼容
typedef enum{
	JVMEDIA_FRAME_TYPE_UNKNOWN=0,
	JVMEDIA_FRAME_TYPE_I,
	JVMEDIA_FRAME_TYPE_B,
	JVMEDIA_FRAME_TYPE_P,
	JVMEDIA_FRAME_TYPE_A, 		//audio
	JVMEDIA_FRAME_TYPE_VI=22,	//0x16 虚拟I帧
	JVMEDIA_FRAME_TYPE_RAW,     //未编码数据，可能是YUV或ARGB取决于请求参数
	JVMEDIA_FRAME_TYPE_JPEG,    //JPEG帧
	JVMEDIA_FRAME_TYPE_USER=0x80,//用户自定义帧:0x80~0xff
	JVMEDIA_FRAME_TYPE_BUTT
}JVMediaFrameType_e;

typedef enum
{
	JVMEDIA_VENC_RC_MODE_CBR,
	JVMEDIA_VENC_RC_MODE_VBR,
	JVMEDIA_VENC_RC_MODE_FIXQP
}JVMediaRcmode_e;

typedef struct
{
	JVMediaVideotype_e enVideoType;	/* 解码视频类型，e.g. H264 */
	int nVideoWidth;				/* 解码视频宽 */
	int nVideoHigh;					/* 解码视频高 */
	float frameRate;				/* 解码帧率 */
}JVMediaVDecAttr_t;

typedef struct
{
	unsigned char	*buffer;
	int				len;
	JVMediaFrameType_e	frametype;
	uint64_t			timestamp;	//timestamp in msecond.
}JVMediaFrame_t;


//音频编码类型, 和O帧一致
typedef enum
{
	JVMEDIA_AUDIO_TYPE_PCM=0,
	JVMEDIA_AUDIO_TYPE_AMR,
	JVMEDIA_AUDIO_TYPE_G711_A,	//世界其他地区
	JVMEDIA_AUDIO_TYPE_G711_U,	//主要用在北美和日本
	JVMEDIA_AUDIO_TYPE_G726,
	JVMEDIA_AUDIO_TYPE_AAC,
	JVMEDIA_AUDIO_TYPE_AC3,
	JVMEDIA_AUDIO_TYPE_MAX
}JVMediaAudioType_e;

//音频编码参数
typedef struct
{
	JVMediaAudioType_e encType;		//类型
	int32_t			samplerate;		//采样率
	int32_t			bitwidth;		//采样位数
}JVMediaAdecAttr_t;


#endif /* SOURCE_JVBASE_JVMEDIATYPES_H_ */
