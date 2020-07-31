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

inline bool IsLeapYear(int32_t year)
{
    return ((year % 4) == 0) && ((year % 100) != 0 || (year % 400) == 0);
}

int32_t e::lib::krnln::DateTimeUtils::DaysInMonth(int32_t year, int32_t month)
{
    constexpr int32_t daysInMonthOfRegularYear[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12)
    {
        throw std::invalid_argument("month is out of range");
    }
    int32_t result = daysInMonthOfRegularYear[month - 1];
    if (month == 2)
    {
        if (IsLeapYear(year))
        {
            result++;
        }
    }
    return result;
}

// Note that the result is calculated based on year only
// The distance can be 1 even though they are only one day apart
inline double DateTimeDistanceInYear(e::system::datetime x, e::system::datetime y)
{
    return x.year() - y.year();
}

// Note that the result is calculated based on year and month only
// The distance can be 1 even though they are only one day apart
inline double DateTimeDistanceInQuarter(e::system::datetime x, e::system::datetime y)
{
    int32_t x_year, x_month, y_year, y_month;
    x.get_date_part(&x_year, &x_month, nullptr);
    y.get_date_part(&y_year, &y_month, nullptr);
    return (x_year - y_year) * 4 + (x_month - 1) / 3 - (y_month - 1) / 3;
}

// Note that the result is calculated based on year and month only
// The distance can be 1 even though they are only one day apart
inline double DateTimeDistanceInMonth(e::system::datetime x, e::system::datetime y)
{
    int32_t x_year, x_month, y_year, y_month;
    x.get_date_part(&x_year, &x_month, nullptr);
    y.get_date_part(&y_year, &y_month, nullptr);
    return (x_year - y_year) * 12 + x_month - y_month;
}

// Note that the distance is between x's week number and y's week number
// eg.
// 1) Saturday, Aug. 8, 2020 is in the same week as that of Friday, Aug. 7, 2020, so the distance is 0
// 2) Sunday, Aug. 9, 2020 is in the next week of that of Friday, Aug. 7, 2020, so the distance is 1, even though they are only two days apart
inline double DateTimeDistanceInWeek(e::system::datetime x, e::system::datetime y)
{
    return std::trunc((x.value - 1) / 7) - std::trunc((y.value - 1) / 7);
}

// Note that the result contains decimals
// eg. The distance between 18:00 and 15:00 (in the same day, of course) is 0.125
inline double DateTimeDistanceInDay(e::system::datetime x, e::system::datetime y)
{
    double dataPart_x;
    double timePart_x = std::fabs(std::modf(x.value, &dataPart_x));
    double dataPart_y;
    double timePart_y = std::fabs(std::modf(y.value, &dataPart_y));
    return dataPart_x - dataPart_y + timePart_x - timePart_y;
}

// Note that the result is truncated to an integer
inline double DateTimeDistanceInHour(e::system::datetime x, e::system::datetime y)
{
    return std::trunc(DateTimeDistanceInDay(x, y) * 24);
}

// Note that the result is truncated to an integer
inline double DateTimeDistanceInMinute(e::system::datetime x, e::system::datetime y)
{
    return std::trunc(DateTimeDistanceInDay(x, y) * 24 * 60);
}

// Note that the result is rounded (not truncated) to an integer
inline double DateTimeDistanceInSecond(e::system::datetime x, e::system::datetime y)
{
    return std::round(DateTimeDistanceInDay(x, y) * 24 * 60 * 60);
}

double e::lib::krnln::DateTimeUtils::GetDistance(e::system::datetime x, e::system::datetime y, int32_t type)
{
    switch (type)
    {
    case Year:
        return DateTimeDistanceInYear(x, y);
    case Quarter:
        return DateTimeDistanceInQuarter(x, y);
    case Month:
        return DateTimeDistanceInMonth(x, y);
    case Week:
        return DateTimeDistanceInWeek(x, y);
    case Day:
        return DateTimeDistanceInDay(x, y);
    case Hour:
        return DateTimeDistanceInHour(x, y);
    case Minute:
        return DateTimeDistanceInMinute(x, y);
    case Second:
        return DateTimeDistanceInSecond(x, y);
    default:
        throw std::invalid_argument("unknown distance type for datetime");
    }
}

int32_t e::lib::krnln::DateTimeUtils::GetSpecificPart(e::system::datetime x, int32_t type)
{
    switch (type)
    {
    case Year:
        return x.year();
    case Quarter:
        return (x.month() + 2) / 3;
    case Month:
        return x.month();
    case CalcWeekOfYear:
        return (x.day_of_year() + 6) / 7;
    case Day:
        return x.day();
    case Hour:
        return x.hour();
    case Minute:
        return x.minute();
    case Second:
        return x.second();
    case CalcDayOfWeek:
        return x.day_of_week();
    case CalcDayOfYear:
        return x.day_of_year();
    default:
        throw std::invalid_argument("unknown part type for datetime");
    }
}

inline e::system::datetime AddYear(e::system::datetime x, int32_t interval)
{
    int32_t year, month, day;
    x.get_date_part(&year, &month, &day);
    year += interval;
    if (month == 2 && day == 29)
    {
        if (!IsLeapYear(year))
        {
            day--;
        }
    }
    e::system::datetime result(year, month, day);
    double originalDatePart;
    result.value += std::copysign(std::modf(x.value, &originalDatePart), result.value);
    return result;
}

inline e::system::datetime AddMonth(e::system::datetime x, int32_t interval)
{
    int32_t year, month, day;
    x.get_date_part(&year, &month, &day);

    month = year * 12 + month + interval - 1;
    year = month / 12;
    month = month % 12 + 1;

    int32_t maxDay = e::lib::krnln::DateTimeUtils::DaysInMonth(year, month);
    if (day > maxDay)
    {
        day = maxDay;
    }
    e::system::datetime result(year, month, day);
    double originalDatePart;
    result.value += std::copysign(std::modf(x.value, &originalDatePart), result.value);
    return result;
}

inline e::system::datetime AddDay(e::system::datetime x, int32_t interval)
{
    double datePart;
    double timePartWithSign = std::modf(x.value, &datePart);
    datePart += interval;
    return e::system::datetime(datePart + std::copysign(timePartWithSign, datePart));
}

inline e::system::datetime AddDay(e::system::datetime x, double interval)
{
    double datePart;
    double timePart = std::fabs(std::modf(x.value, &datePart));
    double offset = datePart + timePart + interval;
    datePart = std::floor(offset);
    timePart = offset - datePart;
    return e::system::datetime(datePart + std::copysign(timePart, datePart));
}

e::system::datetime e::lib::krnln::DateTimeUtils::DateAdd(e::system::datetime x, int32_t type, int32_t interval)
{
    switch (type)
    {
    case Year:
        return AddYear(x, interval);
    case Quarter:
        return AddMonth(x, interval * 3);
    case Month:
        return AddMonth(x, interval);
    case Week:
        return AddDay(x, interval * 7);
    case Day:
        return AddDay(x, interval);
    case Hour:
        return AddDay(x, interval / (double)24);
    case Minute:
        return AddDay(x, interval / (double)(24 * 60));
    case Second:
        return AddDay(x, interval / (double)(24 * 60 * 60));
    default:
        throw std::invalid_argument("unknown distance type for datetime");
    }
}