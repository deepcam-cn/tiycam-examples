
/**
 * @file JCTLV.h
 * @brief tlv数据封装
 * @version 0.1
 * @date 2021-11-10
 * @copyright @ Jovision Technology Co.,Ltd. 2021-. All rights reserved
 *     
 * 
 */
#ifndef AI_TLV_H_
#define AI_TLV_H_

#include <string>
#include "jvtlvtype.h"

class JCTLV
{
public:
    JCTLV(const char *head="META");
    ~JCTLV();
public:
    int AddUInt8Value(int type, uint8_t value);
    int AddUInt16Value(int type, uint16_t value);
    int AddUInt32Value(int type, uint32_t value);
    int AddUInt64Value(int type, uint64_t value);
    int AddFloatValue(int type, float value);
    int AddDoubleValue(int type, double value);
    int AddStringValue(int type, const char *value);
    int AddStringValue(int type, const std::string &value);
    int AddBytesValue(int type, unsigned char *value, int length);
    int AddSizeValue(int type, TLVSize_t *value);
    int AddRectValue(int type, TLVRect_t *value);
    int AddRuleAreasValue(int type, TLVRuleArea_t *areas, uint8_t count);
    int AddObjAreasValue(int type, TLVObjArea_t *areas, uint8_t count);
    //TLV数据
    unsigned char *GetTLVBuffer() const;
    //TLV数据长度
    int GetTLVBytes() const;
    void *GetCHdl() const;
public:
    //解析成TLV
    int ParseToTLV(unsigned char *buff, int len);
    const char *GetHeadType();
    int GetUInt8Value(int type, uint8_t &value) const;
    int GetUInt16Value(int type, uint16_t &value) const;
    int GetUInt32Value(int type, uint32_t &value) const;
    int GetUInt64Value(int type, uint64_t &value) const;
    int GetFloatValue(int type, float &value) const;
    int GetDoubleValue(int type, double &value) const;
    int GetStringValue(int type, std::string &value) const;
    int GetBytesValue(int type, unsigned char *value, int *length) const;
    int GetBytesValue(int type, unsigned char *value, int length) const;
    int GetBytesValuePtr(int type, unsigned char **value, int &length) const;
    int GetSizeValue(int type, TLVSize_t *value);
    int GetRectValue(int type, TLVRect_t *value);
    // areas需要外部free
    int GetRuleAreasValue(int type, TLVRuleArea_t **areas, int *count);
    // areas需要外部free
    int GetObjAreasValue(int type, TLVObjArea_t **areas, int *count);
public:
    int DelType(int type);

private:
    void *m_tlv;
};

#endif