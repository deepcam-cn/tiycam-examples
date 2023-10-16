/***********************************************************************
 * @file jes_user.h
     JES_USER
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-10-20 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JES_USER_H__
#define __JES_USER_H__

#include <juser_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _juser_ctx *juser_hdl_t;

//interface start
//============================[账号管理]==================================
/**
 * @brief 初始化
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
juser_hdl_t JES_User_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_USER_Init 返回值
 * @return 无
 */
void JES_User_Deinit(juser_hdl_t hdl);
/**
 * @brief 添加账号
 * @note 用户名和密码都仅支持 大小写字母，数字，英文符号
 * @note 密码至少为其中2种类型的组合，长度必须为 8-64 字节
 * @note USER初始化后，存在默认账号admin，密码为空，此账号不可删除
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名，最长支持64字节
 * @param [in] passwd 密码，最长支持64字节
 * @return <0 失败，==0 成功
 * @retval JUSER_ERR_LIMITED 用户数量超出最大值(JUSER_MAX_CNT)
 * @retval JUSER_ERR_EXISTED 用户已存在
 * @retval JUSER_ERR_PASSWD_INVALID 密码无效，详见Remarks
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int JES_User_Add(juser_hdl_t hdl, const char *name, const char *passwd, uint32_t powerid);
/**
 * @brief 删除账号
 * @note 默认账号admin，不可删除
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名，最长支持64字节
 * @return <0 失败，==0 成功
 * @retval JUSER_ERR_PERMISION_DENIED 无权限（删除admin账号时返回）
 * @retval JUSER_ERR_NOTEXIST 账号不存在
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int JES_User_Del(juser_hdl_t hdl, const char *name);
/**
 * @brief 清空所有账号
 * @note 默认账号admin，恢复空密码，不会被删除
 * @param [in] hdl JES_USER_Init 返回值
 * @return <0 失败，==0 成功
 */
int JES_User_Clear(juser_hdl_t hdl);
/**
 * @brief 修改账号密码
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [in] newpasswd 密码
 * @return <0 失败，==0 成功
 * @retval JUSER_ERR_NOTEXIST 账号不存在
 * @retval JUSER_ERR_PASSWD_INVALID 密码无效，详见 JES_User_Add 的 Remarks
 * @retval JUSER_ERR_UNKNOW 其他错误
 * @see JES_User_Add
 */
int JES_User_SetPasswd(juser_hdl_t hdl, const char *name, const char *newpasswd);
/**
 * @brief 修改账号权限
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [in] newpowerid 权限ID
 * @return <0 失败，==0 成功
 * @retval JUSER_ERR_NOTEXIST 账号不存在
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int JES_User_SetPower(juser_hdl_t hdl, const char *name, uint32_t newpowerid);
/**
 * @brief 查询账号列表
 * @note 返回值需要外部调用 free 释放
 * @note 用户信息中的passwd为密文，防止不小心被web等前端接口获取到明文密码
 * @param [in] hdl JES_USER_Init 返回值
 * @param [out] count 账号数量
 * @return 成功返回 JUserInfo_t 数组指针，失败返回NULL
 */
JUserInfo_t *JES_User_GetList(juser_hdl_t hdl, int *count);
/**
 * @brief 查询账号信息
 * @note 本接口可以查询明文密码用于部分协议认证比如：rtsp协议等
 * @note 禁止web等前端接口获取明文密码
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [out] user 账号信息
 * @return <0 失败，==0 成功
 * @retval JUSER_ERR_NOTEXIST 账号不存在
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int JES_User_GetInfo(juser_hdl_t hdl, const char *name, JUserInfo_t *user);
/**
 * @brief 账号认证
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [in] passwd 密码
 * @return <0 失败，>=0 权限ID
 * @retval JUSER_ERR_PASSWD 用户名或密码错误
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int64_t JES_User_Auth(juser_hdl_t hdl, const char *name, const char *passwd);
/**
 * @brief 账号认证
 * @note 本接口使用密文密码，用于远程验证
 * @note 密文密码生成规则：MD5(username€passwd)
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [in] passwd 密码
 * @return <0 失败，>=0 权限ID
 * @retval JUSER_ERR_PASSWD 用户名或密码错误
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int64_t JES_User_AuthMd5(juser_hdl_t hdl, const char *name, const char *passwd);

//============================[密保管理]==================================
/**
 * @brief 配置密保问题
 * @note 密保问题数量固定为3个，认证时全部须全部认证通过
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [in] security 密保信息列表
 * @return <0 失败，==0 成功
 * @retval JUSER_ERR_NOTEXIST 账号不存在
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int JES_User_SetSecurityQuestion(juser_hdl_t hdl, const char *name, const JUserSecurityInfo_t security[JUSER_MAX_SECURITY_CNT]);
/**
 * @brief 查询密保问题
 * @note 密保问题数量固定为3个，认证时全部须全部认证通过
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [in] question 密保问题列表
 * @return <0 失败，==0 成功
 * @retval JUSER_ERR_NOTEXIST 账号不存在
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int JES_User_GetSecurityQuestion(juser_hdl_t hdl, const char *name, JUserSecurityQuestion_t question[JUSER_MAX_SECURITY_CNT]);
/**
 * @brief 校验密保问题
 * @note 密保问题数量固定为3个，认证时全部须全部认证通过
 * @param [in] hdl JES_USER_Init 返回值
 * @param [in] name 用户名
 * @param [in] security 密保信息列表
 * @return <0 失败，==0 成功
 * @return JUSER_ERR_NOTEXIST 账号不存在
 * @retval JUSER_ERR_UNKNOW 其他错误
 */
int JES_User_VerifySecurityQuestion(juser_hdl_t hdl, const char *name, const JUserSecurityInfo_t security[JUSER_MAX_SECURITY_CNT]);

//============================[密码找回]==================================
/**
 * @brief 获取密码错误的错误码
 * @note 错误码可用于找回密码业务
 * @param [in] hdl JES_USER_Init 返回值
 * @return 错误码
 */
uint32_t JES_User_GetPasswdErrorCode(juser_hdl_t hdl);


#ifdef __cplusplus
}
#endif
#endif // __JES_USER_H__
