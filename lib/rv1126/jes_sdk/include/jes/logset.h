/***********************************************************************
 * @file logset.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __LOGSET_H__
#define __LOGSET_H__

#include <jlog.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;

typedef void (*LogsetCallback)(const JLogParam_t *param, void *userarg);

/**
 * @brief 初始化
 * @note 本接口主要接受控制台命令发过来的打印日志等级控制，依赖jbus通信
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @param [in] sign 应用标识名称，用于过滤日志消息
 * @param [in] cb 打印日志参数回调，如果使用的是jlog则传NULL即可，内部会调用 jlog_set_param
 * @param [in] userarg 用户参数
 * @return 无
 */
void Logset_Init(jbus_hdl_t jbus, const char *sign, LogsetCallback cb, void *userarg);

#ifdef __cplusplus
}
#endif
#endif // __LOGSET_H__
