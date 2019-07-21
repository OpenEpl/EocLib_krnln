#define _CRT_SECURE_NO_WARNINGS

#include "Converter.h"
#include "DateTimeUtils.h"
#include <e/system/func.h>
#include <string>

int32_t e::lib::krnln::ToInt32(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToInt32(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToInt32(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToInt32(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToInt32(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToInt32(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToInt32(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToInt32(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToInt32(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToInt32(value.cast<e::system::methodptr>());
    }
    return 0;
}

int16_t e::lib::krnln::ToInt16(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToInt16(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToInt16(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToInt16(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToInt16(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToInt16(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToInt16(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToInt16(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToInt16(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToInt16(value.cast<e::system::methodptr>());
    }
    return 0;
}

int64_t e::lib::krnln::ToInt64(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToInt64(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToInt64(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToInt64(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToInt64(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToInt64(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToInt64(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToInt64(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToInt64(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToInt64(value.cast<e::system::methodptr>());
    }
    return 0;
}

intptr_t e::lib::krnln::ToIntPtr(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToIntPtr(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToIntPtr(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToIntPtr(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToIntPtr(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToIntPtr(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToIntPtr(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToIntPtr(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToIntPtr(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToIntPtr(value.cast<e::system::methodptr>());
    }
    return 0;
}

uint8_t e::lib::krnln::ToUInt8(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToUInt8(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToUInt8(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToUInt8(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToUInt8(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToUInt8(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToUInt8(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToUInt8(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToUInt8(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToUInt8(value.cast<e::system::methodptr>());
    }
    return 0;
}

double e::lib::krnln::ToDouble(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToDouble(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToDouble(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToDouble(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToDouble(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToDouble(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToDouble(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToDouble(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToDouble(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToDouble(value.cast<e::system::methodptr>());
    }
    return 0;
}

float e::lib::krnln::ToFloat(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToFloat(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToFloat(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToFloat(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToFloat(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToFloat(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToFloat(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToFloat(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToFloat(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToFloat(value.cast<e::system::methodptr>());
    }
    return 0;
}

e::system::bin e::lib::krnln::ToBin(const e::system::any &value)
{
    if (value.type() == typeid(e::system::bin))
    {
        return ToBin(value.cast<e::system::bin>());
    }
    if (value.type() == typeid(uint8_t))
    {
        return ToBin(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToBin(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToBin(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToBin(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToBin(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToBin(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToBin(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToBin(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::methodptr))
    {
        return ToBin(value.cast<e::system::methodptr>());
    }
    return nullptr;
}

e::system::bin e::lib::krnln::ToBin(const e::system::bin &value)
{
    return value;
}

e::system::bin e::lib::krnln::ToBin(bool value)
{
    return e::lib::krnln::ToBin(value ? 1 : 0);
}

e::system::bin e::lib::krnln::ToBin(e::system::datetime value)
{
    return e::system::make_bin(&value.value, sizeof(value.value));
}

e::system::bin e::lib::krnln::ToBin(const e::system::string &value)
{
    return e::system::make_bin(value.c_str(), value.len());
}

e::system::bin e::lib::krnln::ToBin(e::system::methodptr value)
{
    return e::system::make_bin(&value, sizeof(value));
}

e::system::string e::lib::krnln::ToString(uint8_t value)
{
    e::system::string result(3);
    _itoa(value, result.data, 10);
    return result;
}

e::system::string e::lib::krnln::ToString(const e::system::bin &value)
{
    auto length = value.GetSize();
    if (length == 0)
        return nullptr;
    e::system::string result(length);
    std::memcpy(result.c_str(), value.GetElemPtr(), length);
    result.c_str()[length] = '\0';
    return result;
}

e::system::string e::lib::krnln::ToString(const e::system::any &value)
{
    if (value.type() == typeid(uint8_t))
    {
        return ToString(value.cast<uint8_t>());
    }
    if (value.type() == typeid(int16_t))
    {
        return ToString(value.cast<int16_t>());
    }
    if (value.type() == typeid(int32_t))
    {
        return ToString(value.cast<int32_t>());
    }
    if (value.type() == typeid(int64_t))
    {
        return ToString(value.cast<int64_t>());
    }
    if (value.type() == typeid(double))
    {
        return ToString(value.cast<double>());
    }
    if (value.type() == typeid(float))
    {
        return ToString(value.cast<float>());
    }
    if (value.type() == typeid(bool))
    {
        return ToString(value.cast<bool>());
    }
    if (value.type() == typeid(e::system::string))
    {
        return ToString(value.cast<e::system::string>());
    }
    if (value.type() == typeid(e::system::bin))
    {
        return ToString(value.cast<e::system::bin>());
    }
    return nullptr;
}

e::system::string e::lib::krnln::ToString(int16_t value)
{
    e::system::string result(6);
    _itoa(value, result.data, 10);
    return result;
}

e::system::string e::lib::krnln::ToString(int32_t value)
{
    e::system::string result(11);
    _itoa(value, result.data, 10);
    return result;
}

e::system::string e::lib::krnln::ToString(int64_t value)
{
    e::system::string result(20);
    _i64toa(value, result.data, 10);
    return result;
}

e::system::string e::lib::krnln::ToString(float value)
{
    std::string buf = std::to_string(value);
    return e::system::string(buf.c_str());
}

e::system::string e::lib::krnln::ToString(double value)
{
    std::string buf = std::to_string(value);
    return e::system::string(buf.c_str());
}

e::system::string e::lib::krnln::ToString(bool value)
{
    return value ? e::system::string("Õæ") : e::system::string("¼Ù");
}

e::system::string e::lib::krnln::ToString(e::system::datetime value)
{
    return DateTimeUtils::DateTimeToString(value);
}
