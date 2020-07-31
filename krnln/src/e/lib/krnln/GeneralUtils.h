#pragma once
#include <e/system/basic_type.h>
#include <utility>
namespace e::lib::krnln::GeneralUtils
{
    // This function is VERY DANGEROUS and SHOULD NOT BE USED unless you must use it.
    // It can damage the data that the object saves.
    // Make sure you have a good knowledge of the internal data structure before using.
    template <typename T1, typename T2>
    void ForceSwap(T1 &a, T2 &b) noexcept
    {
        static_assert(sizeof(T1) == sizeof(T2), "ForceSwap's parameter must be the same size");
        uint8_t temp[sizeof(T1)];
        memcpy(&temp, &a, sizeof(T1));
        memcpy(&a, &b, sizeof(T1));
        memcpy(&b, &temp, sizeof(T1));
    }
}