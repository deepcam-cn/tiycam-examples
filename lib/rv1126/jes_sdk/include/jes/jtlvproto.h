
/**
 * @file tlvproto.h
 * @author Simon Liu (lfx@jovision.com)
 * @brief tlv数据元
 * @version 0.1
 * @date 2021-11-10
 * 
 * @copyright @ Jovision Technology Co.,Ltd. 2021-. All rights reserved
 * 
 */
#ifndef TLV_PROTO_H_
#define TLV_PROTO_H_


#define TLV_HEAD_META "META"
#define TLV_HEAD_AREA "AREA"
#define TLV_HEAD_ALAM "ALAM"

/**
 * @brief 智能元数据的类型；T的取值
 */
typedef enum {
    META_TYPE_TARGET                = 0x1,    ///< 目标类型；4字节；取值 @see MetaTargetType_e
    META_TYPE_AI_SIGN               = 0x2,    ///< 算法名字；N字节；用于区分不同厂家的算法
    META_TYPE_DEVICEID              = 0x3,    ///< 设备ID；N字节；字符串形式
    META_TYPE_CHANNELID             = 0x4,    ///< 通道号； 4字节
    META_TYPE_PTS                   = 0x5,    ///< 时间戳； 8字节； 1970年以来的毫秒数（注意：不是标准的mktime的秒数，而是忽略了时区的墙钟时间的秒数）
    META_TYPE_PIC_SIZE              = 0x6,    ///< 图像宽高； 4字节； 宽、高各占2字节
    META_TYPE_OBJ_RECT              = 0x7,    ///< 抓图位置和大小； 8字节； x,y,w,h 各占2字节
    META_TYPE_OBJ_ID                = 0x8,    ///< 目标ID uint64_t
    META_TYPE_OBJ_PIC               = 0x9,    ///< 目标抠图，包括人脸，人体，机非人； 二进制图像
    META_TYPE_SNAPSHOT              = 0xA,    ///< 全景抓图； 二进制图像
    META_TYPE_CHANNELSN             = 0xB,    ///< 通道的设备ID，字符串形式；根据实际情况使用，目前只有个别项目使用；
    META_TYPE_CHANNELTYPE           = 0xC,    ///< 通道类型，1字节：0视频输入，1外部输入，2设备本身；根据实际情况使用，目前只有报警使用；
    META_TYPE_SNAPFILE              = 0xD,    ///< 本地抓拍路径，字符串；根据实际情况使用，目前只有报警在本地传输使用；


    /// @brief 通用模板检测
    META_TYPE_OBJ_NAME              = 0x10,   ///< 目标名称

    /// @brief 人脸子属性   
    META_TYPE_FACE_INFO             = 0x10001,  ///< 是否有人脸子属性； 1 有； 0 无
    META_TYPE_FACE_GENDER           = 0x10002,  ///< 性别； 1字节； 1 男; 2 女
    META_TYPE_FACE_AGE              = 0x10003,  ///< 年龄； 1字节；
    META_TYPE_FACE_MASK             = 0x10004,  ///< 口罩； 1字节； 1 戴口罩； 0 未戴口罩
    META_TYPE_FACE_EXPRESSION       = 0x10005,  ///< 表情； 1字节； 1 微笑；2 愤怒； 3 悲伤； 4 正常； 5 惊讶
    META_TYPE_FACE_HAT              = 0x10006,  ///< 帽子； 1字节； 1 有； 0 无
    META_TYPE_FACE_BEARD            = 0x10007,  ///< 胡子； 1字节； 1 有； 0 无
    META_TYPE_FACE_HAIR             = 0x10008,  ///< 头发； 1字节； 1 长发； 2 短发
    META_TYPE_FACE_GLASS            = 0x10009,  ///< 眼镜； 1字节； 0 无； 1 普通眼镜； 2 太阳眼镜
    META_TYPE_FACE_FEATURE          = 0x1000A,  ///< 人脸识别特征值； N字节； 二进制数据
    META_TYPE_FACE_SIMILARITY       = 0x1000B,  ///< 相似度； 2字节 取值 0-10000， 除以100为百分比
    META_TYPE_FACE_LIVENESS         = 0x1000C,  ///< 是否为活体； 1字节； 1 是； 0 否
    META_TYPE_FACE_ID               = 0x1000D,  ///< 人脸ID； N字节； 二进制数据。人脸库中一个人脸的唯一标识
	META_TYPE_FACE_TEMPERATURE		= 0x1000F,	///< 人脸温度；2字节；人脸摄氏温度乘以100

    /// @brief 人体子属性   
    META_TYPE_BODY_INFO             = 0x20002,  ///< 是否有人体子属性； 1字节； 1 有； 0 无
    META_TYPE_BODY_AGE              = 0x20002,  ///< 年龄； 1字节； 1 少年； 2 青年； 3 老年
    META_TYPE_BODY_GENDER           = 0x20003,  ///< 性别； 1字节； 1 男; 2 女
    META_TYPE_BODY_UPPER_STYLE      = 0x20004,  ///< 上衣款式； 1字节； 1 长袖； 2 短袖
    META_TYPE_BODY_UPPER_COLOR      = 0x20005,  ///< 上衣颜色； 1字节； 1 黑； 2 蓝； 3 绿； 4 白/灰； 5 黄/橙/棕； 6 红/粉/紫
    META_TYPE_BODY_UPPER_TEXTURE    = 0x20006,  ///< 上衣纹理； 1字节； 1 纯色； 2 条纹； 3 格子
    META_TYPE_BODY_LOWER_STYLE      = 0x20007,  ///< 下衣款式； 1字节； 1 长裤； 2 短裤； 3 裙子
    META_TYPE_BODY_LOWER_COLOR      = 0x20008,  ///< 下衣颜色； 1字节； 1 黑； 2 蓝； 3 绿； 4 白/灰； 5 黄/橙/棕； 6 红/粉/紫
    META_TYPE_BODY_SHAPE            = 0x20009,  ///< 体型； 1字节； 1 中等； 2 胖； 3 瘦
    META_TYPE_BODY_LUGGAGE          = 0x2000A,  ///< 行李箱； 1字节； 1 有； 0 无
    META_TYPE_BODY_GLASS            = 0x2000B,  ///< 眼镜； 1字节； 0 无； 1 普通眼镜； 2 太阳眼镜
    META_TYPE_BODY_HAT              = 0x2000C,  ///< 帽子； 1字节； 1 有； 0 无

    /// @brief 车辆子属性   
    META_TYPE_VEHICLE_INFO          = 0x30001,  ///< 是否有车辆子属性； 1字节； 1 有； 0 无
    META_TYPE_VEHICLE_TYPE          = 0x30002,  ///< 车辆类型； 1 小轿车； 2 SUV； 3 面包车； 4 卡车； 5 自行车； 6 电动车/摩托车； 7 三轮车
    META_TYPE_VEHICLE_PLATE_RECT    = 0x30003,  ///< 车牌位置及大小； 8字节； x,y,w,h 各占2字节
    META_TYPE_VEHICLE_PLATE_NO      = 0x30004,  ///< 车牌号； N字节； 车牌字符串
    META_TYPE_VEHICLE_PLATE_PIC     = 0x30005,  ///< 车牌抠图； N字节； 二进制数据

    /// @brief 客流数量统计
    META_TYPE_CUSTOMER_COUNT_IN     = 0x40001,  ///< 进店人数； 4字节；
    META_TYPE_CUSTOMER_COUNT_OUT    = 0x40002,  ///< 出店人数； 4字节；
    META_TYPE_CUSTOMER_PASS         = 0x40003,  ///< 过店人数； 4字节；
    META_TYPE_CUSTOMER_COUNT_KEEP   = 0x40004, ///< 留存人数； 4字节；

    /// @brief 客流数量统计基础数据
    META_TYPE_CUSTOMER_HUMAN_ID     = 0x40021,  ///< 客流统计时的人员ID；4字节；
    META_TYPE_CUSTOMER_ENTER_TIME   = 0x40022,  ///< 人形进入时间；8字节； 1970年以来的毫秒数（注意：不是标准的mktime的秒数，而是忽略了时区的墙钟时间的秒数）
    META_TYPE_CUSTOMER_LEAVE_TIME   = 0x40023,  ///< 人形离开时间；8字节； 1970年以来的毫秒数（注意：不是标准的mktime的秒数，而是忽略了时区的墙钟时间的秒数）
    META_TYPE_CUSTOMER_CROSS_TIME   = 0x40024,  ///< 人形穿过时间；8字节； 1970年以来的毫秒数（注意：不是标准的mktime的秒数，而是忽略了时区的墙钟时间的秒数）

    /// @brief 热度图
    META_TYPE_HOTMAP_SIZE           = 0x50001,  ///< 热度图宽高； 4字节； 宽、高各占2字节
    META_TYPE_HOTMAP_DATA           = 0x50002,  ///< 热度图； N字节； 二进制数据

    /// @brief 区域关注度
    META_TYPE_REGIONAL_HUMAN_COUNT  = 0x60001,  ///< 区域经过人数；4字节；
    META_TYPE_REGIONAL_HUMAN_STAY   = 0x60002,  ///< 区域停留人数（停留超过某个设定时间）；4字节
    META_TYPE_REGIONAL_HUMAN_STAY_RATE = 0x60003, ///< 驻足率；2字节，取值 0-10000， 除以100为百分比
    META_TYPE_REGIONAL_HUMAN_STAY_AVERAGE_TIME = 0x60004, ///< 驻足均时，秒数；4字节
    META_TYPE_REGIONAL_HUMAN_REGION_NAME   = 0x60005,  ///< 区域名称；N字节
    META_TYPE_REGIONAL_HUMAN_REGION_ID  = 0x60006,  ///< 区域ID；4字节；

    /// @brief 区域关注度基础数据
    META_TYPE_REGIONAL_HUMAN_ID         = 0x60021,  ///< 区域关注度的人形ID；4字节；
    META_TYPE_REGIONAL_HUMAN_ENTER_TIME = 0x60022,  ///< 人形进入的时间；8字节； 1970年以来的毫秒数（注意：不是标准的mktime的秒数，而是忽略了时区的墙钟时间的秒数）
    META_TYPE_REGIONAL_HUMAN_LEAVE_TIME = 0x60023,  ///< 人形离开的时间；8字节； 1970年以来的毫秒数（注意：不是标准的mktime的秒数，而是忽略了时区的墙钟时间的秒数）
    
    /// @brief 外接传感器数据
    META_TYPE_EXTERNAL_SENSOR_ID    = 0x70001,  ///< 传感器序号；（注意：只用于区分已接入的传感器，如果换了传感器通过ID无法区分）
    META_TYPE_EXTERNAL_SENSOR_NAME  = 0x70002,  ///< 传感器名称；字符串
    META_TYPE_EXTERNAL_SENSOR_VALUE = 0x70003,  ///< 数值乘以100，int64_t
    META_TYPE_EXTERNAL_SENSOR_UNIT  = 0x70004,  ///< 数值单位；字符串

    /// @brief 排队长度
    META_TYPE_HUMAN_QUEUE_LENGTH      = 0x90001,  ///< 排队人数； 4字节
} TLVMetaType_e;

typedef enum{
    TLVAREA_TYPE_RULE    = 0x10010001,  ///< 规则（检测）区域；区域个数1字节，每个区域：顶点个数1字节，每个顶点坐标4字节XY各2字节；
    TLVAREA_TYPE_OBJ     = 0x10010002,  ///< 目标区域； 每个目标10字节； id、xywh均为unsigned short各占2字节；N/10可以取到目标数量；网络字节序；
} TLVAreaType_e;

typedef enum{
    TLVALARM_TYPE_TYPE     = 0x20010001, ///< 报警类型，字符串形式
    TLVALARM_TYPE_NAME     = 0x20010002, ///< 报警名称，字符串形式，需支持多语言，具备自然语言可读性
    TLVALARM_TYPE_STATUS   = 0x20010003, ///< 报警状态，1字节：0stop，1start，2pulse
    TLVALARM_TYPE_DELAY    = 0x20010004, ///< 报警延时，STATUS=2时有效，表示延时多久结束报警
} TLVAlarmType_e;

/**
 * @brief 智能元数据的目标类型； @see META_TYPE_TARGET 的取值
 * 
 */
typedef enum {

    META_TARGET_FACE                        = 1,        ///< 人脸
    META_TARGET_BODY                        = 2,        ///< 人体
    META_TARGET_MOTOR_VEHICLE               = 3,        ///< 机动车
    META_TARGET_NONMOTOR_VEHICLE            = 4,        ///< 非机动车
    META_TARGET_CUSTOMER_COUNTER            = 5,        ///< 客流统计
    META_TARGET_HOT_MAP                     = 6,        ///< 热度图
    META_TARGET_HOT_AREA                    = 7,        ///< 热区
    META_TARGET_CUSTOMER_COUNTER_BASIC      = 8,        ///< 客流统计基础数据
    META_TARGET_HOT_AREA_BASIC              = 9,        ///< 热区基础数据
    META_TARGET_EXTERNAL_SENSOR             = 10,       ///< 外接传感器数据
    META_TARGET_COMMON                      = 11,       ///<通用内容，比如目标检测
    META_TARGET_HUMAN_QUEUE_LENGTH          = 13,       ///<排队长度
} MetaTarget_e;

#endif