/***********************************************************************
 * @file jlinux_i2c.h
     JLINUX_I2C
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-08-19 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JLINUX_I2C_H__
#define __JLINUX_I2C_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _i2c_ctx *ji2c_hdl_t;

//适用于连续读写
ji2c_hdl_t ji2c_open(int num, uint32_t devaddr);
int ji2c_read(ji2c_hdl_t i2c, uint32_t regw, uint32_t reg, uint32_t dataw, uint32_t *data);
int ji2c_write(ji2c_hdl_t i2c, uint32_t regw, uint32_t reg, uint32_t dataw, uint32_t *data);
void ji2c_close(ji2c_hdl_t i2c);

//用于单次读写
int ji2c_read_ex(int num, uint32_t dev, uint32_t regw, uint32_t reg, uint32_t dataw, uint32_t *data);
int ji2c_write_ex(int num, uint32_t dev, uint32_t regw, uint32_t reg, uint32_t dataw, uint32_t data);


#ifdef __cplusplus
}
#endif
#endif // __JLINUX_I2C_H__
