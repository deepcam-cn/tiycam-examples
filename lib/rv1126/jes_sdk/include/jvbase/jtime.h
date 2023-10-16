#ifndef _JTIME_H_
#define _JTIME_H_

#include <time.h>
#include "jvtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

//时间转time_t，忽略时区
//year		:年
//month		:月,1~12
//day 		:日,1~31
//hour		:时,0~23
//minute	:分,0~59
//second	:秒,0~59
//返回值	:time_t
time_t JTime_mkgmtime_ex(unsigned int year, unsigned int mon, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec);
time_t JTime_mkgmtime(const JTime_t *pJVTime);

//time_t转墙钟时间，忽略时区
void JTime_gmtime(const time_t *tm, JTime_t *outJVTime);

//time_t转当前时区的墙钟时间
void JTime_localtime(const time_t *tm, JTime_t *outJVTime);

//当前时区的墙钟时间转time_t
time_t JTime_mktime_ex(unsigned int year, unsigned int mon, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec);
time_t JTime_mktime(const JTime_t *pJVTime);

//把start~end的时间范围 按天分割。保存到outDayStart和outDayEnd
//返回值	:天数
int JTime_split_into_day(const JTime_t *start, const JTime_t *end, JTime_t *outDayStart, JTime_t *outDayEnd, int maxDay);

//获取当前时区的墙钟时间
void JTime_get_localtime(JTime_t *outJVTime);

//将当前时间增加（或减少） seconds 秒
//now 原始时间
//seconds 要增加的时间。 为负则是减少
//dstTm 结果。可以与 #srcTm 相同
void JTime_add(const JTime_t *srcTm, int seconds, JTime_t *dstTm);

//把时间按格式转化为字符串
//ptm 要转换的时间。如果为空，则使用 #second
//second 要转换的时间。如果 #ptm非空，则本参数无效
//timeFormat 串格式，例如："YYYYMMDD hh:mm:ss"。年可以用YY只显示后两个。其它的顺序可以颠倒。空格，冒号等分隔符可以随意换，数量也不限
//str 输出。请提供足够的空间
//return str
char *JTime_time2str(const JTime_t *ptm, time_t second, const char *timeFormat, char *str);

//可以把多种格式的字符串格式的时间转换成tm
struct tm *JTime_str2tm(const char *str, struct tm *tm);


//打印本次执行的当前时间，精确到微秒，同时打印相对上次执行时经过的时间间隔
//打印类似这样：[userInfo] Time Now: 2018-01-30 10:28:54.722745, Elapsed 19725us
//userInfo 一个标记，随便填
void JTime_elapsed(const char *userInfo);

#ifdef __cplusplus
}
#endif

#endif /* _ARRAY_H_ */


