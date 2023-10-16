/***********************************************************************
 * @file jboard.h
     JBOARD
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-07-21 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JBOARD_H__
#define __JBOARD_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief 获取productid
 * @note productid由cpuid生成和硬件绑定且具有唯一性
 * @note 第一次调用本接口，内部会初始化所有配置的寄存器
 * @note 并把一些固定设备信息存储到/etc/jes.d/board.conf中供其他进程使用，内容详见《硬件配置指南》
 * @note 本接口会在BAS服务中第一次被调用
 * @param [out] productid 16位字符+\0
 * @return <0 失败，==0 成功
 */
int jboard_get_productid(char productid[17]);
/**
 * @brief 读取加密芯片数据
 * @param [out] encryptdata 加密芯片内部数据
 * @return <0 失败，==0 成功
 */
int jboard_read_encryptdata(char encryptdata[256]);
/**
 * @brief 写入加密芯片数据
 * @note 最大支持256个字节
 * @param [in] data 数据
 * @param [in] len 长度
 * @return <0 失败，==0 成功
 */
int jboard_write_encryptdata(uint8_t *data, int len);

/**
 * @brief 配置产测参数
 * @note 保存到 /factory/production.json 中，有则修改无则添加，目前仅支持单层json结构
 * @note 也可根据 production.json 定义自行实现配置接口
 * @param [in] key key值
 * @param [in] value value值，必须是字符串，不要超过256字节
 * @return <0 失败，==0 成功
 */
int jboard_set_production_value(const char *key, const char *value);
int jboard_set_production_value_int(const char *key, int value);
/**
 * @brief 获取产测参数
 * @note 从 /factory/production.json 中读取，目前仅支持单层json结构
 * @note 也可根据 production.json 定义自行实现解析接口
 * @param [in] key key值
 * @param [out] value value值
 * @param [in] valuesize value内存大小
 * @return <0 失败，==0 成功
 */
int jboard_get_production_value(const char *key, char *value, int valuesize);
int jboard_get_production_value_int(const char *key, int defval);



#ifdef __cplusplus
}
#endif
#endif // __JBOARD_H__
