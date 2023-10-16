/***********************************************************************
 * @file jes_bas.h
     JES_BAS
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-10-12 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JES_BAS_H__
#define __JES_BAS_H__

#include <jbase_define.h>
#include <jlang_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _jbus_ctx *jbus_hdl_t;
typedef struct _jbas_ctx *jbas_hdl_t;

/**
 * @brief 系统通知回调
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] name 系统环境变量的名称
 * @param [in] value 系统环境变量的值
 * @param [in] arg 用户参数
 * @return 无
 */
typedef void (*JESBASLocaleCB)(void *handle, const char *name, const char *value, void *arg);

//interface start
//=================================[初始化]=================================
/**
 * @brief BAS 初始化
 * @note BAS 为 Base Service 的缩写
 * @note jbus_init 位于 jbus.h 中，每个进程只可以调用一次 jbus_init
 * @param [in] jbus jbus_init 的返回值
 * @return 失败返回 NULL， 成功返回 句柄
 */
jbas_hdl_t JES_BAS_Init(jbus_hdl_t jbus);
/**
 * @brief 去初始化
 * @param [in] hdl JES_BAS_Init 返回值
 * @return 无
 */
void JES_BAS_Deinit(jbas_hdl_t hdl);

//=================================[系统通知]=================================
/**
 * @brief 配置或获取地域信息
 * @note 当系统语言、时区等发生变化时，调用本接口可以实时修改本程序的环境变量，以保证多语言、localtime等正常
 * @note 如果用户不关系这些变化，回调配置为NULL即可，sdk内部会自动修改环境变量
 * @note 目前支持通知的环境变量：TZ(时区),LANGUAGE(语言),NAME(设备名称)
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] cb 回调
 * @param [in] arg 用户参数
 * @return 无
 */
void JES_BAS_SetLocale(jbas_hdl_t hdl, JESBASLocaleCB cb, void *arg);
//=================================[系统参数]=================================
/**
 * @brief 获取设备信息
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [out] devinfo 设备信息
 * @param [in] bDefalut 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_BAS_GetDevInfo(jbas_hdl_t hdl, JBASDevInfo_t *devinfo, JBOOL bDefault);
/**
 * @brief 配置设备名称
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [out] name 设备名称
 * @return <0 失败，==0 成功
 */
int JES_BAS_SetDevName(jbas_hdl_t hdl, const char *name);
/**
 * @brief 配置系统语言
 * @note 本接口实际修改的是系统环境变量，修改后必须重启系统才会生效
 * @note 系统重启后所有使用 setlocale(LC_ALL, "") 的应用均生效
 * @note language 语言，格式：language_territory，如zh_CN，en_US
 * @note 其中language符合ISO 639标准，territory符合ISO 3166标准
 * @note 其他应用可使用 _("string") 支持多语言
 * @note 多语言详细开发指南请参考 《JES多语言开发指南》
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [out] language 语言
 * @return <0 失败，==0 成功
 */
int JES_BAS_SetLanguage(jbas_hdl_t hdl, const char *language);
/**
 * @brief 获取定时重启参数
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [out] timer 定时重启参数
 * @param [in] bDefault 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_BAS_GetRebootTimer(jbas_hdl_t hdl, JBASRebootTimer_t *timer, JBOOL bDefault);
/**
 * @brief 配置定时重启参数
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] timer 定时重启参数
 * @return <0 失败，==0 成功
 */
int JES_BAS_SetRebootTimer(jbas_hdl_t hdl, const JBASRebootTimer_t *timer);
/**
 * @brief 重置设备
 * @note 设备恢复出厂状态，包括卸载所有用户安装的app以及重置所有配置
 * @param [in] hdl JES_BAS_Init 返回值
 * @return <0 失败，==0 成功
 */
int JES_BAS_ResetDevice(jbas_hdl_t hdl);
/**
 * @brief 重置配置
 * @note 重置系统及应用配置，不会卸载已安装的app
 * @note 如想在 reserve=false 时保留参数，请将配置文件存到 /etc/jes.d/reserve 目录下
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] hdl reserve true保留账号管理、操作日志等重要参数。false恢复所有系统及应用配置到出厂状态。
 * @return <0 失败，==0 成功
 */
int JES_BAS_ResetConfigs(jbas_hdl_t hdl, JBOOL reserve);

//=================================[时区和校时]=================================
/**
 * @brief 获取时区参数
 * @note 获取日期时间可直接使用系统接口： time(NULL)/gettimeofday+localtime_r
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [out] tzinfo 时区参数
 * @param [in] bDefault 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_BAS_GetTimezone(jbas_hdl_t hdl, JBASTimezone_t *tzinfo, JBOOL bDefault);
/**
 * @brief 配置时区参数
 * @note 配置日期时间可直接使用系统接口： mktime+settimeofday+system("hwclock -w&")
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] tzinfo 时区参数
 * @param [in] bDefault 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_BAS_SetTimezone(jbas_hdl_t hdl, const JBASTimezone_t *tzinfo);
/**
 * @brief 配置时区参数2
 * @note tzstr需符合 POSIX1003.1 Section 8.3
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] time 时区参数
 * @param [in] bDefault 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_BAS_SetTimezoneStr(jbas_hdl_t hdl, const char *tzstr);
/**
 * @brief 获取NTP校时参数
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [out] ntp NTP校时参数
 * @param [in] bDefault 是否获取默认值
 * @return <0 失败，==0 成功
 */
int JES_BAS_GetNtp(jbas_hdl_t hdl, JBASNtp_t *ntp, JBOOL bDefault);
/**
 * @brief 配置NTP校时参数
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] ntp NTP校时参数
 * @return <0 失败，==0 成功
 */
int JES_BAS_SetNtp(jbas_hdl_t hdl, const JBASNtp_t *ntp);

//=================================[应用看门狗]=================================
/**
 * @brief 注册应用到看门狗
 * @note 看门狗会监测注册的应用是否在运行，如未在运行则使用 cmd start进行启动
 * @note 手动停止应用时必须调用 JES_BAS_WdtRemoveApp 移除看门狗监视，否则还会被启动
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] name 被监测应用名称
 * @param [in] cmd 被监测应用启动脚本，须支持 cmd start/stop/restart 三个指令，cmd无需拼接指令
 * @return <0 失败，==0 成功
 */
int JES_BAS_WdtRegisterApp(jbas_hdl_t hdl, const char *name, const char *cmd);
/**
 * @brief 移除看门狗监视应用
 * @note 手动停止应用时必须调用本接口移除看门狗监视，否则还会被启动
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] name 要移除的应用名称
 * @return <0 失败，==0 成功
 */
int JES_BAS_WdtRemoveApp(jbas_hdl_t hdl, const char *name);

//=================================[日志记录]=================================
/**
 * @brief 记录运行日志
 * @note 可使用 _("string") 支持多语言
 * @note 多语言详细开发指南请参考 《JES多语言开发指南》
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] proc 应用名称
 * @param [in] event 事件
 * @return <0 失败，==0 成功
 */
int JES_BAS_WriteRunLog(jbas_hdl_t hdl, const char *proc, const char *event, ...);
/**
 * @brief 记录操作日志
 * @note 可使用 _("string") 支持多语言
 * @note 多语言详细开发指南请参考 《JES多语言开发指南》
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] user 操作者用户名
 * @param [in] ip 操作者IP，ipv4或ipv6格式字符串，本地操作可根据产品需求填NULL或"-"等
 * @param [in] port 操作者端口号
 * @param [in] result 操作结果错误码，0表示成功，其他值均为失败
 * @param [in] event 操作事件描述
 * @return <0 失败，==0 成功
 */
int JES_BAS_WriteOptLog(jbas_hdl_t hdl, const char *user, const char *ip, uint16_t port, int result, const char *event, ...);
/**
 * @brief 查询日志
 * @note 返回值需要外部调用 free 释放
 * @note 运行日志的proc参数转为JBASLogItem_t中的user
 * @param [in] hdl JES_BAS_Init 返回值
 * @param [in] type 日志类型
 * @param [in] start 开始日期事件，NULL表示从最早有记录的时间开始
 * @param [in] end 结束日期事件，NULL表示到当前时间结束
 * @param [in] page 页码号从0开始
 * @param [in] pageSize 每页条数，最大支持100
 * @param [in] reverse 是否逆序查询，true表示最新的日志为第0页第一条，false表示最早的日志为第0页第一条
 * @param [out] count 本次实际查询到结果的数量
 * @param [out] totalCount 符合条件的日志总数
 * @return 成功返回JBASLogItem_t数组指针，使用完毕需外部free，失败返回NULL
 */
JBASLogItem_t *JES_BAS_QueryLog(jbas_hdl_t hdl, JBASLogType_e type, JTime_t *start, JTime_t *end, int page, int pageSize, JBOOL reverse, int *count, int *totalCount);



#ifdef __cplusplus
}
#endif
#endif // __JES_BAS_H__
