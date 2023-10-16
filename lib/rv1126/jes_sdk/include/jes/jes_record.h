/***********************************************************************
 * @file jes_record.h
 * @author Lucky(lukai@jovision.com)
 * @brief 音视频录像业务 header file
 * @version 0.1
 * @date 2022-11-17
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JES_RECORD_H__
#define __JES_RECORD_H__

#include <jrecord_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jrec_ctx *jrec_hdl_t;

//interface start
/**
 * @brief 初始化
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jrec_hdl_t JES_Record_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_Record_Init 返回值
 * @return 无
 */
void JES_Record_DeInit(jrec_hdl_t hdl);

/**
 * @brief 获取录像参数
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [out] param 参数
 * @param [in] bdefault 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_Record_GetParam(jrec_hdl_t hdl, int chn, JRecParam_t *param, JBOOL bdefault);
/**
 * @brief 配置录像参数
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [in] param 参数
 * @return <0 失败，==0 成功
 */
int JES_Record_SetParam(jrec_hdl_t hdl, int chn, const JRecParam_t *param);

/**
 * @brief 获取录像计划
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [out] plan 参数
 * @return <0 失败，==0 成功
 */
int JES_Record_GetPlan(jrec_hdl_t hdl, int chn, JRecPlan_t *plan);
/**
 * @brief 配置录像计划
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [in] plan 参数
 * @return <0 失败，==0 成功
 */
int JES_Record_SetPlan(jrec_hdl_t hdl, int chn, const JRecPlan_t *plan);

/**
 * @brief 获取当前正在录像的文件
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [out] rec 参数
 * @return <0 失败，==0 成功
 */
int JES_Record_GetRecordingFile(jrec_hdl_t hdl, int chn, JRecordingFile_t *rec);

/**
 * @brief 录像日历检索
 * @note 单次最多查询366条数据（一年），如果查询时间跨度大于一年请分多次查询
 * @note 返回值非 NULL 时，需要外部 free 释放
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [in] start 开始时间，不可以为NULL
 * @param [in] end 结束时间，不可以为NULL
 * @param [out] count 输出记录数量
 * @return 录像日期列表(需外部free)，失败返回NULL
 */
JRecDateItem_t *JES_Record_SearchDate(jrec_hdl_t hdl, int chn, const JTime_t *start, const JTime_t *end, int *count);
/**
 * @brief 录像文件检索
 * @note 单次最多查询1000条数据，如果时间跨度太大，文件太多请分时间段多次查询
 * @note 如果输出参数count等于1000，请使用最后一条数据的 starttime+duration 作为查询条件中的开始时间再次查询
 * @note 返回值非 NULL 时，需要外部 free 释放
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [in] type 录像类型
 * @param [in] start 开始时间
 * @param [in] end 结束时间
 * @param [out] count 输出记录数量
 * @return 录像文件列表(需外部free)，失败返回NULL
 */
JRecFileItem_t *JES_Record_SearchFile(jrec_hdl_t hdl, int chn, JRecType_e type, const JTime_t *start, const JTime_t *end, int *count);

/**
 * @brief 获取联动参数
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] type 事件类型
 * @param [out] param 联动参数
 * @param [in] bDefault 是否获取默认参数
 * @return <0 失败，==0 成功
 */
JBOOL JES_Record_GetLinkParam(jrec_hdl_t hdl, const char *type, JBOOL bDefault);
/**
 * @brief 配置联动参数
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] type 事件类型
 * @param [in] param 联动参数
 * @return <0 失败，==0 成功
 */
int JES_Record_SetLinkParam(jrec_hdl_t hdl, const char *type, JBOOL enable);
/**
 * @brief 事件日历检索
 * @note 单次最多查询366条数据（一年），如果查询时间跨度大于一年请分多次查询
 * @note 返回值非 NULL 时，需要外部 free 释放
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [in] start 开始时间，不可以为NULL
 * @param [in] end 结束时间，不可以为NULL
 * @param [out] count 输出记录数量
 * @return 事件日期列表(需外部free)，失败返回NULL
 */
JRecDateItem_t *JES_Record_SearchEventDate(jrec_hdl_t hdl, int chn, const JTime_t *start, const JTime_t *end, int *count);
/**
 * @brief 事件检索
 * @note 单次最多查询1000条数据，如果时间跨度太大，文件太多请分时间段多次查询
 * @note 如果输出参数count等于1000，请使用最后一条数据的 starttime+duration 作为查询条件中的开始时间再次查询
 * @note 返回值非 NULL 时，需要外部 free 释放
 * @param [in] hdl JES_Record_Init 返回值
 * @param [in] chn 通道号，从0开始
 * @param [in] event 录像类型，-1表示取所有类型，其他取值参见 jmessage_define.h 中 JMCSEvent_e
 * @param [in] type 录像类型，NULL表示取所有类型
 * @param [in] start 开始时间
 * @param [in] end 结束时间
 * @param [out] count 输出记录数量
 * @return 录像文件列表(需外部free)，失败返回NULL
 */
JRecEventItem_t *JES_Record_SearchEvent(jrec_hdl_t hdl, int chn, int event, const char *type, const JTime_t *start, const JTime_t *end, int *count);

#ifdef __cplusplus
}
#endif
#endif // __JES_RECORD_H__
