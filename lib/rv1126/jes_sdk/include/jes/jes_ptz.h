/***********************************************************************
 * @file jes_ptz.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2022-12-27
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JES_PTZ_H__
#define __JES_PTZ_H__

#include <jvtypes.h>
#include <jptz_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jptz_ctx *jptz_hdl_t;



//interface start
/**
 * @brief 初始化
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jptz_hdl_t JES_PTZ_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_PTZ_Init 返回值
 * @return 无
 */
void JES_PTZ_DeInit(jptz_hdl_t hdl);

/**
 * @brief PTZ复位
 * @param [in] hdl jptz_init 返回值
 * @return <0 失败，==0 成功
 */
int JES_PTZ_Reset(jptz_hdl_t hdl);
/**
 * @brief PTZ复位
 * @param [in] hdl jptz_init 返回值
 * @param [out] status 状态
 * @return <0 失败，==0 成功
 */
int JES_PTZ_GetResetStatus(jptz_hdl_t hdl, JPTZResetStatus_t *status);
/**
 * @brief 云台开始转动
 * @param [in] hdl jptz_init 返回值
 * @param [in] left >0向左<0向右，绝对值表示速度，0表示不动,-255~255
 * @param [in] up >0向上<0向下，绝对值表示速度，0表示不动,-255~255
 * @return <0 失败，==0 成功
 */
int JES_PTZ_MoveStart(jptz_hdl_t hdl, int left, int up);
/**
 * @brief 停止云台转动
 * @param [in] hdl jptz_init 返回值
 * @return <0 失败，==0 成功
 */
int JES_PTZ_MoveStop(jptz_hdl_t hdl);
/**
 * @brief 获取运动状态
 * @param [in] hdl jptz_init 返回值
 * @return true正在转动，PTZ均处于停止状态
 */
JBOOL JES_PTZ_IsMoving(jptz_hdl_t hdl);
/**
 * @brief 手动变焦（变倍）
 * @param [in] hdl jptz_init 返回值
 * @param [in] zoomin >0拉进（放大），<0（推远）缩小，绝对值表示速度：-255~255
 * @param [in] speed 变焦速度，0~255
 * @return <0 失败，==0 成功
 */
int JES_PTZ_ZoomStart(jptz_hdl_t hdl, int zoomin);
/**
 * @brief 停止变焦（变倍）
 * @param [in] hdl jptz_init 返回值
 * @return <0 失败，==0 成功
 */
int JES_PTZ_ZoomStop(jptz_hdl_t hdl);
/**
 * @brief 手动对焦（调焦）
 * @param [in] hdl jptz_init 返回值
 * @param [in] near >0拉近，<0拉远，绝对值表示速度：-255~255
 * @return <0 失败，==0 成功
 */
int JES_PTZ_FocusStart(jptz_hdl_t hdl, int near);
/**
 * @brief 停止对焦（调焦）
 * @param [in] hdl jptz_init 返回值
 * @return <0 失败，==0 成功
 */
int JES_PTZ_FocusStop(jptz_hdl_t hdl);
/**
 * @brief 调节光圈
 * @param [in] hdl jptz_init 返回值
 * @param [in] open >0扩大，<0缩小，绝对值表示速度：-255~255
 * @return <0 失败，==0 成功
 */
int JES_PTZ_IrisStart(jptz_hdl_t hdl, int open);
/**
 * @brief 停止光圈
 * @param [in] hdl jptz_init 返回值
 * @return <0 失败，==0 成功
 */
int JES_PTZ_IrisStop(jptz_hdl_t hdl);


#ifdef __cplusplus
}
#endif
#endif // __JES_PTZ_H__
