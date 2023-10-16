#ifndef _JTIME_H_
#define _JTIME_H_

#include <time.h>
#include "jvtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

//ʱ��תtime_t������ʱ��
//year		:��
//month		:��,1~12
//day 		:��,1~31
//hour		:ʱ,0~23
//minute	:��,0~59
//second	:��,0~59
//����ֵ	:time_t
time_t JTime_mkgmtime_ex(unsigned int year, unsigned int mon, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec);
time_t JTime_mkgmtime(const JTime_t *pJVTime);

//time_tתǽ��ʱ�䣬����ʱ��
void JTime_gmtime(const time_t *tm, JTime_t *outJVTime);

//time_tת��ǰʱ����ǽ��ʱ��
void JTime_localtime(const time_t *tm, JTime_t *outJVTime);

//��ǰʱ����ǽ��ʱ��תtime_t
time_t JTime_mktime_ex(unsigned int year, unsigned int mon, unsigned int day, unsigned int hour, unsigned int min, unsigned int sec);
time_t JTime_mktime(const JTime_t *pJVTime);

//��start~end��ʱ�䷶Χ ����ָ���浽outDayStart��outDayEnd
//����ֵ	:����
int JTime_split_into_day(const JTime_t *start, const JTime_t *end, JTime_t *outDayStart, JTime_t *outDayEnd, int maxDay);

//��ȡ��ǰʱ����ǽ��ʱ��
void JTime_get_localtime(JTime_t *outJVTime);

//����ǰʱ�����ӣ�����٣� seconds ��
//now ԭʼʱ��
//seconds Ҫ���ӵ�ʱ�䡣 Ϊ�����Ǽ���
//dstTm ����������� #srcTm ��ͬ
void JTime_add(const JTime_t *srcTm, int seconds, JTime_t *dstTm);

//��ʱ�䰴��ʽת��Ϊ�ַ���
//ptm Ҫת����ʱ�䡣���Ϊ�գ���ʹ�� #second
//second Ҫת����ʱ�䡣��� #ptm�ǿգ��򱾲�����Ч
//timeFormat ����ʽ�����磺"YYYYMMDD hh:mm:ss"���������YYֻ��ʾ��������������˳����Եߵ����ո�ð�ŵȷָ����������⻻������Ҳ����
//str ��������ṩ�㹻�Ŀռ�
//return str
char *JTime_time2str(const JTime_t *ptm, time_t second, const char *timeFormat, char *str);

//���԰Ѷ��ָ�ʽ���ַ�����ʽ��ʱ��ת����tm
struct tm *JTime_str2tm(const char *str, struct tm *tm);


//��ӡ����ִ�еĵ�ǰʱ�䣬��ȷ��΢�룬ͬʱ��ӡ����ϴ�ִ��ʱ������ʱ����
//��ӡ����������[userInfo] Time Now: 2018-01-30 10:28:54.722745, Elapsed 19725us
//userInfo һ����ǣ������
void JTime_elapsed(const char *userInfo);

#ifdef __cplusplus
}
#endif

#endif /* _ARRAY_H_ */


