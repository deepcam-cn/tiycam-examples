/*
 * jlog.h
 *
 *  Created on: 2019年3月26日
 *      Author: Administrator
 */

#ifndef DEVEL_JVBASE_SOURCE_JVBASE_JLOG_H_
#define DEVEL_JVBASE_SOURCE_JVBASE_JLOG_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	LOGLEVEL_ERR,	///< 致命错误
	LOGLEVEL_WARN,	///< 可能导致出错
	LOGLEVEL_INFO,	///< 告知用户，当前运行状态
	LOGLEVEL_TRACE,  ///< 调试信息
	LOGLEVEL_DEBUG,	///< 详细调试信息
	LOGLEVEL_ALL	///< 所有日志信息
}JLogLevel_e;


typedef struct{
	JLogLevel_e levelFile;		//文件输出的Log等级
	JLogLevel_e levelConsole;	//终端输出的Log等级
	int enableTimeStamp;		//行首加时间
	struct
	{
		char logPath[256];		//终端输出的路径。置空则不输出到文件
		int logFileLen;			//文件的最大长度，单位为字节。超过长度将会重新创建文件
		int logFileCnt;			//Log文件数量。自动删除超过的数量.最大值为99
	};
}JLogParam_t;

int jlog_set_param(JLogParam_t *param);

typedef void (*jlog_callback_t)(const char* str, int len);
void jlog_regirst(jlog_callback_t callback);

int jlog_printf_ex(JLogLevel_e level, const char *fname, const char *function, int line, const char* format, ...) __attribute__((format(printf,5,6)));
#define jlog_printf(level, fname, line, format, ...) jlog_printf_ex(level, fname, "", line, format, ## __VA_ARGS__)




#ifdef __cplusplus
}
#endif



#endif /* DEVEL_JVBASE_SOURCE_JVBASE_JLOG_H_ */
