/***********************************************************************
 * @file jes_onvifserver.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2022-12-27
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JES_ONVIFSERVER_H__
#define __JES_ONVIFSERVER_H__

#include <jvtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define PKG_JVOVS "Jovision_OnvifServer"

//本应用使用MCS的Config接口进行配置
//@see jes_mcs.h JES_MCS_Config 接口文档

//mcs config interface start

typedef enum {
    JESOVS_CMD_GETPARAM = 0x0, // 获取Onvif参数
    JESOVS_CMD_GETPARAM_DEF,   // 获取默认Onvif参数
                               //     @req:JESOVS_Config_t
                               //     @resp:JESOnvifSvrParam_t
                               //     @ret:<0 失败，==0 成功
    JESOVS_CMD_SETPARAM,       // 配置Onvif参数
                               //     @req:JESOVS_SetParam_Req_t
                               //     @resp:None
                               //     @ret:<0 失败，==0 成功
    JESOVS_CMD_MAX
} JESOVSCmd_e;

typedef struct{
    JBOOL enable;       //onvif 服务开关
    JBOOL discovery;    //onvif 搜索开关，关闭后只能通过IP地址连接
    JBOOL jovisionFlag; //onvif 搜索协议中带jovision标识让中维NVR搜不到，JFALSE去掉标识
    short rtspPort;     //rtspPort
    JBOOL ipAdapt;      //onvif 搜索IP自适应
    struct Protocol_t{
        JBOOL http;     //onvif 使用http通信
        JBOOL https;    //onvif 使用https通信
    }protocol;          //传输协议，http和https均为true时使用http
    struct AuthType_t{
        JBOOL digestMD5;    //启用MD5认证
        JBOOL digestSHA256; //启用SHA256认证
        JBOOL wsse;         //启用wsse认证
    }authType;          //认证类型，都启用时以客户端携带为准
    char reserve[128];
}JESOnvifSvrParam_t;
typedef struct{
    char package[64];//固定为宏定义： PACKAGE_ALARMMANAGER
    JESOVSCmd_e cmd;//指令
}JESOVS_Config_t;//配置接口信息
typedef struct{
    JESOVS_Config_t config;
    JESOnvifSvrParam_t param;
}JESOVS_SetParam_Req_t;

#ifdef __cplusplus
}
#endif
#endif // __JES_ONVIFSERVER_H__
