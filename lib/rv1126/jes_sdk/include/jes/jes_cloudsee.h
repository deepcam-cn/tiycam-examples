/***********************************************************************
 * @file jes_cloudsee.h
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2023-04-21 V1.0    cxb,cxb@jovision.com   Create
 *
 * @Copyright (C)  2023  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JES_CLOUDSEE_H__
#define __JES_CLOUDSEE_H__

#include <stdint.h>
#include <jvtypes.h>


#ifdef __cplusplus
extern "C"
{
#endif

#define PACKAGE_CLOUDSEE "Jovision_CloudSee"
#define CLOUDSEE_ALARM_LINK_MAX 64
#define CLOUDSEE_LINK_TYPE_ALARM 1 //报警
#define CLOUDSEE_LINK_TYPE_SMART 2 //智能事件

//本应用使用MCS的Config接口进行配置
//@see jes_mcs.h JES_MCS_Config 接口文档

//mcs config interface start
typedef enum {
    //=============================[参数配置]===================================
    JES_CLOUDSEE_CMD_GETPARAM = 0x0,       // 获取云视通参数
    JES_CLOUDSEE_CMD_GETPARAM_DEF,          // 获取默认云视通参数
                                            //     @req:JESCloudseeConfig_t
                                            //     @resp:JESCloudSeeParam_t
                                            //     @ret:<0 失败，==0 成功
    JES_CLOUDSEE_CMD_SETPARAM,               // 配置云视通参数
                                            //     @req:JESCloudseeSetParamReq_t
                                            //     @resp:None
                                            //     @ret:<0 失败，==0 成功
    JES_CLOUDSEE_CMD_PUBLIC_GETPARAM,       // 获取公有云参数
    JES_CLOUDSEE_CMD_PUBLIC_GETPARAM_DEF,   // 获取默认公有云参数
                                            //     @req:JESCloudseeConfig_t
                                            //     @resp:JESCloudSeePublicParam_t
                                            //     @ret:<0 失败，==0 成功
    JES_CLOUDSEE_CMD_PUBLIC_SETPARAM,       // 配置公有云参数
                                            //     @req:JESCloudseeSetPublocParamReq_t
                                            //     @resp:None
                                            //     @ret:<0 失败，==0 成功
    JES_CLOUDSEE_CMD_GETONLINE_STATUS,      // 获取在线状态
                                            //     @req:JESCloudseeGetOnlineStatusReq_t
                                            //     @resp:None
                                            //     @ret:<0 失败，==1 在线 ==2不在线
    JES_CLOUDSEE_CMD_GETVERIFCATIONCODE,    // 获取验证码(VC值)
                                            //     @req:JESCloudseeConfig_t
                                            //     @resp:char[64]
                                            //     @ret:<0 失败，==0 成功
    JES_CLOUDSEE_CMD_GETLINKLIST,           // 获取联动列表
                                            //     @req:JESCloudseeConfig_t
                                            //     @resp:JESCloudseeLinkList_t
                                            //     @ret:<0 失败，==0 成功
    JES_CLOUDSEE_CMD_SETLINKPARAM,           // 设置联动参数
                                            //     @req:JESCloudseeSetLinkParam_t
                                            //     @resp:None
                                            //     @ret:<0 失败，==0 成功
    JES_CLOUDSEE_CMD_MAX
} JES_CLOUDSEE_CMD_e; // 指令类型

typedef enum {
    SERVER_TYPE_CLOSE = -1, // 关闭
    SERVER_TYPE_PUBLIC,    // 公有云
    SERVER_TYPE_PRIVATE,   // 私有云
    SERVER_TYPE_MAX,
}JESCloudSeeServerType_e;

typedef struct
{
    char serverUrl[128];//云服务地址
}JESCloudSeeServerParam_t;

typedef struct{
    JBOOL enable;       //服务开关
    JBOOL onlineEnable; //上线使能
    JBOOL smartOnline;  //智能上下线
    int port;           //云视通传输端口
    char reserve[256];      // 预留扩展使用
}JESCloudSeeParam_t;//云视通配置信息

typedef struct{
    char linkName[64];//联动报警明
    JBOOL bLink;
    int type;//CLOUDSEE_LINK_TYPE_
}JESCloudseeLinkParam_t;

typedef struct{
    JESCloudseeLinkParam_t linkList[CLOUDSEE_ALARM_LINK_MAX];
}JESCloudseeLinkList_t;

typedef struct{
    JESCloudSeeServerType_e enableIdx;//公有云和私有云只能打开一个，这个是打开的索引
    JESCloudSeeServerParam_t serverParam[SERVER_TYPE_MAX];
    char reserve[256];      // 预留扩展使用
}JESCloudSeePublicParam_t;//公有云配置信息

typedef struct{
    char package[64];//固定为宏定义： PACKAGE_CLOUDSEE
    JES_CLOUDSEE_CMD_e cmd;//指令
}JESCloudseeConfig_t;//配置接口信息

typedef struct{
    JESCloudseeConfig_t config;//配置接口信息
    JESCloudSeeParam_t param;
}JESCloudseeSetParamReq_t;

typedef struct{
    JESCloudseeConfig_t config;//配置接口信息
    JESCloudSeePublicParam_t param;
}JESCloudseeSetPublocParamReq_t;

typedef struct{
    JESCloudseeConfig_t config;//配置接口信息
    int type;// 1云视通 2公有云
}JESCloudseeGetOnlineStatusReq_t;

typedef struct{
    JESCloudseeConfig_t config;//配置接口信息
    JESCloudseeLinkParam_t param;
}JESCloudseeSetLinkParam_t;

#ifdef __cplusplus
}
#endif
#endif // __JES_COUDSEE_H__
