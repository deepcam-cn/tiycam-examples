/***********************************************************************
 * @file jes_mcs.h
     JES_MCS
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-09-05 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JES_MCS_H__
#define __JES_MCS_H__

#include <stdint.h>
#include <jmessage_define.h>


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jmcs_ctx *jmcs_hdl_t;

/**
 * @brief 事件回调
 * @note 如多个事件使用同一个回调，则需要在回调中区分event，如果每个事件独立一个回调则回调中无需关心event
 * @see JES_MCS_SendEvent 
 * @param [in] handle JES_MCS_Init 返回值
 * @param [in] event 订阅的事件
 * @param [in] data 事件数据
 * @param [in] len 事件数据长度
 * @param [in] arg 用户参数
 * @return <0 失败，==0 成功
 */
typedef void (*JESMCSEventCB)(void *handle, JMCSEvent_e event, const char *type, const void *data, int len, void *arg);
/**
 * @brief 配置回调
 * @note reqLen=0表示req为json，reqLen>0表示req为结构体，其他注意事项请参见 JES_MCS_Config
 * @see JES_MCS_Config
 * @param [in] handle JES_MCS_Init 返回值
 * @param [in] req 请求参数
 * @param [in] reqLen 请求参数长度
 * @param [out] resp 返回结果
 * @param [out] respLen resp内存大小
 * @return <0 失败，==0 成功
 */
typedef int (*JESMCSConfigMsgCB)(void *handle, const void *req, int reqLen, void *resp, int respSize, void *arg);

//interface start
//=============================[初始化]===================================
/**
 * @brief MCS 初始化
 * @note MCS 为 Message Center Service 的缩写
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jmcs_hdl_t JES_MCS_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_MCS_Init 返回值
 * @return 无
 */
void JES_MCS_Deinit(jmcs_hdl_t hdl);
//=============================[应用注册]===================================
/**
 * @brief 注册事件联动项
 * @note 接收事件的应用需要使用本接口注册，允许一个应用注册多个联动项
 * @note 联动应用应该自己提供联动配置页面，配置页面路径由configpath参数进行注册，配置页面请参考demo进行开发
 * @note name为linkage的名称，要求为英文且具备自然语言可读性
 * @note name的多语言支持，要求应用提供 jbus_name.mo 文件，其中包含 name 的翻译
 * @note 如：jbus_init("OnvifServer"); 须提供 OnvifServer.mo
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] linkage 联动项ID
 * @param [in] name 联动项名称，要求：英文且具备自然语言可读性，在对应的mo中支持多语言
 * @param [in] configpath 联动项配置页面路径（包括路径和文件名）
 * @return <0 失败，==0 成功
 */
int JES_MCS_RegisterLinkage(jmcs_hdl_t hdl, const char *linkage, const char *name, const char *configpath);
/**
 * @brief 查询联动项列表
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [out] list 联动项列表
 * @return <0 失败，==0 成功
 */
int JES_MCS_GetLinkageList(jmcs_hdl_t hdl, JMCSLinkageList_t *list);

/**
 * @brief 注册事件类型
 * @note 发布事件的应用需要使用本接口注册，允许一个应用注册多个事件
 * @note type要求： 当event=JMCSEVENT_ALARM时，type为报警类型和linkage进行关联联动
 * @note            当event=JMCSEVENT_META时，type为 jbus_name 
 * @note name为type的名称，要求为英文且具备自然语言可读性
 * @note name的多语言支持，要求应用提供 jbus_name.mo 文件，其中包含 name 的翻译
 * @note 如：jbus_init("OnvifServer"); 须提供 OnvifServer.mo
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] event 事件类别
 * @param [in] type 事件类型
 * @param [in] name 联动项名称，要求：英文且具备自然语言可读性，在对应的mo中支持多语言
 * @param [in] configpath 联动项配置页面路径（包括路径和文件名）
 * @return <0 失败，==0 成功
 */
int JES_MCS_RegisterEventType(jmcs_hdl_t hdl, JMCSEvent_e event, const char *type, const char *name);
/**
 * @brief 查询事件类型列表
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [out] list 联动项列表
 * @return <0 失败，==0 成功
 */
int JES_MCS_GetEventTypeList(jmcs_hdl_t hdl, JMCSEventTypeList_t *list);


//=============================[消息转发]===================================
/**
 * @brief 发布事件
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] event 事件
 * @param [in] type 事件类型
 * @param [in] data 数据，根据不同事件而定义
 * @param [in] len 数据长度
 * @return <0 失败，==0 成功
 */
int JES_MCS_PublishEvent(jmcs_hdl_t hdl, JMCSEvent_e event, const char *type, const void *data, int len);
/**
 * @brief 订阅事件
 * @note 允许调用多次本接口，订阅多个事件
 * @note 如多个事件使用同一个回调，则需要在回调中区分event，如果每个事件独立一个回调则回调中无需关心event
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] event 事件类型
 * @param [in] cb 事件接收回调
 * @param [in] arg 用户参数
 * @return <0 失败，==0 成功
 */
int JES_MCS_SubscribeEvent(jmcs_hdl_t hdl, JMCSEvent_e event, JESMCSEventCB cb, void *arg);
/**
 * @brief 配置透传
 * @note 本接口和 JES_MCS_RegisterConfigCB 搭配使用
 * @note 当reqLen=0时，req内容为json，json中必须包含字段 package 用于标识具体应用，赋值为要配置的应用的jbus名称。
 * @note 如： {"package":"mrs","method":"set_param","param":{"param1":"1","param2":2}}
 * @note 当reqLen>0时，req内容为结构体，结构体第一个字段必须为 package ，长度为64字节，赋值为要配置的应用的jbus名称。
 * @note 如：typedef struct {char package[64];uint32_t methodid;int param1;int param2;};
 * @note req为json时候resp也是json，req为结构体时，resp也为结构体
 * @see JES_MCS_RegisterConfigCB
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] req 请求内容
 * @param [in] reqLen 请求内容
 * @param [out] resp 返回参数
 * @param [out] respSize resp内存大小
 * @return <0 失败，>=0 resp真实长度
 * @retval -2 表示不支持即目标 package 不存在或者没有注册 JPKGTYPE_CONFIG_RECV
 */
int JES_MCS_Config(jmcs_hdl_t hdl, const void *req, int reqLen, void *resp, int respSize);
/**
 * @brief 注册配置回调
 * @note 回调接口用于接收 JES_MCS_Config 接口的 req 数据
 * @note 回复结果，请调用 JES_MCS_ConfigReply 接口
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] cb 配置数据回调，返回值：<0失败，>=0为回复数据的实际长度表示成功
 * @param [in] arg 用户参数，回调中返回
 * @return <0 失败，==0 成功
 */
int JES_MCS_RegisterConfigCB(jmcs_hdl_t hdl, JESMCSConfigMsgCB cb, void *arg);

//=============================[布防计划]===================================
/**
 * @brief 获取布防参数
 * @note 布防表示该事件类型的消息会被转发，撤防表示改事件类型的所有消息将被丢弃不会被转发
 * @see JES_MCS_SendEventMsg
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] event 事件类型
 * @param [out] param 布防参数
 * @param [in] bDefault 默认值
 * @return true开启，false关闭
 */
int JES_MCS_GetDefenceParam(jmcs_hdl_t hdl, JMCSDefenceParam_t *param, JBOOL bDefault);
/**
 * @brief 配置布防参数
 * @note 布防表示该事件类型的消息会被转发，撤防表示改事件类型的所有消息将被丢弃不会被转发
 * @see JES_MCS_SendEventMsg
 * @param [in] hdl JES_MCS_Init 返回值
 * @param [in] event 事件类型
 * @param [in] param 布防参数
 * @return <0 失败，==0 成功
 */
int JES_MCS_SetDefenceParam(jmcs_hdl_t hdl, const JMCSDefenceParam_t *param);


#ifdef __cplusplus
}
#endif
#endif // __JES_MCS_H__
