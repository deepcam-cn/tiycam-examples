/***********************************************************************
 * @file juser_define.h
     JUSER_DEFINE
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-10-20 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JUSER_DEFINE_H__
#define __JUSER_DEFINE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define JUSER_ERR_NO                   0 ///< 无错误
#define JUSER_ERR_UNKNOW              -1 ///< 未知错误
#define JUSER_ERR_EXISTED             -2 ///< 用户已存在
#define JUSER_ERR_LIMITED             -3 ///< 数量超出了限制
#define JUSER_ERR_NOTEXIST            -4 ///< 用户不存在
#define JUSER_ERR_PASSWD              -5 ///< 密码错误
#define JUSER_ERR_PERMISION_DENIED    -6 ///< 无权限
#define JUSER_ERR_PARAM_INVALID       -7 ///< 参数错误
#define JUSER_ERR_PASSWD_INVALID      -8 ///< 密码无效
#define JUSER_ERR_LOCKED              -9 ///< 用户已锁定

#define JUSER_MAX_CNT 20
#define JUSER_MAX_SECURITY_CNT 3



//typdef start
typedef struct{
    char name[64];    //用户名
    char passwd[256]; //用户密码
    uint32_t powerid; //用户权限ID
}JUserInfo_t;//用户账号信息
typedef struct{
    char question[64];//密保问题
    char answer[256];//密保答案
}JUserSecurityInfo_t;//用户密保信息
typedef struct{
    char question[64];//密保问题
}JUserSecurityQuestion_t;//用户密保问题
typedef struct
{
    char token[32]; //登录token
    int maxErrorNum;    //最大登陆错误次数
    int maxLockSec;     //最大锁定时间
    int curErrorNum;    //当前登陆错误次数
    int curLockSec;     //当前锁定时间
}JUserLoginResult_t;//登录结果


#ifdef __cplusplus
}
#endif
#endif // __JUSER_DEFINE_H__
