#pragma once
#include <functional>
#include <e/system/basic_type.h>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace BinUtils
            {
                intptr_t Len(const e::system::bin &x);
                e::system::bin Left(const e::system::bin &x, intptr_t length);
                e::system::bin Right(const e::system::bin &x, intptr_t length);
                e::system::bin SubBin(const e::system::bin &x, intptr_t start, intptr_t length);
                e::system::bin Space(intptr_t length);
                e::system::bin Repeat(intptr_t times, const e::system::bin &x);
                intptr_t IndexOf(const e::system::bin &haystack, const e::system::bin &needle, std::optional<intptr_t> startIndex = std::nullopt);
                intptr_t LastIndexOf(const e::system::bin &haystack, const e::system::bin &needle, std::optional<intptr_t> startIndex = std::nullopt);
                e::system::bin Replace(const e::system::bin &x,
                    intptr_t start,
                    intptr_t length,
                    std::optional<std::reference_wrapper<const e::system::bin>> target = std::nullopt);
                inline auto Replace(const e::system::bin &x, intptr_t start, intptr_t length, const e::system::bin &target)
                {
                    return Replace(x, start, length, std::optional(std::cref(target)));
                }
                e::system::array<e::system::bin> Split(const e::system::bin &x,
                    std::optional<std::reference_wrapper<const e::system::bin>> separator = std::nullopt,
                    std::optional<intptr_t> limit = std::nullopt);
                inline auto Split(const e::system::bin &x, const e::system::bin &separator, std::optional<intptr_t> limit = std::nullopt)
                {
                    return Split(x, std::optional(std::cref(separator)), limit);
                }
                e::system::bin ReplaceSubBin(const e::system::bin &x,
                    const e::system::bin &oldBin,
                    std::optional<std::reference_wrapper<const e::system::bin>> newBin = std::nullopt,
                    std::optional<intptr_t> startIndex = std::nullopt,
                    std::optional<intptr_t> limit = std::nullopt);
                inline auto ReplaceSubBin(const e::system::bin &x,
                    const e::system::bin &oldBin,
                    const e::system::bin &newBin,
                    std::optional<intptr_t> startIndex = std::nullopt,
                    std::optional<intptr_t> limit = std::nullopt)
                {
                    return ReplaceSubBin(x, oldBin, std::optional(std::cref(newBin)), startIndex, limit);
                }
                e::system::any GetDataFromBin(const e::system::bin &from, int32_t type, std::optional<std::reference_wrapper<int32_t>> pos = std::nullopt);
            }
        }
    }
}