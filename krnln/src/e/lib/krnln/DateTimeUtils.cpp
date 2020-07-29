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

    std::ostringstream s;
    if (convertDate)
    {
        int32_t year, month, day;
        value.get_date_part(&year, &month, &day);
        s << year << "年" << month << "月" << day << "日";
    }
    if (convertTime)
    {
        int32_t hour, minute, second;
        value.get_time_part(&hour, &minute, &second);
        if (hour | minute | second)
        {
            s << hour << "时" << minute << "分" << second << "秒";
        }
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
    return e::system::datetime(
        year,
        month.value_or(1),
        day.value_or(1),
        hour.value_or(0),
        minute.value_or(0),
        second.value_or(0));
}

int32_t e::lib::krnln::DateTimeUtils::GetYearPart(e::system::datetime value)
{
    return value.year();
}

int32_t e::lib::krnln::DateTimeUtils::GetMonthPart(e::system::datetime value)
{
    return value.month();
}

int32_t e::lib::krnln::DateTimeUtils::GetDayPart(e::system::datetime value)
{
    return value.day();
}

int32_t e::lib::krnln::DateTimeUtils::GetHourPart(e::system::datetime value)
{
    return value.hour();
}

int32_t e::lib::krnln::DateTimeUtils::GetMinutePart(e::system::datetime value)
{
    return value.minute();
}

int32_t e::lib::krnln::DateTimeUtils::GetSecondPart(e::system::datetime value)
{
    return value.second();
}

int32_t e::lib::krnln::DateTimeUtils::DayOfWeek(e::system::datetime value)
{
    return value.day_of_week();
}