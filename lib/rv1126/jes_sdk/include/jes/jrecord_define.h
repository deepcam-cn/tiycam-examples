/***********************************************************************
 * @file jrecord_define.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JRECORD_DEFINE_H__
#define __JRECORD_DEFINE_H__

#include <stdint.h>
#include <jvtypes.h>
#include <jvmediatypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

//typdef start
typedef enum {
    JREC_NORMAL = 'N',  // 手动记录 78
    JREC_ALARM = 'A',   // 报警记录 65
    JREC_ALL            // 检索使用
} JRecType_e;//记录文件类型
typedef enum {
    JRECMODE_NONE,    // 关闭
    JRECMODE_NORMAL,  // 全天录像
    JRECMODE_TIMING,  // 定时录像
} JRecMode_e;        // 录像模式
typedef struct {
    int streamid;           // 码流id
    JRecMode_e recMode;     // 录像模式
    JBOOL enableAudio;       // 是否录制音频
    JBOOL enableOnlyIFrame;  // 只录I帧
    int fileDuration;       // 单个文件持续时间（打包时长），单位为秒
    int preRecDuration;     // 预录时长(报警录像使用)
    int delayDuration;      // 录像延时(报警录像使用)
    char reserve[64];   //预留
} JRecParam_t;  //录像参数
typedef struct {
    int wday;               // 0周日，1-6周一到周六
    uint32_t starttime;  // 定时开始时间，单位当天秒数
    uint32_t stoptime;   // 定时结束时间，单位当天秒数
} JRecTime_t;   //计划时间
typedef struct {
    int count;  //times个数
    JRecTime_t times[56];//计划时间，每天支持8个时间段，每周共支持56个时间段
} JRecPlan_t; //录像计划
typedef struct {
    JBOOL recording;    //是否正在录像
    char fname[128];    //正在录像的文件路径
} JRecordingFile_t; //录像文件
typedef struct {
    JRecType_e type;     // RECTYPE
    uint16_t chn;        // 通道id
    uint8_t stream;      // 码流id
    uint64_t starttime;  // 开始时间（秒）
    uint32_t duration;   // 时长（秒）
    uint32_t filesize;   // 文件大小
    char fname[128];      // 文件路径
} JRecFileItem_t;//录像文件
typedef struct {
    int chn;     // 通道id
    int date;    // 20170101
} JRecDateItem_t;//录像日期
typedef struct {
    JBOOL reportHttp;   //抓拍图片上报到http服务器
    JBOOL reportFtp;    //抓拍图片上报到FTP服务器
    JBOOL reportEMail;  //抓拍图片发送到邮件
    char reserve[64];   //预留
} JRecSnapParam_t;  //录像参数
typedef struct {
    int wday;            // 0周日，1-6周一到周六
    uint32_t starttime;  // 开始时间，单位当天秒数
    uint32_t stoptime;   // 结束时间，单位当天秒数
    uint32_t interval;   // 抓拍间隔
} JRecSnapTime_t;   //计划时间
typedef struct {
    int count;  //times个数
    JRecSnapTime_t times[56];//计划时间，每天支持8个时间段，每周共支持56个时间段
} JRecSnapPlan_t; //录像计划
typedef struct {
    JRecType_e type;     // RECTYPE
    uint16_t chn;        // 通道id
    uint64_t starttime;  // 开始时间（秒）
    uint32_t filesize;   // 文件大小
    char fname[64];      // 文件路径
} JRecSnapFileItem_t;//录像文件
typedef struct {
    int event;          // 事件分类，取值参见 jmessage_define.h 中 JMCSEvent_e
    int chntype;        // 通道类型，取值参见 jmessage_define.h 中 JMCSEventChnType_e
    int chn;            // 通道号，从0开始
    char type[64];      // 事件类型，不可重复定义，详见《事件定义管理指南》
    char typeName[128]; // 事件类型名称：需具有可读性，需支持多语言
    int status;         // 事件状态，取值参见 jmessage_define.h 中 JMCSEventStatus_e
    uint64_t time;       // 事件时间
    char snapfile[128]; // 抓拍的图片文件的绝对路径
} JRecEventItem_t;// 事件查询

#ifdef __cplusplus
}
#endif
#endif // __JRECORD_DEFINE_H__
