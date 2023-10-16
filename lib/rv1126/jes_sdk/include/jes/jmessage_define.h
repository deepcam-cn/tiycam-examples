/***********************************************************************
 * @file jmessage_define.h
     JMESSAGE_DEFINE
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-09-05 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JMESSAGE_DEFINE_H__
#define __JMESSAGE_DEFINE_H__

#include <stdint.h>
#include <jvtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define JMCS_ALARM_ELIMINATION "alarm_elimination"  //消警

//typdef start
typedef enum {
    JMCSEVENT_NONE = 0x0,
    JMCSEVENT_ALARM,                     // 报警事件(TLV格式)
    JMCSEVENT_META,                      // 智能元数据(TLV格式)
    JMCSEVENT_TIMER,                     // 定时事件(TLV格式)
    JMCSEVENT_CUSTOM_START = 0x10000000, // 自定义事件起始
    JMCSEVENT_CUSTOM_END = 0x1FFFFFFF    // 自定义事件结束
} JMCSEvent_e;//事件分类

typedef struct {
    char package[64]; // 应用ID，唯一标识
    char linkage[64];      // 事件类型，对应 JEventMsg_t 中的 type
    char name[64]; // 事件类型名称，对应 JEventMsg_t 中的 typeName
    char configpath[64];
} JMCSLinkageInfo_t;      // 报警类型信息
typedef struct {
    int count;  //数量
    JMCSLinkageInfo_t list[128];//类型列表，最多支持 128 个
} JMCSLinkageList_t;//报警类型列表

typedef struct {
    char package[64];  // 应用ID，唯一标识
    JMCSEvent_e event; // 事件分类，对应 JEventMsg_t 中的 event
    char type[64];     // 事件类型，对应 JEventMsg_t 中的 type
    char name[64];     // 事件类型名称，对应 JEventMsg_t 中的 typeName
} JMCSEventInfo_t;// 报警类型信息
typedef struct {
    int count;// 数量
    JMCSEventInfo_t list[128]; // 类型列表，最多支持 128 个
} JMCSEventTypeList_t;// 报警类型列表

typedef struct {
    int wday;           // 0周日，1-6周一到周六
    uint32_t starttime; // 定时开始时间，单位当天秒数
    uint32_t stoptime;  // 定时结束时间，单位当天秒数
} JMCSTime_t;           // 计划时间
typedef struct {
    JBOOL defence;       // 是否布防
    int count;           // 布防计划数量
    JMCSTime_t plan[56]; // 布防计划
} JMCSDefenceParam_t;    // 布防参数

#ifdef __cplusplus
}
#endif
#endif // __JMESSAGE_DEFINE_H__
