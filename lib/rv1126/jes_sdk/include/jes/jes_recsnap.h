/***********************************************************************
 * @file jes_recsnap.h
 * @author Lucky(lukai@jovision.com)
 * @brief 抓拍业务 header file
 * @version 0.1
 * @date 2022-11-17
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JES_RECSNAP_H__
#define __JES_RECSNAP_H__

#include <jrecord_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jrecsnap_ctx *jrecsnap_hdl_t;

//interface start
/**
 * @brief 初始化
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @note RecSnap 为 record snapshot（记录抓拍）缩写
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jrecsnap_hdl_t JES_RecSnap_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_RecSnap_Init 返回值
 * @return 无
 */
void JES_RecSnap_DeInit(jrecsnap_hdl_t hdl);

/**
 * @brief 抓拍并存储
 * @note 只有调用本接口抓拍的图片才可以被 JES_RecSnap_SearchFile 检索到
 * @param [in] hdl JES_RecSnap_Init 返回值
 * @param [in] chn 通道号
 * @param [in] type 抓拍类型
 * @param [out] fnameOut 文件路径和名称
 * @return <0 失败，==0 成功
 */
int JES_RecSnap_Snapshot(jrecsnap_hdl_t hdl, int chn, JRecType_e type, char fnameOut[128]);
/**
 * @brief 抓拍日历检索
 * @note 单次最多查询366条数据（一年），如果查询时间跨度大于一年请分多次查询
 * @note 返回值非 NULL 时，需要外部 free 释放
 * @param [in] hdl JES_RecSnap_Init 返回值
 * @param [in] chn 通道号
 * @param [in] start 开始时间，不可以为NULL
 * @param [in] end 结束时间，不可以为NULL
 * @param [out] count 输出记录数量
 * @return 录像日期列表(需外部free)，失败返回NULL
 */
JRecDateItem_t *JES_RecSnap_SearchDate(jrecsnap_hdl_t hdl, int chn, const JTime_t *start, const JTime_t *end, int *count);
/**
 * @brief 录像文件检索
 * @note 单次最多查询1000条数据，如果时间跨度太大，文件太多请分时间段多次查询
 * @note 如果输出参数count等于1000，请使用最后一条数据的 starttime+duration 作为查询条件中的开始时间再次查询
 * @note 返回值非 NULL 时，需要外部 free 释放
 * @note 本接口只能检索到 JES_RecSnap_SearchFile 抓拍的图片和内部定时抓拍的图片，自己保存到SD卡中的图片无法被检索到
 * @param [in] hdl JES_RecSnap_Init 返回值
 * @param [in] chn 通道号
 * @param [in] type 录像类型
 * @param [in] start 开始时间
 * @param [in] end 结束时间
 * @param [out] count 输出记录数量
 * @return 录像文件列表(需外部free)，失败返回NULL
 */
JRecFileItem_t *JES_RecSnap_SearchFile(jrecsnap_hdl_t hdl, int chn, JRecType_e type, const JTime_t *start, const JTime_t *end, int *count);




#ifdef __cplusplus
}
#endif
#endif // __JES_RECORD_H__
