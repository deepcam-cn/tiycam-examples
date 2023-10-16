/***********************************************************************
 * @file jnetwork_define.h
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2023-04-14
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2023-. All rights reserved
***********************************************************************/
#ifndef __JNETWORK_DEFINE_H__
#define __JNETWORK_DEFINE_H__

#include <jvtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum{
    JNETWORK_EVENT_CHANGED, //网络改变：网卡或IP地址，data对应：JNetCardList_t
}JNetworkEvent_e;
typedef enum{
    JNETWORK_TYPE_ETHERNET, //有线网络
    JNETWORK_TYPE_WIRELESS, //无线网络（WLAN）
    JNETWORK_TYPE_MOBILE,   //移动网络（4G、5G ...）
}JNetworkType_e;
typedef struct
{
    JBOOL enable;     // 是否使能IPv4
    char name[12];    // 当前网卡名称
    int bDHCP;        // 以太网自动获取或者手动设置标志位
    char addr[16];    // IP地址
    char mask[16];    // 子网掩码
    char gateway[16]; // 网关
    char mac[20];     // MAC地址，添加此信息防止有的路由器，设置MAC地址和IP地址绑定
    char dns[16];     // DNS
}JNetAddr_t;// IPV4地址
typedef struct
{
    JBOOL enable;         // 是否使能IPv6
    int type;             // 0 手动 1 dhcp 2 路由公告
    char addr_global[48]; // IPv6地址
    char addr_link[48];   // 本地IPv6地址
    int mask;             // IPv6地址掩码前缀长度 /64
    char gateway[48];     // IPv6网关
    char dns[48];         // IPv6 DNS
}JNetAddr6_t;// IPV6地址
typedef struct{
    JBOOL enable;        // 网卡否启用
    JNetworkType_e type; // 网络类型
    JNetAddr_t addr;     // IPV4网络地址
    JNetAddr6_t addr6;   // IPV6网络地址：暂不支持
}JNetCard_t;// 网卡地址信息
typedef struct{
    int count;  //所有网卡数量
    JNetCard_t cards[5]; //所有网卡地址信息
}JNetCardList_t;
typedef struct{
    char ssid[64];   // wifi名称
    int quality;     // 信号质量：0-100
    int keystat;     // 密钥状态：0无需密码，非0需要密码
    char iestat[32]; // 加密模式：open,shared,wep,wpa,wpa2,plain
    char mode[8];    // 网卡模式：sta,ap
}JNetWlan_t;// 无线网络信息
typedef struct {
    char iccid[32]; // 卡id
    char mode[8];   // 模式：4G/5G
    int quality;    // 信号质量
} JNetMobile_t;// 移动网络信息


#ifdef __cplusplus
}
#endif
#endif // __JNETWORK_DEFINE_H__
