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
#ifndef __JALARM_DEFINE_H__
#define __JALARM_DEFINE_H__

#include <stdint.h>
#include <jvtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif


//typdef start
typedef enum {
    JALM_EMAIL_ENCRYPT_NONE, // 无加密
    JALM_EMAIL_ENCRYPT_TLS,  // TLS加密
    JALM_EMAIL_ENCRYPT_SSL,  // SSL加密
    JALM_EVENT_ENCRYPT_MAX
} JALMEmailEncrypt_e; // 邮件加密类型
typedef enum {
    JALM_LIGHTTYPE_WHITE,  // 白光灯
    JALM_LIGHTTYPE_STATUS, // 状态灯
    JALM_LIGHTTYPE_MAX
} JALMLightType_e; // 报警灯类型
typedef struct
{
    int wday;          //星期几，0-6，0表示星期天
    uint32_t starttime;  // 定时开始时间，单位当天秒数
    uint32_t stoptime;   // 定时结束时间，单位当天秒数
}JALMTime_t;//静音时间
typedef struct {
    JBOOL allTime;        // 全时段静音
    int count;            // 时间数量
    JALMTime_t times[28]; // 静音时间段
} JALMSoundMuteParam_t;   // 报警声音静音参数
typedef struct {
    JBOOL enable;       //报警声音使能
    char filename[128]; //报警音文件名称（绝对路径）
    int playtimes;      //播放次数，默认为0，0表示脉冲报警播放1次，非脉冲报警持续播放至报警停止
    char reserve[64];   // 预留字段
}JALMSoundLink_t;//报警声音联动参数
typedef struct{
    JBOOL enable;   //全局布防开关
    char reserve[64];   // 预留字段
}JALMLightParam_t;//报警灯参数
typedef struct {
    JBOOL enable;   //是否联动闪烁
    int strength;   //闪烁强度: 白光灯时：1低频闪烁，2中频闪烁，3高频闪烁（或常量），RGB灯时0-100频率增加
    char reserve[64];   // 预留字段
} JALMLightLink_t;//报警灯联动参数

typedef struct {
    int id;       // 报警输出id
    int duration; // 有效时长，0表示持续有效，直到报警停止，暂时未生效
    char reserve[64];   // 预留字段
} JALMOutput_t;    // 报警输出信息
typedef struct {
    int count;          // 联动id的数量
    JALMOutput_t out[16]; // 报警输出最多可同时联动16个
} JALMOutputLinkParam_t;     // 报警输出联动参数
typedef struct {
    char sender[64];            // 发件人
    char server[64];            // 服务器
    char username[64];          // 用户名
    char passwd[256];           // 密码：最大支持64位密码
    JALMEmailEncrypt_e encrypt; // 加密类型
    int port;                   // 端口号
    char receiver0[64];         // 收件人1
    char receiver1[64];         // 收件人2
    char receiver2[64];         // 收件人3
    char receiver3[64];         // 收件人4
    char reserve[256];   // 预留字段
} JALMEmailParam_t;             // 邮件参数
typedef struct
{
    JBOOL enable;   //是否开启
    char addr[64];  //地址：http://abc.com https://abc.com 192.168.1.100
    int port;       //端口号
    char username[64];  //用户名
    char passwd[256];   //密码：最大支持64位密码
    char reserve[256];  //预留字段
}JALMReportServerParam_t;//上报服务参数
typedef struct{
    JBOOL defence;//是否布防，默认为true，配置为false时所有发送的事件消息将直接被丢弃
    char reserve[64];  //预留字段
}JALMDefenceParam_t; //全局参数
typedef struct{
    JBOOL enable;   //是否联动
    char reserve[64];  //预留字段
}JALMLinkParam_t;//通用联动参数

typedef struct {
    JBOOL reportHttp;   //抓拍图片上报到http服务器
    JBOOL reportFtp;    //抓拍图片上报到FTP服务器
    JBOOL reportEMail;  //抓拍图片发送到邮件
    char reserve[64];   //预留
} JSnapshotParam_t;  //抓拍参数
typedef struct {
    int wday;            // 0周日，1-6周一到周六
    uint32_t starttime;  // 开始时间，单位当天秒数
    uint32_t stoptime;   // 结束时间，单位当天秒数
    uint32_t interval;   // 抓拍间隔
} JSnapPlanTime_t;   //抓拍计划时间
typedef struct {
    int count;  //times个数
    JSnapPlanTime_t times[56];//计划时间，每天支持8个时间段，每周共支持56个时间段
} JSnapshotPlan_t; //抓拍计划
typedef enum {
    JALM_MODE_NORMALLY_OPEN,  //常开，闭合报警
    JALM_MODE_NORMALLY_CLOSE, //常闭，断开报警
}JALMMode_e;
typedef struct {
    int id;          //报警输入ID
    JBOOL enable;       //是否启用
    JALMMode_e mode;  //报警模式
}JALMInput_t; //开关量报警输入参数
typedef struct{
    int count;  //报警输入个数
    JALMInput_t input[16];//报警输入参数，最多支持16个
}JALMInputList_t;//开关量报警输入参数列表


#ifdef __cplusplus
}
#endif
#endif // __JALARM_DEFINE_H__
