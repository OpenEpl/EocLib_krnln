#pragma once
#include <e/system/basic_type.h>
#include <cmath>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace MathUtils
            {
                inline int32_t FloorToInt32(double v)
                {
                    return static_cast<int32_t>(std::floor(v));
                }
                inline int32_t TruncToInt32(double v)
                {
                    return static_cast<int32_t>(std::trunc(v));
                }
                inline double Round(double value, std::optional<int32_t> to = std::nullopt)
                {
                    double places = pow(10.0, to.value_or(0));
                    return round(value * places) / places;
                }
                inline int32_t GetSign(double value)
                {
                    if (value == 0)
                        return 0;
                    return 1 - (((int32_t)std::signbit(value)) << 1);
                }
            }
        }
    }
}