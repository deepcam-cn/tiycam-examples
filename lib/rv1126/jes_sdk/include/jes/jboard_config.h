/***********************************************************************
 * @file jboard_control.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2023-. All rights reserved
***********************************************************************/
#ifndef __JBOARD_CONTROL_H__
#define __JBOARD_CONTROL_H__

#include <jvtypes.h>
#include <jvmediatypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_LIST_CNT 10

typedef enum{
    JBOARD_PERIPHERAL_NONE,//未找到
    JBOARD_PERIPHERAL_GPIO,//GPIO
    JBOARD_PERIPHERAL_PWM,//PWM
}JBoardPeripheral_e;//外围设备类型
typedef enum{
    JBoardChat_NONE,    //不支持对讲
    JBoardChat_HALF,    //半双工对讲
    JBoardChat_FULL,    //全双工对讲
}JBoardChatMode_e;  //对讲模式
typedef enum{
    JBOARD_AUDIO_IN_MIC,    //mic输入
    JBOARD_AUDIO_IN_PICKUP, //外接拾音器
}JBoardAudioInType_e; //音频输入类型
typedef enum{
    JBOARD_AUDIO_OUT_SPEAKER,   //内置喇叭
    JBOARD_AUDIO_OUT_LINEOUT,   //外接喇叭
}JBoardAudioOutType_e; //音频输出类型
typedef enum{
    JBOARD_PTZ_PTMODE_NONE, //不支持云台
    JBOARD_PTZ_PTMODE_SYNC, //水平垂直同步转动
    JBOARD_PTZ_PTMODE_NOSYNC,//水平垂直不支持同时转动
}JBoardPtzPTMode_e;

typedef struct{
    int num;    //gpio num（不分组的）
    int dir;    //方向：0输入，1输出
    int act;    //0表示低有效，1表示高有效
}JBoardGpio_t;//GPIO信息
typedef struct{
    int chip;   //pwm chip num
    int chn;    //pwm channel num
    int period; //周期，单位纳秒
    int duty_def;//默认占空比，单位纳秒
    int duty_range[2];//占空比有效区间，单位纳秒
}JBoardPwm_t;//PWM信息
typedef struct {
    char hardware[32];          // 硬件版本
    int hulltype;               // 机壳型号
    int lenstype;               // 镜头型号
    int soundcount;             // 自定义声音文件最大数量
    char reserve[256]; // 预留扩展使用
} JBoardDevice_t;               // 设备属性
typedef struct {
    int id;         //id
    char name[32];  //名称
    JSize_t size;   //分辨率
    int pixel;      //像素约值（万）
    int sensor_wdr; //是否支持wdr
    char reserve[256];  //预留扩展使用
} JBoardSensor_t;   //sensor属性
typedef struct{
    int typelist_cnt;                          // 编码类型数量，取值：1-9
    JVMediaVideotype_e typelist[MAX_LIST_CNT]; // 编码类型列表
    int reslist_cnt;                           // 分辨率列表数量
    JSize_t reslist[MAX_LIST_CNT];             // 分辨率列表
    int frame_range[2];         // 帧率范围：frame_range[0]最小值，frame_range[1]最大值
    char reserve[256]; // 预留扩展使用
}JBoardVENC_t;  //视频编码能力属性
typedef struct {
    int typelist_cnt;                          // 编解码类型列表数量
    JVMediaAudioType_e typelist[MAX_LIST_CNT]; // 编解码类型列表
    int samplerate_list_cnt;                   // 采样率列表数量
    int samplerate_list[MAX_LIST_CNT];         // 采样率列表
    int bitwidth_list_cnt;                     // 位宽列表数量
    int bitwidth_list[MAX_LIST_CNT];           // 位宽列表
    int bitrate_range[2]; // 码率范围：bitrate_range[0]最小值，bitrate_range[1]最大值
    JBoardChatMode_e chat_mode; // 对讲模式
    int ai_cnt; //音频输入设备的数量
    int ao_cnt; //音频输出设备的数量
    char reserve[256]; //预留扩展使用
} JBoardAudio_t; // 音频能力属性
typedef struct{
    JBoardPtzPTMode_e ptmode;
    char reserve[256]; // 预留扩展使用
}JBoardPtz_t;
typedef struct{
    int day_thresh;
    int night_thresh;
    int value;
}JBoardPhotoSns_t;

/**
 * @brief 获取硬件配置文件绝对路径
 * @note 硬件配置存在还未提供解析接口的信息，可以根据json定义自行解析
 * @return 配置文件路径
 */
const char *jboard_get_hwconfig_file();
/**
 * @brief 查找外围设备
 * @note 本接口仅是从硬件配置中查找外围设备
 * @param [in] name 设备名称，详见/factory/hwconfig.json中的 peripheral
 * @return 设备类型
 */
JBoardPeripheral_e jboard_find_peripheral(const char *name);
/**
 * @brief 获取GPIO信息
 * @note 从硬件配置中读取 name 对应的GPIO
 * @note 读取信息后可使用 jlinux/jlinux_gpio.h 中接口控制
 * @param [in] name 设备名称，详见/factory/hwconfig.json中的 peripheral
 * @param [out] count 对应GPIO的数组个数
 * @return GPIO结构体数组指针，需要外部使用 free 释放，NULL表示未找到
 */
JBoardGpio_t *jboard_get_gpio(const char *name, int *count);
/**
 * @brief 获取PWM信息
 * @note 从硬件配置中读取 name 对应的PWM
 * @note 读取信息后可使用 jlinux/jlinux_pwm.h 中接口控制
 * @param [in] name 设备名称，详见/factory/hwconfig.json中的 peripheral
 * @param [out] count 对应PWM数组个数
 * @return PWM 结构体数组指针，需要外部使用 free 释放，NULL表示未找到
 */
JBoardPwm_t *jboard_get_pwm(const char *name, int *count);

/**
 * @brief 开关灯
 * @note 灯一般有gpio和pwm两种方式，内部自动匹配控制方式进行开关控制
 * @param [in] name 灯名称，详见/factory/hwconfig.json中的 peripheral
 * @param [in] idx 灯序号，-1表示同时控制所有，同一种灯有多个控制接口时使用比如RGB状态的，有3个GPIO或PWM分别进行控制
 * @param [in] on 取值0-100；GPIO控制时，0表示关闭，其他值表示开启；pwm时0表示关闭，其他值表示占空比的百分比用于控制亮度
 * @return <0 失败，==0 成功
 */
int jboard_set_light(const char *name, int idx, int on);

/**
 * @brief 获取设备参数
 * @param [out] device 参数
 * @return <0 失败，==0 成功
 */
int jboard_get_device_attr(JBoardDevice_t *device);
/**
 * @brief 获取sensor参数
 * @param [out] sensor 参数
 * @return <0 失败，==0 成功
 */
int jboard_get_sensor_attr(JBoardSensor_t *sensor);
/**
 * @brief 获取视频流数量
 * @param [in] live true只取直播流，false取直播流+抓拍流
 * @return 视频流数量
 */
int jboard_get_stream_cnt(JBOOL live);
/**
 * @brief 获取视频流编码能力
 * @param [in] stream 流id从0开始
 * @param [out] venc 编码能力
 * @return <0 失败，==0 成功
 */
int jboard_get_venc_ability(int stream, JBoardVENC_t *venc);
/**
 * @brief 获取音频编解码能力
 * @param [out] audio 编解码能力
 * @return <0 失败，==0 成功
 */
int jboard_get_audio_ability(JBoardAudio_t *audio);
/**
 * @brief 获取PTZ能力
 * @param [out] ptz 编解码能力
 * @return <0 失败，==0 成功
 */
int jboard_get_ptz_ability(JBoardPtz_t *ptz);
/**
 * @brief 查询音频能力是否支持
 * @param [in] ability 音频能力字段
 * @return <0 失败，==0 成功
 */
int jboard_find_audio_ability(const char *ability);
/**
 * @brief 获取硬件特性是否支持
 * @param [in] feature 硬件特性字段
 * @return 1支持，0不支持
 */
int jboard_find_hwfeature(const char *feature);
/**
 * @brief 获取图像能力是否支持
 * @param [in] ability 图像能力字段
 * @return 1支持，0不支持
 */
int jboard_find_image_ability(const char *ability);
/**
 * @brief 获取PTZ能力是否支持
 * @param [in] ability PTZ能力字段
 * @return 1支持，0不支持
 */
int jboard_find_ptz_ability(const char *ability);
/**
 * @brief 读取硬光敏信息
 * @param [in] sns 光敏值
 * @return 0成功，-1失败，-2不支持
 */
int jboard_get_photosensor(JBoardPhotoSns_t *sns);


#ifdef __cplusplus
}
#endif
#endif // __JBOARD_CONTROL_H__
