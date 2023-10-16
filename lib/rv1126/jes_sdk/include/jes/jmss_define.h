/***********************************************************************
 * @file jmss_define.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
***********************************************************************/
#ifndef __JMSS_DEFINE_H__
#define __JMSS_DEFINE_H__

#include <jmedia_define.h>

#ifdef __cplusplus
extern "C"
{
#endif

//坐标转换：所有OSD相关的坐标转换为 宽x高=65535x65535为参考的坐标系中，可使用 JMSS_TO_REFVAL 进行转换
#define JMSS_REFERENCE_MAX_WH 65535
#define JMSS_TO_REFVAL(realwh, realval) (realval)*(JMSS_REFERENCE_MAX_WH)/(realwh)
#define JMSS_TO_REALVAL(realwh, refval) (refval)*(realwh)/(JMSS_REFERENCE_MAX_WH)
//获取通道在线状态：返回值0表示不在线，1表示在线
#define JMSS_CHN_STATUS(channelStatus, channel) (((channelStatus)[(channel)/8])>>((channel)%8)&0x1)

//typdef start
typedef enum{
    JMSS_EVENT_STREAM_CHANGE,//编码参数改变，data 为 JVMediaDecodeAttr_t 数组，数组大小为 len/sizeof(JVMediaDecodeAttr_t)
}JMSSEvent_e;
typedef struct{
    struct{
        char deviceId[64];  //设备ID
        int channel;        //通道号
        int substream;      //子码流号
    }devInfo;//设备信息
    JVMediaVDecAttr_t vdec; //视频解码参数
    JVMediaAdecAttr_t adec; //音频解码参数
}JVMediaDecodeAttr_t;//媒体解码参数
typedef struct{
    JBOOL enable;          //开关
    JMediaAencAttr_t attr; //编解码参数
}JMediaAencParam_t;//音频参数
typedef struct{
    JBOOL enable;           //开关（目前强制开启关闭不生效）
    JMediaVencAttr_t attr;  //视频编码参数
}JMediaVencParam_t;//视频参数
typedef struct {
    JBOOL mirror;          // 镜像
    JBOOL flip;            // 翻转
    JMediaRotate_e rotate; // 旋转，get时JMEDIA_ROTATE_MAX表示不支持
    char reserve[64];      // 预留扩展使用
} JMediaVpsParam_t;        // 视频处理参数
typedef struct 
{
    JMediaOsdAttr_t time;//时间osd，text请配置Format：时间格式如：YYYY-MM-DD hh:mm:ss，DD/MM/YYYY hh:mm:ss
    JMediaOsdAttr_t name;//设备名称osd
    JMediaOsdAttr_t custom[JMEDIA_CUSTOM_OSD_MAX_CNT]; //用户自定义多行osd
    JMediaCover_t cover[JMEDIA_CUSTOM_OSD_MAX_CNT];    //遮挡
    JBOOL showWeek;     //是否显示星期
    char reserve[64];      // 预留扩展使用
}JMediaOsdParam_t;//预置OSD参数
typedef struct 
{
    JU32 brightness;       //亮度
    JU32 saturation;       //饱和度
    JU32 contrast;         //对比度
    JU32 sharpness;        //锐度
    JMediaStyle_e style;   //风格
    char reserve[64];      // 预留扩展使用
}JMediaISPAttr_t;//图像基础参数
typedef struct
{
    JMediaWdrType_e type; //宽动态类型
    JMediaWdrMode_e mode; //切换模式
    int strength;         //wdr强度
    JTime_t openTime;     //开启时间，硬件宽动态定时模式时有效（参数中仅时分秒有效）
    JTime_t closeTime;    //关闭时间，硬件宽动态定时模式时生效（参数中仅时分秒有效）
    char reserve[64];      // 预留扩展使用
}JMediaISPWdrParam_t;//图像宽动态参数
typedef struct{
    JMediaDayNightMode_e mode;  //日夜切换模式
    int sensitivity;            //灵敏度，1-10，自动模式生效，值越大进入夜视越早离开夜视越晚
    JMediaFillLightMode_e lightMode;    //补光模式，红外补光，白光灯补光，不补光
    JMediaAdjustMode_e strengthMode; // 灯光强度模式
    int lightStrength;               // 灯光强度，1-100，手动模式有效
    JTime_t dayStart;           //进入白天模式时间，定时模式生效（参数中仅时分秒有效）
    JTime_t dayEnd;             //进入夜间模式时间，定时模式生效（参数中仅时分秒有效）
    char reserve[64];      // 预留扩展使用
}JMediaISPDayNightParam_t;//图像夜视切换参数
typedef struct{
    JBOOL nightReduceFrame; //夜视降帧
    JBOOL starLight;        //星光模式
    JMediaISPDenoise_t denoise;//降噪
    JMediaISPDefog_t defog; //去雾
    JBOOL faceMode;         //人脸模式，特定场景下看清人脸
    JBOOL vehicleMode;      //车辆模式，特定场景下看清车牌
    char reserve[256];      // 预留扩展使用
}JMediaISPAdvancedAttr_t;//图像高级参数


#ifdef __cplusplus
}
#endif
#endif // __JMSS_DEFINE_H__
