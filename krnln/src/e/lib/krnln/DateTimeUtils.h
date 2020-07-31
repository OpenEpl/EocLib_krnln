#pragma once
#include <e/system/basic_type.h>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace DateTimeUtils
            {
                const int32_t ConvertDateTime(1);
                const int32_t ConvertDate(2);
                const int32_t ConvertTime(3);
                const int32_t Year(1);
                const int32_t Quarter(2);
                const int32_t Month(3);
                const int32_t CalcWeekOfYear(4);
                const int32_t Week(4);
                const int32_t Day(5);
                const int32_t Hour(6);
                const int32_t Minute(7);
                const int32_t Second(8);
                const int32_t CalcDayOfWeek(9);
                const int32_t CalcDayOfYear(10);
                e::system::string DateTimeToString(e::system::datetime value, std::optional<int> mode = ConvertDateTime);
                e::system::datetime Now();
                e::system::datetime GetTimePart(e::system::datetime x);
                e::system::datetime GetDatePart(e::system::datetime x);
                e::system::datetime BuildDateTime(int32_t year, std::optional<int32_t> month = 1, std::optional<int32_t> day = 1, std::optional<int32_t> hour = 0, std::optional<int32_t> minute = 0, std::optional<int32_t> second = 0);
                int32_t GetYearPart(e::system::datetime value);
                int32_t GetMonthPart(e::system::datetime value);
                int32_t GetDayPart(e::system::datetime value);
                int32_t GetHourPart(e::system::datetime value);
                int32_t GetMinutePart(e::system::datetime value);
                int32_t GetSecondPart(e::system::datetime value);
                int32_t DayOfWeek(e::system::datetime value);
                int32_t DaysInMonth(int32_t year, int32_t month);
                double GetDistance(e::system::datetime x, e::system::datetime y, int32_t type);
                int32_t GetSpecificPart(e::system::datetime x, int32_t type);
                e::system::datetime DateAdd(e::system::datetime x, int32_t type, int32_t interval);
            }
        }
    }
}