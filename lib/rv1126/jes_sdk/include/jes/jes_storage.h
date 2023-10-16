/***********************************************************************
 * @file jes_storage.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2023-02-09
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2023-. All rights reserved
***********************************************************************/
#ifndef __JES_STORAGE_H__
#define __JES_STORAGE_H__

#include <jvtypes.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jsto_ctx *jsto_hdl_t;

typedef enum {
    HDISK_STATUS_NOTFORMAT,  // 未格式化，比如新卡或格式化失败的卡
    HDISK_STATUS_FORMATING,  // 正在格式化
    HDISK_STATUS_NORMAL,     // 正常
    HDISK_STATUS_ABNORMAL,   // 异常，读写异常需要格式化修复或者换卡
} JHDiskStatus_e;
typedef struct{
    uint32_t id;
    char devname[32];
    uint64_t totalBytes;
    uint64_t freeBytes;
    JHDiskStatus_e status;
}JHDiskInfo_t;

//interface start
/**
 * @brief 初始化
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jsto_hdl_t JES_Storage_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_Storage_Init 返回值
 * @return 无
 */
void JES_Storage_DeInit(jsto_hdl_t hdl);
/**
 * @brief 获取磁盘列表
 * @note 返回值需要外部调用 free 释放
 * @param [in] hdl JES_Storage_Init 返回值
 * @param [out] count 磁盘数量
 * @return 成功返回JHDiskInfo_t数组指针，使用完毕需外部free，失败返回NULL
 */
JHDiskInfo_t *JES_Storage_GetDiskList(jsto_hdl_t hdl, int *count);
/**
 * @brief 格式化磁盘
 * @note 异步执行格式化，本接口会立即返回，请调用JES_Storage_GetDiskList查看磁盘状态
 * @param [in] hdl JES_Storage_Init 返回值
 * @param [in] diskid 磁盘id，JHDiskInfo_t中的id
 * @return <0 失败，==0 成功
 */
int JES_Storage_Format(jsto_hdl_t hdl, int diskid);



#ifdef __cplusplus
}
#endif
#endif // __JES_STORAGE_H__
