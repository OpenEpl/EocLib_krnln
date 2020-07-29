#include "DateTimeUtils.h"
#include <Windows.h>
#include <sstream>
#include <cmath>
#include <chrono>
e::system::string e::lib::krnln::DateTimeUtils::DateTimeToString(e::system::datetime value, std::optional<int> mode)
{
    bool convertDate, convertTime;
    switch (mode.value_or(ConvertDateTime))
    {
    case ConvertDate:
        convertDate = true;
        convertTime = false;
        break;
    case ConvertTime:
        convertDate = false;
        convertTime = true;
        break;
    default:
        convertDate = convertTime = true;
        break;
    }

    std::stringstream s;
    SYSTEMTIME info;
    VariantTimeToSystemTime(value.value, &info);
    if (convertDate)
    {
        s << info.wYear;
        s << "年";
        s << info.wMonth;
        s << "月";
        s << info.wDay;
        s << "日";
    }
    if (convertTime && (info.wHour | info.wMinute | info.wSecond))
    {
        s << info.wHour;
        s << "时";
        s << info.wMinute;
        s << "分";
        s << info.wSecond;
        s << "秒";
    }
    return e::system::string(s.str().c_str());
}

e::system::datetime e::lib::krnln::DateTimeUtils::Now()
{
    SYSTEMTIME info;
    e::system::datetime result;
    GetLocalTime(&info);
    SystemTimeToVariantTime(&info, &result.value);
    return result;
}

e::system::datetime e::lib::krnln::DateTimeUtils::GetTimePart(e::system::datetime x)
{
    double intpart;
    return e::system::datetime(std::fabs(std::modf(x.value, &intpart)) + 36526.0 /* 2000年1月1日 */);
}

e::system::datetime e::lib::krnln::DateTimeUtils::GetDatePart(e::system::datetime x)
{
    double intpart;
    std::modf(x.value, &intpart);
    return e::system::datetime(intpart);
}

e::system::datetime e::lib::krnln::DateTimeUtils::BuildDateTime(int32_t year, std::optional<int32_t> month, std::optional<int32_t> day, std::optional<int32_t> hour, std::optional<int32_t> minute, std::optional<int32_t> second)
{
    SYSTEMTIME info = {0};
    e::system::datetime result;
    info.wYear = (WORD)year;
    info.wMonth = (WORD)month.value_or(1);
    info.wDay = (WORD)day.value_or(1);
    info.wHour = (WORD)hour.value_or(0);
    info.wMinute = (WORD)minute.value_or(0);
    info.wSecond = (WORD)second.value_or(0);
    SystemTimeToVariantTime(&info, &result.value);
    return result;
}

inline int32_t GetTotalSecondsInTimePart(e::system::datetime value)
{
    constexpr int32_t totalSecondsPerDay = 24 * 60 * 60;
    double dataPart;
    double timePart = std::modf(value.value, &dataPart);
    int32_t result = static_cast<int32_t>(std::round(totalSecondsPerDay * std::abs(timePart)));
    return result;
}

int32_t e::lib::krnln::DateTimeUtils::GetHourPart(e::system::datetime value)
{
    return GetTotalSecondsInTimePart(value) / 3600;
}

int32_t e::lib::krnln::DateTimeUtils::GetMinutePart(e::system::datetime value)
{
    return (GetTotalSecondsInTimePart(value) / 60) % 60;
}

int32_t e::lib::krnln::DateTimeUtils::GetSecondPart(e::system::datetime value)
{
    return GetTotalSecondsInTimePart(value) % 60;
}

int32_t e::lib::krnln::DateTimeUtils::DayOfWeek(e::system::datetime value)
{
    return (static_cast<int32_t>(std::fmod(value.value, 7)) + 6) % 7 + 1;
}