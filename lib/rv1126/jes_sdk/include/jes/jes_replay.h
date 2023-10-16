/***********************************************************************
 * @file jes_replay.h
 * @author Lucky(lukai@jovision.com)
 * @brief 音视频回放业务 header file
 * @version 0.1
 * @date 2022-11-17
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JES_REPLAY_H__
#define __JES_REPLAY_H__

#include <stdint.h>
#include <jvtypes.h>
#include <jvmediatypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jrep_ctx *jrep_hdl_t;

typedef enum {
    JREPLAY_EVENT_METADATA,  // 更新元数据，data对应：JReplayDecAttr_t
    JREPLAY_EVENT_FINISHED,  // 播放完成，data为NULL
    JREPLAY_EVENT_MAX
} JReplayEvent_e;
typedef struct{
    int duration;   //文件时长单位秒
    JVMediaVDecAttr_t vdec;
    JVMediaAdecAttr_t adec;
}JReplayDecAttr_t;
typedef void (*JESReplayEventCB)(void *hdl, JReplayEvent_e event, void *data, int len, void *arg);
typedef void (*JESReplayDataCB)(void *hdl, const JVMediaFrame_t *frame, void *arg);

//interface start
/**
 * @brief 打开文件
 * @note 按录像检索的文件名称进行录像回放，Open之后可直接获取数据无需调用Play
 * @note 播放结束通过 JESReplayEventCB 通知结束事件，需要外部调用 JES_Replay_Close 进行关闭
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @param [in] fname 文件名称，全路径名称
 * @param [in] eventcb 事件回调
 * @param [in] datacb 数据回调，可以为NULL，为NULL时请使用 JES_Replay_GetFrame 获取数据
 * @param [in] arg 用户参数，eventcb和datacb中的arg
 * @return 失败返回 NULL， 成功返回 句柄
 * @see JES_Record_SearchFile 
 */
jrep_hdl_t JES_Replay_OpenFile(jbus_hdl_t jbus, const char *fname, JESReplayEventCB eventcb, JESReplayDataCB datacb, void *arg);
/**
 * @brief 打开文件
 * @note 按照时钟时间进行回放，Open之后可直接获取数据无需调用Play
 * @note 播放结束通过 JESReplayEventCB 通知结束事件，需要外部调用 JES_Replay_Close 进行关闭
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @param [in] chn 通道号
 * @param [in] start 开始时间，不可以为NULL
 * @param [in] end 结束时间，不可以为NULL
 * @param [in] eventcb 事件回调
 * @param [in] datacb 数据回调，可以为NULL，为NULL时请使用 JES_Replay_GetFrame 获取数据
 * @param [in] arg 用户参数，eventcb和datacb中的arg
 * @return 失败返回 NULL， 成功返回 句柄
 */
jrep_hdl_t JES_Replay_OpenTime(jbus_hdl_t jbus, int chn, const JTime_t *start, const JTime_t *end, JESReplayEventCB eventcb, JESReplayDataCB datacb, void *arg);
/**
 * @brief 获取帧数据
 * @note 不可以和 JESReplayDataCB 同时使用
 * @param [in] hdl JES_Replay_OpenFile 或 JES_Replay_OpenTime 的返回值
 * @param [out] frame 帧数据
 * @return <0 失败，==0 成功
 */
int JES_Replay_GetFrame(jrep_hdl_t hdl, JVMediaFrame_t *frame);
/**
 * @brief 文件定位
 * @note 仅用于 JES_Replay_OpenFile 
 * @param [in] hdl JES_Replay_OpenFile 的返回值
 * @param [in] offset 相对偏移时间（秒），文件开头为0
 * @return <0 失败，==0 成功
 */
int JES_Replay_SeekFile(jrep_hdl_t hdl, uint32_t offset);
/**
 * @brief 时间定位
 * @note 仅用于 JES_Replay_OpenTime 
 * @param [in] hdl JES_Replay_OpenTime 的返回值
 * @param [in] time 时间（墙钟时间）需介于 JES_Replay_OpenTime 的start和end之间
 * @return <0 失败，==0 成功
 */
int JES_Replay_SeekTime(jrep_hdl_t hdl, const JTime_t *time);
/**
 * @brief 暂停
 * @param [in] hdl JES_Replay_OpenFile 或 JES_Replay_OpenTime 的返回值
 * @return <0 失败，==0 成功
 */
int JES_Replay_Pause(jrep_hdl_t hdl);
/**
 * @brief 播放
 * @note 默认1倍速播放
 * @param [in] hdl JES_Replay_OpenFile 或 JES_Replay_OpenTime 的返回值
 * @return <0 失败，==0 成功
 */
int JES_Replay_Play(jrep_hdl_t hdl);
/**
 * @brief 配置播放速度
 * @note 倒放时仅播放I帧
 * @param [in] hdl JES_Replay_OpenFile 或 JES_Replay_OpenTime 的返回值
 * @param [in] speed 播放速度,取值：1/16,1/8,1/4,1/2,0,1,2,4,8,16。负值为倒放
 * @return <0 失败，==0 成功
 */
int JES_Replay_SetSpeed(jrep_hdl_t hdl, float speed);
/**
 * @brief 单步播放
 * @note 倒放时仅播放I帧
 * @param [in] hdl JES_Replay_OpenFile 或 JES_Replay_OpenTime 的返回值
 * @param [in] forward true正向播放，false倒放
 * @return <0 失败，==0 成功
 */
int JES_Replay_Step(jrep_hdl_t hdl, JBOOL forward);
/**
 * @brief 关闭播放器
 * @param [in] hdl JES_Replay_OpenFile 或 JES_Replay_OpenTime 的返回值
 * @return <0 失败，==0 成功
 */
void JES_Replay_Close(jrep_hdl_t hdl);


#ifdef __cplusplus
}
#endif
#endif // __JES_REPLAY_H__
