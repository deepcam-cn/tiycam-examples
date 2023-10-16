/***********************************************************************
 * @file jes_mss.h
     JES_MSS
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-07-21 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JES_MSS_H__
#define __JES_MSS_H__

#include <jmss_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jmss_ctx *jmss_hdl_t;
typedef struct _jmss_stm_ctx jmss_stm_t;
typedef struct _jmss_osd_ctx jmss_osd_t;
typedef struct _jmss_raw_ctx jmss_raw_t;


typedef void (*JESMSSEventCB)(void *handle, JMSSEvent_e event, const void *data, int len, void *arg);
typedef void (*JESMSSDataCB)(void *handle, const char *devid, int channel, int substream, const JVMediaFrame_t *frame, void *arg);

//interface start
//===============================[初始化]==============================================
/**
 * @brief MSS初始化
 * @note MSS为Media Source Service的缩写
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jmss_hdl_t JES_MSS_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_MSS_Init 返回值
 * @return 无
 */
void JES_MSS_Deinit(jmss_hdl_t hdl);
//===============================[直播业务]==============================================
/**
 * @brief 打开直播流
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] deviceid 设备ID，对于NVR和IPC来说传NULL即可
 * @param [in] channel 通道ID，从0开始
 * @param [in] substream 子码流ID，从0开始，-1表示抓拍流，如不支持抓拍传-1返回NULL
 * @return <0 失败，==0 成功
 */
jmss_stm_t *JES_MSS_StreamOpen(jmss_hdl_t hdl, const char *deviceid, int channel, int substream);
/**
 * @brief 关闭直播流
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @return 无
 */
void JES_MSS_StreamClose(jmss_stm_t *ctx);
/**
 * @brief 配置事件回调
 * @note hdl JES_MSS_StreamOpen 返回值
 * @param [in] cb 事件通知回调
 * @param [in] arg 用户参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_StreamRegisterEventCB(jmss_stm_t *ctx, JESMSSEventCB cb, void *arg);
/**
 * @brief 插入I帧
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @return <0 失败，==0 成功
 */
int JES_MSS_StreamInsertIDR(jmss_stm_t *ctx);
/**
 * @brief 获取解码参数
 * @note 本接口获取当前的解码参数，当解码参数发生改变时会通过 JESMSSEventCB 回调主动通知给应用
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @param [out] attr 音视频解码参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_StreamGetDecodeAttr(jmss_stm_t *ctx, JVMediaDecodeAttr_t *attr);
/**
 * @brief 读取一帧数据
 * @note 此接口和 JES_MSS_StreamRegisterCallback 只能使用一种方式，不支持同时使用
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @param [out] frame 帧数据，其中的buffer无需释放，其指向的内容缓存满了后会被覆盖
 * @return <0 失败，==0 成功
 */
int JES_MSS_StreamGetFrame(jmss_stm_t *ctx, JVMediaFrame_t *frame);
/**
 * @brief 读取最新一帧数据
 * @note 本接口和 JES_MSS_StreamGetFrame 使用方式一致，只是本接口每次都获取最新一帧数据，而不是顺序读取
 * @note 可用于从 MJEGP 流中抓拍，每次都获取最新的图片
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @param [out] frame 帧数据，其中的buffer无需释放，其指向的内容缓存满了后会被覆盖
 * @return <0 失败，==0 成功
 */
int JES_MSS_StreamGetLastFrame(jmss_stm_t *ctx, JVMediaFrame_t *frame);
/**
 * @brief 注册数据回调
 * @note 此接口和 JES_MSS_StreamGetFrame 只能使用一种方式，不支持同时使用
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @param [in] cb 数据回调
 * @param [in] arg 用户参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_StreamRegisterDataCB(jmss_stm_t *ctx, JESMSSDataCB cb, void *arg);


//===============以下接口仅IPC支持，NVR请使用其通道参数配置接口=============================
//===============================[参数配置]==============================================
/**
 * @brief 获取视频编码参数
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @param [in] stream 流id，JES_MSS_GetLiveStream 或 JES_MSS_GetSnapStream返回值
 * @param [out] param 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetVencParam(jmss_hdl_t hdl, int stream, JMediaVencParam_t *param, JBOOL bDefault);
/**
 * @brief 配置视频编码参数
 * @param [in] ctx JES_MSS_StreamOpen 返回值
 * @param [in] stream 流id，JES_MSS_GetLiveStream 或 JES_MSS_GetSnapStream返回值
 * @param [in] param 编码参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetVencParam(jmss_hdl_t hdl, int stream, JMediaVencParam_t *param);
/**
 * @brief 获取音频输入参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] param 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetMICParam(jmss_hdl_t hdl, JMediaAencParam_t *param, JBOOL bDefault);
/**
 * @brief 配置音频输入参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] param 编码参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetMICParam(jmss_hdl_t hdl, const JMediaAencParam_t *param);
/**
 * @brief 获取ROI参数
 * @note ROI 感兴趣区域
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] param 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetRoiParam(jmss_hdl_t hdl, JMediaRoi_t *param, JBOOL bDefault);
/**
 * @brief 配置ROI参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] param 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetRoiParam(jmss_hdl_t hdl, JMediaRoi_t *param);
/**
 * @brief 获取视频处理参数
 * @note 镜像、翻转、旋转，参数对所有码流生效
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] param 输出视频处理参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetVpsParam(jmss_hdl_t hdl, JMediaVpsParam_t *param, JBOOL bDefault);
/**
 * @brief 配置视频处理参数
 * @note 镜像、翻转、旋转，参数对所有码流生效
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] param 视频处理参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetVpsParam(jmss_hdl_t hdl, JMediaVpsParam_t *param);
/**
 * @brief 获取OSD参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] param 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetOSDParam(jmss_hdl_t hdl, JMediaOsdParam_t *param, JBOOL bDefault);
/**
 * @brief 配置OSD参数
 * @note osd坐标值请使用 JMSS_TO_REFVAL 进行坐标转换
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] param 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetOSDParam(jmss_hdl_t hdl, const JMediaOsdParam_t *param);
/**
 * @brief 配置OSD闪烁
 * @note 时间和设备名称OSD闪烁，主要用于提示报警
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] enable 是否闪烁
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetOSDFlicker(jmss_hdl_t hdl, JBOOL enable);
/**
 * @brief 获取图像库版本号
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] version 输出参数，使用64字节即可
 * @param [in] size version大小
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetISPVersion(jmss_hdl_t hdl, char *version, int size);
/**
 * @brief 获取图像基础参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] attr 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetISPAttr(jmss_hdl_t hdl, JMediaISPAttr_t *attr, JBOOL bDefault);
/**
 * @brief 配置图像基础参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] attr 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetISPAttr(jmss_hdl_t hdl, const JMediaISPAttr_t *attr);
/**
 * @brief 获取图像曝光参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] attr 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetISPAEAttr(jmss_hdl_t hdl, JMediaISPAE_t *attr, JBOOL bDefault);
/**
 * @brief 配置图像曝光参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] attr 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetISPAEAttr(jmss_hdl_t hdl, const JMediaISPAE_t *attr);
/**
 * @brief 获取白平衡参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] attr 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetISPWBAttr(jmss_hdl_t hdl, JMediaISPWb_t *attr, JBOOL bDefault);
/**
 * @brief 配置白平衡参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] attr 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetISPWBAttr(jmss_hdl_t hdl, const JMediaISPWb_t *attr);
/**
 * @brief 获取图像宽动态参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] attr 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetISPWdrAttr(jmss_hdl_t hdl, JMediaISPWdrParam_t *attr, JBOOL bDefault);
/**
 * @brief 配置图像宽动态参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] attr 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetISPWdrAttr(jmss_hdl_t hdl, const JMediaISPWdrParam_t *attr);
/**
 * @brief 获取图像夜视切换参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] attr 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetISPDayNightAttr(jmss_hdl_t hdl, JMediaISPDayNightParam_t *attr, JBOOL bDefault);
/**
 * @brief 配置图像夜视切换参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] attr 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetISPDayNightAttr(jmss_hdl_t hdl, const JMediaISPDayNightParam_t *attr);
/**
 * @brief 获取图像高级参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [out] attr 输出参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_GetISPAdvanceAttr(jmss_hdl_t hdl, JMediaISPAdvancedAttr_t *attr, JBOOL bDefault);
/**
 * @brief 配置图像高级参数
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] attr 配置参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetISPAdvanceAttr(jmss_hdl_t hdl, const JMediaISPAdvancedAttr_t *attr);
/**
 * @brief 通知ISP库灯光参数
 * @note 当外部控制白光灯时，需使用本接口通知图像库当前灯光使用情况，图像库进行图像参数优化防止灯光对图像参数不良影响
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] light 灯光模式：0关闭，1开启白光灯
 * @param [in] freq 灯光闪烁频率，1低频，2中频，3高频
 * @return <0 失败，==0 成功
 */
int JES_MSS_SetISPLightParam(jmss_hdl_t hdl, int light, int freq);

//===============================[OSD叠加业务]==============================================
/**
 * @brief 打开OSD图层
 * @note 每个应用尽量创建一个图层使用，图层总数有限
 * @param [in] hdl JES_MSS_Init 返回值
 * @return 成功返回图层句柄，失败返回NULL
 */
jmss_osd_t *JES_MSS_OsdLayerOpen(jmss_hdl_t hdl);
/**
 * @brief 关闭OSD图层
 * @note 不使用的图层必须主动关闭，否则该图层内容会一直存在
 * @param [in] ctx JES_MSS_OsdLayerOpen 返回值
 * @return 无
 */
void JES_MSS_OsdLayerClose(jmss_osd_t *ctx);
/**
 * @brief 绘制OSD图层
 * @param [in] ctx JES_MSS_OsdLayerOpen 返回值
 * @param [in] region 绘制的区域内容
 * @return 无
 */
void JES_MSS_OsdLyaerDraw(jmss_osd_t *ctx, const JMediaOsdRegions_t *region);

//===============================[原始数据业务]==============================================
/**
 * @brief 打开原始数据通道
 * @param [in] hdl JES_MSS_Init 返回值
 * @param [in] width 分辨率宽
 * @param [in] height 分辨率高
 * @param [in] type 数据格式类型：不同芯片可能支持不同请根据具体芯片确定，不支持时返回失败
 * @return 成功返回图层句柄，失败返回NULL
 */
jmss_raw_t *JES_MSS_RawOpen(jmss_hdl_t hdl, int width, int height, JMediaRawFrameType_e type);
/**
 * @brief 关闭原始数据通道
 * @note 不使用的数据通道需要主动关闭
 * @param [in] ctx JES_MSS_RawOpen 返回值
 * @return 无
 */
void JES_MSS_RawClose(jmss_raw_t *ctx);
/**
 * @brief 获取一帧原始数据
 * @note 本接口和 JES_MSS_RawRegisterCallback 选择一种方式使用，不支持同时使用
 * @note 本接口帧数据内容位于OS内存中，注意和 JES_MSS_RawGetPhyAddr 的差异
 * @note 帧缓存为循环使用，缓存10帧超出后会覆盖最早帧，应用端使用速度需要快于此速度，如太慢需拷贝一份进行使用
 * @param [in] ctx JES_MSS_RawOpen 返回值
 * @param [out] frame 原始数据帧 
 * @return <0 失败，==0 成功
 */
int JES_MSS_RawGetFrame(jmss_raw_t *ctx, JVMediaFrame_t *frame);
/**
 * @brief 获取最新一帧原始数据
 * @note 本接口和 JES_MSS_RawRegisterCallback 选择一种方式使用，不支持同时使用
 * @note 本接口帧数据内容位于OS内存中，注意和 JES_MSS_RawGetPhyAddr 的差异
 * @note 帧缓存为循环使用，缓存10帧超出后会覆盖最早帧，应用端使用速度需要快于此速度，如太慢需拷贝一份进行使用
 * @param [in] ctx JES_MSS_RawOpen 返回值
 * @param [out] frame 原始数据帧 
 * @return <0 失败，==0 成功
 */
int JES_MSS_RawGetLastFrame(jmss_raw_t *ctx, JVMediaFrame_t *frame);
/**
 * @brief 注册原始数据回调
 * @note 本接口和 JES_MSS_RawGetFrame 选择一种方式使用，不支持同时使用
 * @note 本接口帧数据内容位于OS内存中，注意和 JES_MSS_RawGetPhyAddr 的差异
 * @param [in] ctx JES_MSS_RawOpen 返回值
 * @param [in] cb 回调，回调参数：channel和substream无用固定为0
 * @param [in] arg 用户参数
 * @return <0 失败，==0 成功
 */
int JES_MSS_RawRegisterCallback(jmss_raw_t *ctx, JESMSSDataCB cb, void *arg);
/**
 * @brief 获取原始数据帧物理地址
 * @note 使用完毕需要调用 JES_MSS_RawFreePhyAddr 接口进行释放
 * @note 服务端会缓存10帧数据，缓存满之后会主动释放，应用端使用速度需要快于此速度
 * @param [in] ctx JES_MSS_RawOpen 返回值
 * @param [out] frame 帧数据
 * @return <0 失败，==0 成功
 */
int JES_MSS_RawGetPhyAddr(jmss_raw_t *ctx, JVMediaRawFrame_t *frame);
/**
 * @brief 释放原始数据帧物理地址
 * @param [in] ctx JES_MSS_RawOpen 返回值
 * @param [in] frame 帧数据
 * @return <0 失败，==0 成功
 */
int JES_MSS_RawFreePhyAddr(jmss_raw_t *ctx, const JVMediaRawFrame_t *frame);




#ifdef __cplusplus
}
#endif
#endif // __JES_MSS_H__
