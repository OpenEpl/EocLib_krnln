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
    return e::system::datetime(std::modf(x.value, &intpart) + 36526.0 /* 2000年1月1日 */);
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

int32_t e::lib::krnln::DateTimeUtils::Tick()
{
    return static_cast<int32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
}