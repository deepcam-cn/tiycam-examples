/***********************************************************************
 * @file jbasic_define.h
     JBASIC_DEFINE
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-09-26 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JBASIC_DEFINE_H__
#define __JBASIC_DEFINE_H__

#include <stdint.h>
#include <jvtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

//typdef start
typedef struct
{
    int month;   //月份：1-12
    int week;    //本月第几周：1-5
    int weekday; //星期几，0-6，0表示星期天
    int hour;    //时：0-24
    int minute;  //分：0-59
    int second;  //秒：0-59
} JBASDstTime_t; //夏令时时间
typedef struct
{
    char tz[10];                  //格式示例：+/-hh[:mm[:ss]] ,+表示东区，-表示西区，[]表示可选
    JBOOL dstEnable;             //是否开启夏令时
    JU32 dstOffset;              //夏令时偏移时间,+-秒数
    JBASDstTime_t dstBegin;      //夏令时开始时间
    JBASDstTime_t dstEnd;        //夏令时结束时间
} JBASTimezone_t;                //夏令时参数
typedef struct
{
    JBOOL enable;     //使能
    int interval;     //校时间隔时间，单位小时
    char server[128]; //校时服务器地址
} JBASNtp_t;          // ntp校时服务配置
typedef struct
{
    JBOOL enable;    //是否使能
    int weekday;     //星期几，0-6，0表示星期天，7表示每一天
    int timehour;    //重启时间：时，0-23
    int timemin;     //重启时间：分，0-59
} JBASRebootTimer_t; //定时重启参数
typedef struct{
    char deviceid[32];  //设备ID：云视通号
    char devname[64];   //设备名称
    char language[32];  //语言
    char devmodel[64];  //设备型号：整机型号，产测配置
    char hardware[64];  //硬件信息
    char firmware[64];  //固件版本
    char serialnum[32]; //序列号
    char productid[32]; //产品ID：芯片ID具有唯一性可用于绑定硬件
    char uoid[256];     //uoid
    char mac[18];       //mac地址格式：CE:88:C3:C4:B9:73
    char reserve[64];   //预留
}JBASDevInfo_t;//设备信息
typedef struct {
    int wday;           // 0周日，1-6周一到周六
    uint32_t starttime; // 定时开始时间，单位当天秒数
    uint32_t stoptime;  // 定时结束时间，单位当天秒数
    char startcmd[64];  // 启动命令和参数
    char stopcmd[64];   // 停止命令和参数
} JBASTime_t;   //计划时间
typedef struct {
    int count;  //times个数
    JBASTime_t times[56];//计划时间，每天支持8个时间段，每周共支持56个时间段
} JBASWdtTimer_t; //看门狗定时器参数
typedef enum
{
    JBAS_LOGTYPE_RUN,   //运行日志
    JBAS_LOGTYPE_OPT,   //操作日志
    JBAS_LOGTYPE_ALL    //全部日志
} JBASLogType_e;//日志类型
typedef struct
{
    JBASLogType_e type; // 日志类型
    char typeName[16];  // 类型名称用于展示
    char time[20];      // 日志时间，YYYY-MM-DD hh:mm:ss
    char user[64];      // 操作用户名，运行日志显示进程名称
    char host[48];      // 操作ip:port，运行日志固定为-
    char event[256];    // 事件
    char result[16];    // 事件结果，运行日志固定为-
} JBASLogItem_t;//日志信息

#ifdef __cplusplus
}
#endif
#endif // __JBASIC_DEFINE_H__
