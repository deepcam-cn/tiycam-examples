/***********************************************************************
 * @file jlinux_gpio.h
     JLINUX_GPIO
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-07-27 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JLINUX_GPIO_H__
#define __JLINUX_GPIO_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief 配置方向
 * @param num GPIO号
 * @param dir 1输出，0输入
 * @return <0 失败，==0 成功
 */
int jgpio_set_dir(int num, int dir);

/**
 * @brief 读取一位
 * @param num GPIO号
 * @return value of bit
 */
int jgpio_read(int num);

/**
 * @brief 设置一位
 * @param num GPIO号
 * @param value 值0/1
 * @return 0成功，-1失败
 */
int jgpio_write(int num, int value);

/**
 * @brief 读取寄存器的值
 * @param phy_addr 寄存器物理地址
 * @return 寄存器值
 */
uint32_t jgpio_get_reg(uint32_t phy_addr);
/**
 * @brief 写寄存器值
 * @param phy_addr 寄存器物理地址
 * @param value 值
 * @return 0成功，-1失败
 */
int jgpio_set_reg(uint32_t phy_addr, uint32_t value);


#ifdef __cplusplus
}
#endif
#endif // __JLINUX_GPIO_H__
