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
                e::system::string DateTimeToString(e::system::datetime value, std::optional<int> mode = ConvertDateTime);
                e::system::datetime Now();
                e::system::datetime GetTimePart(e::system::datetime x);
                e::system::datetime GetDatePart(e::system::datetime x);
                e::system::datetime BuildDateTime(int32_t year, std::optional<int32_t> month = 1, std::optional<int32_t> day = 1, std::optional<int32_t> hour = 0, std::optional<int32_t> minute = 0, std::optional<int32_t> second = 0);
                int32_t GetHourPart(e::system::datetime value);
                int32_t GetMinutePart(e::system::datetime value);
                int32_t GetSecondPart(e::system::datetime value);
            }
        }
    }
}