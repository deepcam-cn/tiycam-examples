 /***********************************************************************
 * @file jmedia_define.h
     JMEDIA_DEFINE
 * @brief   header file
 * @history
 * Date       Version Author    description
 * ========== ======= ========= =======================================
 * 2022-07-13 V1.0    Lucky,lukai@jovision.com   Create
 *
 * @Copyright (C)  2022  Jovision Technology Co., Ltd.
***********************************************************************/
#ifndef __JMEDIA_DEFINE_H__
#define __JMEDIA_DEFINE_H__

#include <stdint.h>
#include "jvtypes.h"
#include "jvmediatypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define JMEDIA_OSD_REGION_MAX_POINT_NUM 10
#define JMEDIA_OSD_REGION_MAX_NUM 40
#define JMEDIA_CUSTOM_OSD_MAX_CNT 8
typedef void *(*JMallocCB)(void *arg, int size);
typedef void *(*JFreeCB)(void *arg, int size);

//typdef start
typedef enum{
    JMEDIA_OSD_TYPE_TEXT,   //OSD类型文字
    JMEDIA_OSD_TYPE_COVER,  //OSD类型遮挡
    JMEDIA_OSD_TYPE_REGION, //OSD类型区域
    JMEDIA_OSD_TYPE_MAX
}JMediaOsdType_e;//OSD类型
typedef enum{
    JMEDIA_OSD_RGN_TYPE_COVER,      //OSD区域类型：矩形遮挡
    JMEDIA_OSD_RGN_TYPE_RECT,       //OSD区域类型：矩形
    JMEDIA_OSD_RGN_TYPE_MINIRECT,   //OSD区域类型：矩形只绘制四个角
    JMEDIA_OSD_RGN_TYPE_POLYGON,    //OSD区域类型：多边形
    JMEDIA_OSD_RGN_TYPE_TEXT,       //OSD区域类型：文字
    JMEDIA_OSD_RGN_TYPE_MAX
}JMediaOsdRgnType_e;//区域类型
typedef enum
{
    JMEDIA_ROTATE_NONE = 0,     //不旋转
    JMEDIA_ROTATE_90 = 1,       //向右旋转90度
    JMEDIA_ROTATE_180 = 2,      //向右旋转180度
    JMEDIA_ROTATE_270 = 3,      //向右旋转270度
    JMEDIA_ROTATE_MAX
} JMediaRotate_e; //旋转
typedef enum{
	JMEDIA_STYLE_NORMAL,    //标准
	JMEDIA_STYLE_BRIGHT,    //通透
	JMEDIA_STYLE_SOFT,      //柔和
	JMEDIA_STYLE_MAX
} JMediaStyle_e;//图形风格
typedef enum
{
    JMEDIA_AEMODE_AUTO,       //自动曝光
    JMEDIA_AEMODE_HIGH_LIGHT, //强光抑制
    JMEDIA_AEMODE_LOW_LIGHT,  //背光补偿
    JMEDIA_AEMODE_MAX
} JMediaAEMode_e;//曝光模式
typedef enum {
    JMEDIA_WBMODE_AUTO,         // 自动
    JMEDIA_WBMODE_INCANDESCENT, // 白炽灯
    JMEDIA_WBMODE_WARMLIGHT,    // 暖光
    JMEDIA_WBMODE_NaturalLight, // 自然光
    JMEDIA_WBMODE_FLUORESCENT,  // 荧光灯
    JMEDIA_WBMODE_MANUAL,       // 手动模式
    JMEDIA_WBMODE_MAX
} JMediaWBMode_e; // 白平衡模式
typedef enum
{
    JMEDIA_POWER_FREQ_TYPE_CLOSE,	//关闭
    JMEDIA_POWER_FREQ_TYPE_50HZ,	//50Hz
    JMEDIA_POWER_FREQ_TYPE_60HZ,	//60Hz
    JMEDIA_POWER_FREQ_TYPE_MAX
}JMediaPowerFreqType_e;//工频类型
typedef enum
{
    JMEDIA_WDR_TYPE_CLOSE,   //关闭
    JMEDIA_WDR_TYPE_DIGITAL, //数字宽动态
    JMEDIA_WDR_TYPE_HARD,    //硬件宽动态
    JMEDIA_WDR_TYPE_MAX,
} JMediaWdrType_e;//宽动态类型
typedef enum
{
    JMEDIA_WDR_MODE_AUTO, //自动模式
    JMEDIA_WDR_MODE_OPEN, //一直开启
    JMEDIA_WDR_MODE_CLOSE, //一直关闭
    JMEDIA_WDR_MODE_TIME, //定时模式
    JMEDIA_WDR_MODE_MAX,
} JMediaWdrMode_e;//宽动态模式
typedef enum
{
    JMEDIA_DAYNIGHT_MODE_AUTO,         //自动模式
    JMEDIA_DAYNIGHT_MODE_ALWAYS_DAY,   //一直白天
    JMEDIA_DAYNIGHT_MODE_ALWAYS_NIGHT, //一直夜间
    JMEDIA_DAYNIGHT_MODE_TIME_DAY,     //定时白天
    JMEDIA_DAYNIGHT_MODE_MAX
} JMediaDayNightMode_e;//夜视模式
typedef enum
{
    JMEDIA_FILLLIGHT_MODE_AUTO_IR,      //自动红外
    JMEDIA_FILLLIGHT_MODE_AUTO_WHITE,   //自动白光
    JMEDIA_FILLLIGHT_MODE_ALWAYS_CLOSE, //常闭
    JMEDIA_FILLLIGHT_MODE_MAX
} JMediaFillLightMode_e;//补光模式
typedef enum {
    JMEDIA_ADJUST_MODE_AUTO,   // 自动
    JMEDIA_ADJUST_MODE_MANUAL, // 手动
    JMEDIA_ADJUST_MODE_MAX
} JMediaAdjustMode_e; // 控制模式
typedef enum
{
    JMEDIA_RAWFRAMETYPE_YV12,   //YUV格式YV12
    JMEDIA_RAWFRAMETYPE_YU12,   //YUV格式YU12
    JMEDIA_RAWFRAMETYPE_NV12,   //YUV格式NV12
    JMEDIA_RAWFRAMETYPE_NV21,   //YUV格式NV21
    JMEDIA_RAWFRAMETYPE_RGB888, //RGB888
    JMEDIA_RAWFRAMETYPE_BGR888, //BGR888
    JMEDIA_RAWFRAMETYPE_MAX
} JMediaRawFrameType_e;//原始数据类型
typedef enum{
    JMEDIA_AREA_POS_LEFT_TOP,
    JMEDIA_AREA_POS_LEFT_BOTTOM,
    JMEDIA_AREA_POS_RIGHT_TOP,
    JMEDIA_AREA_POS_RIGHT_BOTTOM,
    JMEDIA_AREA_POS_CENTER,
    JMEDIA_AREA_POS_CUSTOM,
    JMEDIA_AREA_POS_MAX
}JMediaAreaPos_e;//区域位置类型

typedef struct{
    void *virAddr;    //虚拟地址
    void *phyAddr;    //物理地址，0表示不支持
    JU32 width;       //分辨率宽
    JU32 height;      //分辨率高
    JU32 len;         //虚拟地址数据长度
    JU64 pts;         //时间戳
    JU64 reserve[10]; //预留，海思平台reserve[0]存储PoolID
    void *handle;     //用于存放底层需要释放的句柄调用者无需关心
}JVMediaRawFrame_t;//原始数据帧结构
typedef struct
{
    JVMediaAudioType_e encType; //编码类型
    int sampleRate;             //采样率，取值：8000,11025,16000,22050,24000,32000,44100,48000
    int bitWidth;               //位宽，取值：8,16,32
    int bitrate;                //码率，AAC使用
    int channelnum;             //声道数目，1单声道，2双声道
    int volume;                 //音量0-100范围
    JBOOL mute;                 //静音（仅对输出有效）
    int anrLevel;               //降噪，0关闭，1开启（仅对输入有效）
    char reserve[64];           //预留扩展使用
}JMediaAencAttr_t;//音频编解码参数
typedef struct{
    JVMediaVideotype_e vencType; //视频编码协议类型
    JVMediaRcmode_e rcMode;      //码控模式
    JU32 width;                  //分辨率宽
    JU32 height;                 //分辨率高
    JU32 framerate;              //帧率
    JU32 gop;                    // I帧间隔，帧数
    JU32 bitrate;                //码率kbps
    int quality;                 //图像质量，1-5，5个等级：超清、高清、标清、流畅、极速
    JBOOL stretchEnable;         //对于16：9与4：3之间的差异，是拉伸，还是裁剪。为真时表示拉伸
    JBOOL smartencEnable;        //是否启动智能编码
    char reserve[64];           //预留扩展使用
}JMediaVencAttr_t;//视频编码参数
typedef struct {
    JBOOL enable;     // 开关
    int reverse;      // 是否反选
    int roiCnt;       // ROI数量
    JRect_t roi[4];   // ROI坐标
    int weight;       // 权重0-10
    char reserve[64]; // 预留扩展使用
} JMediaRoi_t;        // 感兴趣区域参数
typedef struct
{
    char text[512];   // 文字，表示时间时为时间格式
    int fontsize;     // 字体大小
    JU32 color;       // 统一使用ARGB8888，内部自行转化为自己支持的
    char reserve[64]; // 预留扩展使用
} JMediaOsdText_t;    // OSD文字信息
typedef struct {
    JBOOL enable;         // 是否显示
    JMediaAreaPos_e pos;  // 位置
    JPoint_t absPos;      // 绝对位置，pos 为 JMEDIA_AREA_POS_CUSTOM 时有效
    JMediaOsdText_t text; // 文字
} JMediaOsdAttr_t;        // OSD属性信息
typedef struct {
    JBOOL enable;     // 使能
    JU32 color;       // 统一使用ARGB8888，内部自行转化为自己支持的
    JRect_t rect;     // 遮挡位置
    char reserve[64]; // 预留扩展使用
} JMediaCover_t;      // 遮挡属性信息
typedef struct
{
    int count;//顶点的个数>=2,=2时是绊线
    JPoint_t points[JMEDIA_OSD_REGION_MAX_POINT_NUM];//顶点坐标
} JMediaPolygon_t;//多边形信息
typedef struct {
    JMediaOsdRgnType_e type; // 区域类型
    JU32 color; // 边框颜色，统一使用ARGB8888，内部自行转化为自己支持的
    union {
        JRect_t rect;            // 矩形坐标
        JMediaPolygon_t polygon; // 多边形坐标
        JMediaOsdAttr_t text;    // 文字坐标以及内容：此处仅支持绝对位置
    };
} JMediaOsdRgn_t; // OSD区域内容
typedef struct {
    JU64 pts; // 时间戳，根据它找到区域要绘制的帧，用于帧同步，不关心时可以为0
    int count; // 区域数量，最大 JMEDIA_OSD_REGION_MAX_NUM
    JMediaOsdRgn_t region[JMEDIA_OSD_REGION_MAX_NUM]; // 区域内容
} JMediaOsdRegions_t;                                 // OSD区域参数
typedef struct {
    JMediaPowerFreqType_e PFType;  // 工频，解决工频干扰问题
    JMediaAEMode_e mode;           // 曝光策略
    JMediaAdjustMode_e adjustMode; // 曝光控制模式
    JU32 exposureMax; // 最大曝光时间。曝光时间为 ： 1/exposureMax 秒，取值 3 - 100000，自动模式生效
    JU32 exposureMin; // 最小曝光时间。曝光时间为 ： 1/exposureMin 秒，取值 3 - 100000，自动模式生效
    int gainCtrl;     // 增益值（0-2048），手动模式生效
    int exposureCtrl; // 曝光时间（1-1024），手动模式生效
    char reserve[256]; // 预留扩展使用
} JMediaISPAE_t;       // 图像曝光参数
typedef struct {
    JMediaWBMode_e mode; // 模式
    int redGain;         // 红色增益，手动模式有效
    int blueGain;        // 红色增益，手动模式有效
    char reserve[256];    // 预留扩展使用
} JMediaISPWb_t;          // 白平衡参数
typedef struct {
    JMediaWdrType_e type; // 宽动态类型
    JMediaWdrMode_e mode; // 切换模式
    int strength;         // wdr强度
    char reserve[256];    // 预留扩展使用
} JMediaISPWdr_t;         // 图像宽动态参数
typedef struct {
    JMediaDayNightMode_e mode; // 夜视切换模式
    int sensitivity; // 灵敏度，1-10，自动模式生效，值越大进入夜视越早离开夜视越晚
    JMediaFillLightMode_e lightMode; // 补光模式
    JMediaAdjustMode_e strengthMode; // 灯光强度模式
    int lightStrength;               // 灯光强度，1-100，手动模式有效
    char reserve[256];                // 预留扩展使用
} JMediaISPDayNight_t;               // 图像夜视切换参数
typedef struct {
    JBOOL enable;            // 开关
    JMediaAdjustMode_e mode; // 模式
    int airDomainStrength;   // 空域降噪强度
    int timeDomainStrength;  // 时域降噪强度
    char reserve[256];        // 预留扩展使用
} JMediaISPDenoise_t;        // 降噪参数
typedef struct {
    JBOOL enable;            // 去雾开关
    JMediaAdjustMode_e mode; // 模式
    int strength;            // 强度
    char reserve[256];        // 预留扩展使用
} JMediaISPDefog_t;          // 去雾

#ifdef __cplusplus
}
#endif
#endif // __JMEDIA_DEFINE_H__




