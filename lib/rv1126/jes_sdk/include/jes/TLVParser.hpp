/***********************************************************************
 * @file TLVParser.hpp
 * @author Lucky(lukai@jovision.com)
 * @brief  header file
 * @version 0.1
 * @date 2022-11-25
 *
 * @copyright @ Jovision Technology Co.,Ltd. 2022-. All rights reserved
 ***********************************************************************/
#pragma once

#include "JCTLV.h"
#include "jtlvproto.h"
#include <jvtypes.h>
#ifndef ERRORF
#define ERRORF printf
#endif

class TLVParser : public JCTLV
{
public:
    TLVParser() {}
    TLVParser(const char *head) : JCTLV(head) {}
    ~TLVParser() {}

public:
    // 配置目标类型
    int SetTarget(MetaTarget_e target)
    {
        if (AddUInt32Value(META_TYPE_TARGET, (int)target) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_TARGET);
            return -1;
        }
        return 0;
    }
    // 配置应用标识
    int SetAiSign(const std::string &name)
    {
        if (AddStringValue(META_TYPE_AI_SIGN, name) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_AI_SIGN);
            return -1;
        }
        return 0;
    }
    // 配置设备ID
    int SetDeviceID(const std::string &devid)
    {
        if (AddStringValue(META_TYPE_DEVICEID, devid) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_DEVICEID);
            return -1;
        }
        return 0;
    }
    // ͨ配置通道ID
    int SetChannelID(int chnl)
    {
        if (AddUInt32Value(META_TYPE_CHANNELID, chnl) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_CHANNELID);
            return -1;
        }
        return 0;
    }
    // ͨ配置通道ID
    int SetChannelSN(const std::string &chnsn)
    {
        if (AddStringValue(META_TYPE_CHANNELSN, chnsn) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_CHANNELSN);
            return -1;
        }
        return 0;
    }
    // 配置时间戳
    int SetPTS(JU64 timestamp)
    {
        if (AddUInt64Value(META_TYPE_PTS, (long long)timestamp) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_PTS);
            return -1;
        }
        return 0;
    }
    // 配置图像大小
    int SetPicSize(JSize_t &pic_size)
    {
        TLVSize_t size = {.w = (uint16_t)pic_size.w, .h = (uint16_t)pic_size.h};
        if (AddSizeValue(META_TYPE_PIC_SIZE, &size) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_PIC_SIZE);
            return -1;
        }
        return 0;
    }
    // 配置区域坐标
    int SetRect(JRect_t &rect)
    {
        TLVRect_t tlvrect = {.x = (uint16_t)rect.x,
                             .y = (uint16_t)rect.y,
                             .w = (uint16_t)rect.w,
                             .h = (uint16_t)rect.h};
        if (AddRectValue(META_TYPE_OBJ_RECT, &tlvrect) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_OBJ_RECT);
            return -1;
        }
        return 0;
    }
    // 配置目标ID
    int SetObjID(JU64 obj_id)
    {
        if (AddUInt64Value(META_TYPE_OBJ_ID, (uint64_t)obj_id) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_OBJ_ID);
            return -1;
        }
        return 0;
    }
    // 配置目标抠图
    int SetObjPic(JU8 *pic, int len)
    {
        if (AddBytesValue(META_TYPE_OBJ_PIC, pic, len) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_OBJ_PIC);
            return -1;
        }
        return 0;
    }
    // 配置整图抓拍
    int SetSnapShot(JU8 *pic, int len)
    {
        if (AddBytesValue(META_TYPE_SNAPSHOT, pic, len) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_SNAPSHOT);
            return -1;
        }
        return 0;
    }
    // 配置目标名称
    int SetObjName(const char *objname)
    {
        if (AddStringValue(META_TYPE_OBJ_NAME, objname) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_OBJ_NAME);
            return -1;
        }
        return 0;
    }

public:
    // 获取目标类型
    int GetTarget(MetaTarget_e &target)
    {
        if (GetUInt32Value(META_TYPE_TARGET, (uint32_t &)target) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_TARGET);
            return -1;
        }
        return 0;
    }
    // 获取应用标识
    int GetAiSign(std::string &name)
    {
        if (GetStringValue(META_TYPE_AI_SIGN, name) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_AI_SIGN);
            return -1;
        }
        return 0;
    }
    // 获取设备ID
    int GetDeviceID(std::string &devid)
    {
        if (GetStringValue(META_TYPE_DEVICEID, devid) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_DEVICEID);
            return -1;
        }
        return 0;
    }
    // ͨ获取通道ID
    int GetChannelID(int &chnl)
    {
        if (GetUInt32Value(META_TYPE_CHANNELID, (uint32_t &)chnl) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_CHANNELID);
            return -1;
        }
        return 0;
    }
    // 获取通道sn
    int GetChannelSN(std::string &chnsn)
    {
        if (GetStringValue(META_TYPE_CHANNELSN, chnsn) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_CHANNELSN);
            return -1;
        }
        return 0;
    }
    // 获取PTS
    int GetPTS(JU64 &timestamp)
    {
        if (GetUInt64Value(META_TYPE_PTS, (uint64_t &)timestamp) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_PTS);
            return -1;
        }
        return 0;
    }
    // 获取图像大小
    int GetPicSize(JSize_t &pic_size)
    {
        TLVSize_t size;
        if (GetSizeValue(META_TYPE_PIC_SIZE, &size) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_PIC_SIZE);
            return -1;
        }
        pic_size.w = size.w;
        pic_size.h = size.h;
        return 0;
    }
    // 获取目标区域坐标
    int GetRect(JRect_t &rect)
    {
        TLVRect_t tlvrect;
        if (GetRectValue(META_TYPE_OBJ_RECT, &tlvrect) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_OBJ_RECT);
            return -1;
        }
        rect.x = tlvrect.x;
        rect.y = tlvrect.y;
        rect.w = tlvrect.w;
        rect.h = tlvrect.h;
        return 0;
    }
    // 获取目标ID
    int GetObjID(JU64 &obj_id)
    {
        if (GetUInt64Value(META_TYPE_OBJ_ID, (uint64_t &)obj_id) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_OBJ_ID);
            return -1;
        }
        return 0;
    }
    // 获取目标抠图
    int GetObjPic(JU8 **pic, int &len)
    {
        if (GetBytesValuePtr(META_TYPE_OBJ_PIC, pic, len) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_OBJ_PIC);
            return -1;
        }
        return 0;
    }
    // 获取整张抓拍图片
    int GetSnapShot(JU8 **pic, int &len)
    {
        if (GetBytesValuePtr(META_TYPE_SNAPSHOT, pic, len) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_SNAPSHOT);
            return -1;
        }
        return 0;
    }
    // 获取目标名称
    int GetObjName(std::string &objname)
    {
        if (GetStringValue(META_TYPE_OBJ_NAME, objname) != 0) {
            return -1;
        }
        return 0;
    }
};

class TLVAlarm : public TLVParser
{
public:
    TLVAlarm() : TLVParser(TLV_HEAD_ALAM) {}
    ~TLVAlarm() {}
    // ͨ配置通道类型：0视频输入，1外部输入，2设备本身
    int SetChannelType(int type)
    {
        if (AddUInt32Value(META_TYPE_CHANNELTYPE, type) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_CHANNELTYPE);
            return -1;
        }
        return 0;
    }
    // ͨ配置抓拍文件本地路径
    int SetSnapfile(const std::string &snapfile)
    {
        if (AddStringValue(META_TYPE_SNAPFILE, snapfile) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_SNAPFILE);
            return -1;
        }
        return 0;
    }
    // ͨ配置报警类型
    int SetAlarmType(const std::string &type)
    {
        if (AddStringValue(TLVALARM_TYPE_TYPE, type) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_TYPE);
            return -1;
        }
        return 0;
    }
    // ͨ配置报警名称：报警名称，字符串形式，需支持多语言，具备自然语言可读性
    int SetAlarmName(const std::string &name)
    {
        if (AddStringValue(TLVALARM_TYPE_NAME, name) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_NAME);
            return -1;
        }
        return 0;
    }
    // 配置报警状态：0stop，1start，2pulse
    int SetAlarmStatus(int status)
    {
        if (AddUInt32Value(TLVALARM_TYPE_STATUS, status) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_STATUS);
            return -1;
        }
        return 0;
    }
    // 配置报警延时：Status=2时有效，表示延时多久结束报警
    int SetAlarmDelay(int delay)
    {
        if (AddUInt32Value(TLVALARM_TYPE_DELAY, delay) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_DELAY);
            return -1;
        }
        return 0;
    }
    // ͨ获取通道类型：0视频输入，1外部输入，2设备本身
    int GetChannelType(int &type)
    {
        if (GetUInt32Value(META_TYPE_CHANNELTYPE, (uint32_t &)type) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", META_TYPE_CHANNELTYPE);
            return -1;
        }
        return 0;
    }
    // 获取抓拍文件本地路径
    int GetSnapfile(std::string &snapfile)
    {
        if (GetStringValue(META_TYPE_SNAPFILE, snapfile) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", META_TYPE_SNAPFILE);
            return -1;
        }
        return 0;
    }
    // ͨ获取报警类型
    int GetAlarmType(std::string &type)
    {
        if (GetStringValue(TLVALARM_TYPE_TYPE, type) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_TYPE);
            return -1;
        }
        return 0;
    }
    // ͨ获取报警名称：报警名称，字符串形式，需支持多语言，具备自然语言可读性
    int GetAlarmName(std::string &name)
    {
        if (GetStringValue(TLVALARM_TYPE_NAME, name) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_NAME);
            return -1;
        }
        return 0;
    }
    // 获取报警状态：0stop，1start，2pulse
    int GetAlarmStatus(int &status)
    {
        if (GetUInt32Value(TLVALARM_TYPE_STATUS, (uint32_t &)status) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_STATUS);
            return -1;
        }
        return 0;
    }
    // 获取报警延时：Status=2时有效，表示延时多久结束报警
    int GetAlarmDelay(int &delay)
    {
        if (GetUInt32Value(TLVALARM_TYPE_DELAY, (uint32_t &)delay) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVALARM_TYPE_DELAY);
            return -1;
        }
        return 0;
    }
};

class TLVFrameArea : public TLVParser
{
public:
    TLVFrameArea() : TLVParser(TLV_HEAD_AREA) {}
    ~TLVFrameArea() {}
    // 配置实时规则区域坐标
    int SetRealTimeRuleArea(TLVRuleArea_t *area, int count)
    {
        if (AddRuleAreasValue(TLVAREA_TYPE_RULE, area, count) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVAREA_TYPE_RULE);
            return -1;
        }
        return 0;
    }
    // 配置实时目标区域坐标
    int SetRealTimeObjArea(TLVObjArea_t *area, int count)
    {
        if (AddObjAreasValue(TLVAREA_TYPE_OBJ, area, count) != 0) {
            ERRORF("tlv_put type[0x%04x] err\n", TLVAREA_TYPE_OBJ);
            return -1;
        }
        return 0;
    }
    // 获取实时规则区域坐标
    int GetRealTimeRuleArea(TLVRuleArea_t **areas, int *count)
    {
        if (GetRuleAreasValue(TLVAREA_TYPE_RULE, areas, count) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", TLVAREA_TYPE_RULE);
            return -1;
        }
        return 0;
    }
    // 获取实时目标区域坐标
    int GetRealTimeObjArea(TLVObjArea_t **areas, int *count)
    {
        if (GetObjAreasValue(TLVAREA_TYPE_OBJ, areas, count) != 0) {
            ERRORF("tlv_get type[0x%04x] err\n", TLVAREA_TYPE_OBJ);
            return -1;
        }
        return 0;
    }
};
