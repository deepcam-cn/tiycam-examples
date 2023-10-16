/*
 * jvtypes.h
 *
 *  Created on: 2016年6月3日
 *      Author: Simon Liu
 *		Email : lfx@jovision.com
 */

#ifndef SOURCE_JVTYPES_H_
#define SOURCE_JVTYPES_H_

#include <stdio.h>

//错误码
#define JVERR_NO						0   //成功
#define JVERR_UNKNOWN				  	-1  //未知错误
#define JVERR_NOT_SUPPORT			  	-2  //不支持的功能
#define JVERR_BAD_PARAM					-3  //参数错误
#define JVERR_NO_MEMORY					-4  //内存不足
#define JVERR_NOT_HANDLED  				-5  //没有被处理
#define JVERR_BAD_HANDLE				-6  //错误的句柄
#define JVERR_OPEN_FAIL					-7  //打开错误
#define JVERR_RD_FAIL					-8  //读错误
#define JVERR_WR_FAIL					-9  //写错误
#define JVERR_NO_FREE_RESOURCE			-10 //资源不足
#define JVERR_NOT_FIND					-11 //没有找到
#define JVERR_NOT_INIT					-12 //未初始化
#define JVERR_BAD_MATRIX				-13 //坐标错误
#define JVERR_BAD_DC					-14 //设备上下文错误
#define JVERR_UNKONW_CONTEXT			-15 //不识别的文本，解析失败
#define JVERR_ALREADY_OPENED			-16 //资源已打开
#define JVERR_ALREADY_CLOSED			-17 //资源已关闭
#define JVERR_TIMEOUT					-18 //超时
#define JVERR_OVER_MAX					-19 //超过最大值
#define JVERR_BUSY						-20 //忙
#define JVERR_SEND_FAIL					-21 //发送失败
#define JVERR_BAD_PASSWD				-22 //密码错误
#define JVERR_NO_POWER					-23	//没有权限

#if defined WIN32 || defined WIN64
	typedef unsigned __int8         JU8;
	typedef unsigned __int16        JU16;
	typedef unsigned __int32        JU32;
	typedef unsigned __int64        JU64;

	typedef __int8					JS8;
	typedef __int16					JS16;
	typedef int					JS32;
	typedef __int64					JS64;

	typedef float                   JFloat;
	typedef double					JDouble;

	typedef int                     JBOOL;
	#define JTRUE 					1
	#define JFALSE 					0

	typedef void *                  JHandle;

	#ifndef NULL
		#define NULL    0L
	#endif

	#define snprintf  _snprintf 
#define strdup _strdup

#else
	
	typedef unsigned char           JU8;
	typedef unsigned short          JU16;
	typedef unsigned int            JU32;
	typedef unsigned long long      JU64;
	
	typedef signed char             JS8;
	typedef signed short            JS16;
	typedef signed int              JS32;
	typedef signed long long        JS64;
	
	typedef float                   JFloat;
	typedef double					JDouble;
	
	typedef int                     JBOOL;
	#define JTRUE 					1
	#define JFALSE 					0
	
	typedef void *                  JHandle;
	
	#ifndef NULL
		#define NULL    0L
	#endif
	
#endif

typedef struct{
	JS32 x;
	JS32 y;
}JPoint_t;

//大小
typedef struct
{
    JS32 w;
    JS32 h;
}JSize_t;

//矩形
typedef struct
{
	JS32 x;
	JS32 y;
	JS32 w;
	JS32 h;
}JRect_t;

//矩形区域
typedef struct{
	int left;
	int top;
	int right;
	int bottom;
}JArea_t;

//日期时间
typedef struct
{
	int year;
	int month;	//1~12
	int day;	//1~31
	int hour;	//0~23
	int minute;	//0~59
	int second;	//0~59
}JTime_t;


///////////////////////////////////////////////////
//useful define...

#define jv_assert(expr, exec)               \
	do{ 								  \
		if (1)\
		{\
			if (!(expr)) {					  \
				printf("\nASSERT failed at:\n"\
					   "  >File name: %s\n"   \
					   "  >Function : %s\n"   \
					   "  >Line No. : %d\n"   \
					   "  >Condition: %s\n",  \
						__FILE__,__FUNCTION__, __LINE__, #expr);\
				exec;\
			} \
		}\
		else\
		{\
			/* do nothing*/\
		}\
	}while(0)


#if defined WIN32 || defined WIN64
#define DEBUGF( fmt,...)
#define TRACEF( fmt,...)
#define INFOF( fmt,...)
#define WARNF( fmt,...)
#define ERRORF( fmt,...)
#else
#include <jlog.h>
//临时兼容之用。在解码器中原来的字段有用到
#define DBG_DEBUG LOGLEVEL_DEBUG
#define DBG_LOG LOGLEVEL_INFO
#define DBG_ERR LOGLEVEL_ERR

#define jvDebug(DEBUGLEVEL, fmt, ...) jlog_printf_ex(DEBUGLEVEL, __FILE__, __FUNCTION__, __LINE__, fmt,  ## __VA_ARGS__)

///\brief 日志宏调用
#define DEBUGF( fmt,...)    jlog_printf(LOGLEVEL_DEBUG, __FILE__, __LINE__, fmt,  ## __VA_ARGS__)
#define TRACEF( fmt,...)    jlog_printf(LOGLEVEL_TRACE, __FILE__, __LINE__, fmt,  ## __VA_ARGS__)
#define INFOF( fmt,...)     jlog_printf(LOGLEVEL_INFO,  __FILE__, __LINE__, fmt,  ## __VA_ARGS__)
#define WARNF( fmt,...)     jlog_printf(LOGLEVEL_WARN,  __FILE__, __LINE__, fmt,  ## __VA_ARGS__)
#define ERRORF( fmt,...)    jlog_printf(LOGLEVEL_ERR,   __FILE__, __LINE__, fmt,  ## __VA_ARGS__)
#endif

//color for printf
#define NOCOLOR      "\033[m"
#define RED          "\033[0;32;31m"
#define GREEN        "\033[0;32;32m"
#define YELLOW       "\033[1;33m"


//对齐，align必须是2的N次方。
//向上对齐，例如：JV_ALIGN_CEILING(5,4) = 8
#define JV_ALIGN_CEILING(x,align)     ( ((x) + ((align) - 1) ) & ( ~((align) - 1) ) )
//向下对齐，例如：JV_ALIGN_FLOOR(5,4) = 4
#define JV_ALIGN_FLOOR(x,align)       (  (x) & (~((align) - 1) ) )
//将val变为min,max范围内的值
#ifndef VALIDVALUE
#define VALIDVALUE(val, min, max)	((val)<(min)) ? (min) : (((val)>(max)) ? (max) : (val))
#endif
//浮点数比较大小
#define EPSILON 1e-6
#define FLOAT_EQ(a,b) (fabs((a)-(b)) <= EPSILON)
#define FLOAT_NE(a,b) (fabs((a)-(b)) > EPSILON)
#ifndef FILE_PATH_SIZE
#define FILE_PATH_SIZE 128  //本系统所有文件路径长度统一定义为128字节
#endif
#define U8ToU32(a)		(((unsigned char *)(a))[0] << 24 | ((unsigned char *)(a))[1] << 16 | ((unsigned char *)(a))[2] << 8 | ((unsigned char *)(a))[3])

//最大最小
#ifndef MIN
#define MIN(a,b) ((a)<=(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>=(b)?(a):(b))
#endif
#ifndef SWAP
#define SWAP(a,b) \
do{\
    unsigned int _tmp = (a);\
    (a) = (b);\
    (b) = _tmp;\
}while(0)
#endif

//数组个数
#define ITEMNUM(arrayCtl) (sizeof(arrayCtl)/sizeof(arrayCtl[0]))


//拷贝字符串到数组
//注意	:dstArray必须是char型数组，且不能强转为指针。那样sizeof(dstArray)出错
//例如这样的用法是错的:
//		unsigned char a[10];
//		STRCPY_ARRAY((char*)dstArray, src);
//lint -emacro(421, STRCPY_ARRAY)
#define STRCPY_ARRAY(dstArray, src)\
do{\
	const char *__pSrc_ = (const char *)(src);\
	if(__pSrc_ != NULL)\
	{\
		strncpy((char*)(dstArray),__pSrc_,sizeof(dstArray)-1);\
		(dstArray)[(sizeof(dstArray))-1]=0;\
	}\
	else\
	{\
		(dstArray)[0]=0;\
	}\
}while(0)

//拷贝字符串到目的地址
//注意: 目的是地址才用这个宏
//lint -emacro(421, STRCPY_ARRAY_ex)
#define STRCPY_ARRAY_ex(dstArray, src, dstSize)\
do{\
	const char *__pSrc_ = (const char *)(src);\
	if(__pSrc_ != NULL)\
	{\
		strncpy((char*)(dstArray),__pSrc_,(dstSize)-1);\
		(dstArray)[(dstSize)-1]=0;\
	}\
	else\
	{\
		(dstArray)[0]=0;\
	}\
}while(0)


//拷贝指定个数字符到目的地址
//注意: 满足两个条件才用这个宏: 1指定个数 2目的是地址
//lint -emacro(421, STRNCPY_ex)
#define STRNCPY_ex(dst, src, dstSize, cntChar)\
do{\
	const char *__pSrc_ = (const char *)(src);\
	if(__pSrc_ != NULL)\
	{\
		int nn = MIN((dstSize)-1, (cntChar));\
		strncpy((char*)(dst), __pSrc_, nn);\
		(dst)[nn]=0;\
	}\
	else\
	{\
		(dst)[0]=0;\
	}\
}while(0)

//拷贝指定个数字符到数组
//注意: 这个宏是不安全的。所以会有pclint警告
//而且只会拷贝cntChar-1个字符
#define STRNCPY(dst, src, cntChar)\
do{\
	const char *__pSrc_ = (const char *)(src);\
	if(__pSrc_ != NULL)\
	{\
		strncpy((char*)(dst), __pSrc_, (cntChar));\
		(dst)[cntChar-1]=0;\
	}\
	else\
	{\
		(dst)[0]=0;\
	}\
}while(0)

//释放内存
#ifndef FREE
#define FREE(p) \
    do{\
        if(p)\
        {\
            free(p);\
            p=NULL;\
        }\
    } while(0)
#endif
//检测结果
#ifndef CHECK_RET
#define CHECK_RET(express, successret)\
    do{\
        JS32 s32Ret = express;\
        if (successret != s32Ret)\
        {\
            ERRORF("%s failed! %d(0x%x)\n", #express,s32Ret,s32Ret);\
        }\
    }while(0)
#endif
#ifndef CHECK_RET_EXE
#define CHECK_RET_EXE(express, successret, exec)\
    do{\
        JS32 s32Ret = express;\
        if (successret != s32Ret)\
        {\
            ERRORF("%s failed with %d(0x%x)\n", #express, s32Ret,s32Ret);\
            exec;\
        }\
    }while(0)
#endif


#endif /* SOURCE_JVTYPES_H_ */
