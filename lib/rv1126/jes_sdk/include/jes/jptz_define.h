/***********************************************************************
 * @file jptz_define.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2023-03-09
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2023-. All rights reserved
***********************************************************************/
#ifndef __JPTZ_DEFINE_H__
#define __JPTZ_DEFINE_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct{
    int iris;  // 光圈状态，取值：0不支持，1检测中，2正常，3异常，下同
    int zoom;  // 变焦状态
    int focus; // 对焦状态
    int HLimit; // 云台水平限位状态
    int VLimit; // 云台垂直限位状态
}JPTZResetStatus_t;


#ifdef __cplusplus
}
#endif
#endif // __JPTZ_DEFINE_H__
