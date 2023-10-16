/***********************************************************************
 * @file jes_network.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2023-01-03
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2023-. All rights reserved
***********************************************************************/
#ifndef __JES_NETWORK_H__
#define __JES_NETWORK_H__

#include <jnetwork_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jnet_ctx *jnet_hdl_t;

typedef void (*JESNetworkEventCB)(void *hdl, JNetworkEvent_e event, const void *data, int len, void *arg);

//interface start
/**
 * @brief 网络SDK初始化
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jnet_hdl_t JES_Network_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_Network_Init 返回值
 * @return 无
 */
void JES_Network_DeInit(jnet_hdl_t hdl);

/**
 * @brief 注册事件回调
 * @param [in] hdl JES_Network_Init 返回值
 * @param [in] cb 事件回调
 * @param [in] arg 用户参数
 * @return <0 失败，==0 成功
 */
int JES_Network_RegisterEventCB(jnet_hdl_t hdl, JESNetworkEventCB cb, void *arg);

/**
 * @brief 获取网络信息
 * @note 可以获取到设备支持的所有网卡的信息以及正在使用哪个网卡
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [out] list 网卡列表
 * @param [in] bAll true表示获取所有硬件网卡包括未启用的，false表示仅获取正在启用的
 * @param [in] bDefalut 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_Network_GetList(jnet_hdl_t hdl, JNetCardList_t *list, JBOOL bAll, JBOOL bDefault);
/**
 * @brief 配置以太网
 * @note 本接口每次配置一个网卡信息，包括ipv4和ivp6地址以及网卡启动和禁用
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] param 网卡参数，type不可修改
 * @return <0 失败，==0 成功
 */
int JES_Network_SetAddr(jnet_hdl_t hdl, const JNetCard_t *param);


#ifdef __cplusplus
}
#endif
#endif // __JES_NETWORK_H__
