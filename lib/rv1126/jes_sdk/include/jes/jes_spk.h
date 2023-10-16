/***********************************************************************
 * @file jes_speaker.h
     JES_SPEAKER
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-09-16 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JES_SPEAKER_H__
#define __JES_SPEAKER_H__

#include <stdint.h>
#include <jmss_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jspk_ctx *jspk_hdl_t;

//interface start
/**
 * @brief SPK初始化
 * @note SPK为speaker的缩写
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jspk_hdl_t JES_SPK_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_SPK_Init 返回值
 * @return 无
 */
void JES_SPK_Deinit(jspk_hdl_t hdl);
/**
 * @brief 获取扬声器参数
 * @param [in] hdl JES_SPK_Init 返回值
 * @param [out] param 扬声器参数
 * @param [in] bDefault 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_SPK_GetParam(jspk_hdl_t hdl, JMediaAencParam_t *param, JBOOL bDefault);
/**
 * @brief 设置扬声器参数
 * @note 如果喇叭正在使用中，除音量参数外其他参数均不会立即生效，播放结束后生效
 * @param [in] hdl JES_SPK_Init 返回值
 * @param [out] param 扬声器参数
 * @return <0 失败，==0 成功
 */
int JES_SPK_SetParam(jspk_hdl_t hdl, const JMediaAencParam_t *param);
/**
 * @brief 查询扬声器是否被占用
 * @param [in] hdl JES_SPK_Init 返回值
 * @return 0空闲，>0被占用：1正在广播或对讲，2正在播放文件
 */
int JES_SPK_IsBusy(jspk_hdl_t hdl);
/**
 * @brief 开启广播或对讲
 * @note 广播和对讲优先级相同，如正在进行广播或对讲本接口返回错误号-2
 * @note 广播对讲优先级高于文件播放，如正在播放文件如报警灯，本接口会强行中断文件播放
 * @note 请先调用配置参数接口，在调用本接口，广播或对讲过程中只有音量参数可以实时调解
 * @see JES_SPK_GetParam JES_SPK_SetParam JES_MSS_GetMICParam JES_MSS_SetMICParam
 * @see JES_SPK_Send JES_SPK_Close
 * @param [in] hdl JES_SPK_Init 返回值
 * @return <0 失败，==0 成功
 * @exception -1 未知错误
 * @exception -2 设备正在广播或对讲
 */
int JES_SPK_Open(jspk_hdl_t hdl);
/**
 * @brief 发送数据
 * @note 发送前要调用JES_SPK_Open，发送结束要调用JES_SPK_Close。
 * @note 需要发送者自行控制发送速度
 * @see JES_SPK_Open JES_SPK_Close
 * @param [in] hdl JES_SPK_Init 返回值
 * @param [in] data 数据
 * @param [in] len 长度
 * @return <0 失败，==0 成功
 */
int JES_SPK_Send(jspk_hdl_t hdl, uint8_t *data, int len);
/**
 * @brief 关闭广播或对讲
 * @note 本接口只可以关闭本应用的对讲或广播，其他应用正在进行广播或对讲无法关闭
 * @see JES_SPK_Open JES_SPK_Send
 * @param [in] hdl JES_SPK_Init 返回值
 * @return 无
 */
void JES_SPK_Close(jspk_hdl_t hdl);
/**
 * @brief 播放文件
 * @note 本接口未非阻塞接口
 * @note 如果正在播放文件则会强制停止播放，开始播放新文件，如果要等当前声音播放完成请调用 JES_SPK_IsBusy
 * @note 如果正在广播或对讲则会返回-2
 * @note 播放文件之前请先调用 JES_SPK_GetParam JES_SPK_SetParam 接口配置编码参数
 * @param [in] hdl JES_SPK_Init 返回值
 * @param [in] file 声音文件，绝对路径
 * @return <0 失败，==0 成功
 * @exception -1 未知错误
 * @exception -2 设备忙
 */
int JES_SPK_PlayFile(jspk_hdl_t hdl, const char *file);

#ifdef __cplusplus
}
#endif
#endif // __JES_SPEAKER_H__
