/***********************************************************************
 * @file tlvtype.h
     TLVTYPE
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-06-23 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __TLVTYPE_H__
#define __TLVTYPE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define TLV_MAX_POINTS_CNT 10       //规则区域最大点个数10，即最多支持10边形
typedef struct{
    uint16_t w;
    uint16_t h;
}TLVSize_t;
typedef struct{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
}TLVRect_t;
typedef struct{
    uint16_t x;
    uint16_t y;
}TLVPoint_t;
typedef struct{
    uint8_t count;
    TLVPoint_t points[TLV_MAX_POINTS_CNT];
}TLVRuleArea_t;
typedef struct{
    uint16_t id;
    TLVRect_t rect;
}TLVObjArea_t;


#ifdef __cplusplus
}
#endif
#endif // __TLVTYPE_H__
