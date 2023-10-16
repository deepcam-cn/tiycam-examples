/***********************************************************************
 * @file jes_alarm.h
     JES_ALARM
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-09-05 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JES_ALARM_H__
#define __JES_ALARM_H__

#include <stdint.h>
#include <jalarm_define.h>


#ifdef __cplusplus
extern "C"
{
#endif

#define PACKAGE_ALARMMANAGER "AlarmManager"

//本应用使用MCS的Config接口进行配置
//@see jes_mcs.h JES_MCS_Config 接口文档

//mcs config interface start
typedef enum {
    //=============================[全局接口]===================================
    JESALM_CMD_CLEAR_CONFIG = 0x0, // 清除联动配置
                                   //     @req:JESALM_ClearLinkConfig_Req_t
                                   //     @resp:None
                                   //     @ret:<0 失败，==0 成功
    //=============================[邮件报警]===================================
    JESALM_CMD_EMAIL_GETPARAM = 0x100, // 获取邮箱参数
    JESALM_CMD_EMAIL_GETPARAM_DEF,     // 获取默认邮箱参数
                                       //     @req:JESALM_Config_t
                                       //     @resp:JALMEmailParam_t
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_EMAIL_SETPARAM,         // 配置邮箱参数
                                       //     @req:JESALM_EmailSetParam_Req_t
                                       //     @resp:None
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_EMAIL_GETLINKPARAM,     // 获取邮箱联动参数
    JESALM_CMD_EMAIL_GETLINKPARAM_DEF, // 获取默认邮箱联动参数
                                       //     @req:JESALM_EmailGetLinkParam_Req_t
                                       //     @resp:JALMLinkParam_t
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_EMAIL_SETLINKPARAM,     // 配置邮箱联动参数
                                       //     @req:JESALM_EmailSetLinkParam_Req_t
                                       //     @resp:None
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_EMAIL_SENDTEST,         // 发送测试邮件
                                       //     @req:JESALM_Config_t
                                       //     @resp:None
                                       //     @ret:<0 失败，==0 成功
    //=============================[HTTP报警]===================================
    JESALM_CMD_HTTP_GETPARAM = 0x200, // 获取HTTP上报服务器参数
    JESALM_CMD_HTTP_GETPARAM_DEF,     // 获取默认HTTP上报服务器参数
                                      //     @req:JESALM_Config_t
                                      //     @resp:JALMReportServerParam_t
                                      //     @ret:<0 失败，==0 成功
    JESALM_CMD_HTTP_SETPARAM,         // 配置HTTP上报服务器参数
                                      //     @req:JESALM_ReportSetParam_Req_t
                                      //     @resp:None
                                      //     @ret:<0 失败，==0 成功
    JESALM_CMD_HTTP_GETLINKPARAM,     // 获取HTTP上报联动参数
    JESALM_CMD_HTTP_GETLINKPARAM_DEF, // 获取默认HTTP上报联动参数
                                      //     @req:JESALM_ReportGetLinkParam_Req_t
                                      //     @resp:JALMLinkParam_t
                                      //     @ret:<0 失败，==0 成功
    JESALM_CMD_HTTP_SETLINKPARAM,     // 配置HTTP上报联动参数
                                      //     @req:JESALM_ReportSetLinkParam_Req_t
                                      //     @resp:None
                                      //     @ret:<0 失败，==0 成功
    //=============================[FTP报警]===================================
    JESALM_CMD_FTP_GETPARAM = 0x300, // 获取FTP上报服务器参数
    JESALM_CMD_FTP_GETPARAM_DEF,     // 获取默认FTP上报服务器参数
                                     //     @req:JESALM_Config_t
                                     //     @resp:JALMReportServerParam_t
                                     //     @ret:<0 失败，==0 成功
    JESALM_CMD_FTP_SETPARAM,         // 配置FTP上报服务器参数
                                     //     @req:JESALM_ReportSetParam_Req_t
                                     //     @resp:None
                                     //     @ret:<0 失败，==0 成功
    JESALM_CMD_FTP_GETLINKPARAM,     // 获取FTP上报联动参数
    JESALM_CMD_FTP_GETLINKPARAM_DEF, // 获取默认FTP上报联动参数
                                     //     @req:JESALM_ReportGetLinkParam_Req_t
                                     //     @resp:JALMLinkParam_t
                                     //     @ret:<0 失败，==0 成功
    JESALM_CMD_FTP_SETLINKPARAM,     // 配置FTP上报联动参数
                                     //     @req:JESALM_ReportSetLinkParam_Req_t
                                     //     @resp:None
                                     //     @ret:<0 失败，==0 成功
    //=============================[开关量报警]===================================
    JESALM_CMD_OUTPUT_GETLINKPARAM = 0x400, // 获取报警输出联动参数
    JESALM_CMD_OUTPUT_GETLINKPARAM_DEF,     // 获取默认报警输出联动参数
                                            //     @req:JESALM_OutputGetLinkParam_Req_t
                                            //     @resp:JALMOutputLinkParam_t
                                            //     @ret:<0 失败，==0 成功
    JESALM_CMD_OUTPUT_SETLINKPARAM,         // 配置报警输出联动参数
                                            //     @req:JESALM_OutputSetLinkParam_Req_t
                                            //     @resp:None
                                            //     @ret:<0 失败，==0 成功
    //=============================[灯光报警]===================================
    JESALM_CMD_LIGHT_GETPARAM = 0x500, // 获取报警灯全局参数
    JESALM_CMD_LIGHT_GETPARAM_DEF,     // 获取默认报警灯全局参数
                                       //     @req:JESALM_Config_t
                                       //     @resp:JALMLightParam_t
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_LIGHT_SETPARAM,         // 配置报警灯全局参数
                                       //     @req:JESALM_LightSetParam_Req_t
                                       //     @resp:None
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_LIGHT_GETLINKPARAM,     // 获取报警灯联动参数
    JESALM_CMD_LIGHT_GETLINKPARAM_DEF, // 获取默认报警灯联动参数
                                       //     @req:JESALM_LightGetLinkParam_Req_t
                                       //     @resp:JALMLinkParam_t
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_LIGHT_SETLINKPARAM,     // 配置报警灯联动参数
                                       //     @req:JESALM_LightSetLinkParam_Req_t
                                       //     @resp:None
                                       //     @ret:<0 失败，==0 成功
    //=============================[OSD报警]===================================
    JESALM_CMD_OSD_GETLINKPARAM = 0x600, // 获取OSD联动参数
    JESALM_CMD_OSD_GETLINKPARAM_DEF,     // 获取默认OSD联动参数
                                         //     @req:JESALM_OSDGetLinkParam_Req_t
                                         //     @resp:JALMLinkParam_t
                                         //     @ret:<0 失败，==0 成功
    JESALM_CMD_OSD_SETLINKPARAM,         // 配置OSD联动参数
                                         //     @req:JESALM_OSDSetLinkParam_Req_t
                                         //     @resp:None
                                         //     @ret:<0 失败，==0 成功
    //=============================[声音报警]===================================
    JESALM_CMD_SOUND_GETPARAM = 0x700, // 获取报警声音全局参数
    JESALM_CMD_SOUND_GETPARAM_DEF,     // 获取默认报警声音全局参数
                                       //     @req:JESALM_Config_t
                                       //     @resp:JALMSoundMuteParam_t
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_SOUND_SETPARAM,         // 配置报警声音全局参数
                                       //     @req:JESALM_SoundSetParam_Req_t
                                       //     @resp:None
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_SOUND_GETLINKPARAM,     // 获取报警声音联动参数
    JESALM_CMD_SOUND_GETLINKPARAM_DEF, // 获取默认报警声音联动参数
                                       //     @req:JESALM_SoundGetLinkParam_Req_t
                                       //     @resp:JALMSoundLink_t
                                       //     @ret:<0 失败，==0 成功
    JESALM_CMD_SOUND_SETLINKPARAM,     // 配置报警声音联动参数
                                       //     @req:JESALM_SoundSetLinkParam_Req_t
                                       //     @resp:None
                                       //     @ret:<0 失败，==0 成功
    //=============================[抓拍计划]===================================
    JESALM_CMD_SNAPSHOT_GETPLAN = 0x800, // 获取抓拍计划
                                         //     @req:JESALM_SnapshotGetPlan_Req_t
                                         //     @resp:JSnapshotPlan_t
                                         //     @ret:<0 失败，==0 成功
    JESALM_CMD_SNAPSHOT_SETPLAN,         // 配置抓拍计划
                                         //     @req:JESALM_SnapshotSetPlan_Req_t
                                         //     @resp:None
                                         //     @ret:<0 失败，==0 成功
    JESALM_CMD_SNAPSHOT_GETRPARAM,       // 获取抓拍参数
    JESALM_CMD_SNAPSHOT_GETRPARAM_DEF,   // 获取默认抓拍参数
                                         //     @req:JESALM_SnapshotGetParam_Req_t
                                         //     @resp:JSnapshotParam_t
                                         //     @ret:<0 失败，==0 成功
    JESALM_CMD_SNAPSHOT_SETPARAM,        // 配置抓拍参数
                                         //     @req:JESALM_SnapshotSetParam_Req_t
                                         //     @resp:None
                                         //     @ret:<0 失败，==0 成功
    //=============================[报警输入]===================================
    JESALM_CMD_INPUT_GETRPARAM = 0x900,  // 获取报警输入参数
    JESALM_CMD_INPUT_GETRPARAM_DEF,      // 获取默认报警输入参数
                                         //     @req:JESALM_Config_t
                                         //     @resp:JALMInputList_t
                                         //     @ret:<0 失败，==0 成功
    JESALM_CMD_INPUT_SETPARAM,           // 配置报警输入参数
                                         //     @req:JESALM_InputSetParam_Req_t
                                         //     @resp:None
                                         //     @ret:<0 失败，==0 成功
    JESALM_CMD_MAX
} JESALMCmd_e; // 指令类型

typedef struct{
    char package[64];//固定为宏定义： PACKAGE_ALARMMANAGER
    JESALMCmd_e cmd;//指令
}JESALM_Config_t;//配置接口信息

typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
}JESALM_ClearLinkConfig_Req_t;//清除联动配置请求参数

typedef struct{
    JESALM_Config_t config;//配置接口信息
    JALMEmailParam_t param;  //邮箱参数
}JESALM_EmailSetParam_Req_t;//配置邮箱请求参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
}JESALM_EmailGetLinkParam_Req_t;//获取邮箱联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
    JALMLinkParam_t param;//联动参数
}JESALM_EmailSetLinkParam_Req_t;//配置邮箱联动参数

typedef struct{
    JESALM_Config_t config;//配置接口信息
    JALMReportServerParam_t param;//上报服务器参数
}JESALM_ReportSetParam_Req_t;//配置上报服务器请求参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
}JESALM_ReportGetLinkParam_Req_t;//获取上报联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
    JALMLinkParam_t param;//联动参数
}JESALM_ReportSetLinkParam_Req_t;//配置上报联动参数

typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
}JESALM_OutputGetLinkParam_Req_t;//获取报警输出联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
    JALMOutputLinkParam_t param;//联动参数
}JESALM_OutputSetLinkParam_Req_t;//配置报警输出联动参数

typedef struct{
    JESALM_Config_t config;//配置接口信息
    JALMLightParam_t param;//报警灯参数
}JESALM_LightSetParam_Req_t;//配置报警灯请求参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
    JALMLightType_e lightType;//报警灯类型
}JESALM_LightGetLinkParam_Req_t;//获取报警灯联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
    JALMLightType_e lightType;//报警灯类型
    JALMLightLink_t param;//联动参数
}JESALM_LightSetLinkParam_Req_t;//配置报警灯联动参数

typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
}JESALM_OSDGetLinkParam_Req_t;//获取OSD联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
    JALMLinkParam_t param;//联动参数
}JESALM_OSDSetLinkParam_Req_t;//配置OSD联动参数

typedef struct{
    JESALM_Config_t config;//配置接口信息
    JALMSoundMuteParam_t param;//报警声音静音参数
}JESALM_SoundSetParam_Req_t;//配置报警声音请求参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
}JESALM_SoundGetLinkParam_Req_t;//获取报警声音联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    char type[64];//联动事件类型
    JALMSoundLink_t param;//联动参数
}JESALM_SoundSetLinkParam_Req_t;//配置报警声音联动参数

typedef struct{
    JESALM_Config_t config;//配置接口信息
    int chn;
}JESALM_SnapshotGetPlan_Req_t;//获取抓拍计划请求参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    int chn;
    JSnapshotPlan_t plan;//抓拍计划
}JESALM_SnapshotSetPlan_Req_t;//配置抓拍计划请求参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    int chn;
}JESALM_SnapshotGetParam_Req_t;//获取上报联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    int chn;
    JSnapshotParam_t param;//联动参数
}JESALM_SnapshotSetParam_Req_t;//配置上报联动参数
typedef struct{
    JESALM_Config_t config;//配置接口信息
    JALMInputList_t param;//联动参数
}JESALM_InputSetParam_Req_t;//配置上报联动参数

#ifdef __cplusplus
}
#endif
#endif // __JES_ALARM_H__
