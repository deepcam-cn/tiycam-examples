/***********************************************************************
 * @file jlinux_pwm.h
     JLINUX_PWM
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-08-22 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JLINUX_PWM_H__
#define __JLINUX_PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif

int jpwm_export(int chip, int num, int period, int minduty, int maxduty);
//duty_percent 为0时候关闭pwm
int jpwm_config(int chip, int num, int duty_percent);
int jpwm_unexport(int chip, int num);

#ifdef __cplusplus
}
#endif
#endif // __JLINUX_PWM_H__
