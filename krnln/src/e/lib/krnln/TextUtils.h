#pragma once
#include <functional>
#include <e/system/basic_type.h>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace TextUtils
            {
                e::system::string Char(uint8_t x);
                int32_t GetCodePoint(const e::system::string &x, std::optional<intptr_t> pos = std::nullopt);
                intptr_t Len(const e::system::string &x);
                e::system::string Left(const e::system::string &x, intptr_t length);
                e::system::string Right(const e::system::string &x, intptr_t length);
                e::system::string SubStr(const e::system::string &x, intptr_t start, intptr_t length);
                intptr_t IndexOf(const e::system::string &str, const e::system::string &subStr, std::optional<intptr_t> startIndex = std::nullopt, std::optional<bool> caseInsensitive = std::nullopt);
                intptr_t LastIndexOf(const e::system::string &str, const e::system::string &subStr, std::optional<intptr_t> startIndex = std::nullopt, std::optional<bool> caseInsensitive = std::nullopt);
                e::system::string ToLower(const e::system::string &x);
                e::system::string ToUpper(const e::system::string &x);
                e::system::string Space(intptr_t length);
                e::system::string Repeat(intptr_t times, const e::system::string &x);
                e::system::string Replace(const e::system::string &x,
                    intptr_t start,
                    intptr_t length,
                    std::optional<std::reference_wrapper<const e::system::string>> target = std::nullopt);
                inline auto Replace(const e::system::string &x, intptr_t start, intptr_t length, const e::system::string &target)
                {
                    return Replace(x, start, length, std::optional(std::cref(target)));
                }
                e::system::array<e::system::string> Split(const e::system::string &x,
                    std::optional<std::reference_wrapper<const e::system::string>> separator = std::nullopt,
                    std::optional<intptr_t> limit = std::nullopt);
                inline auto Split(const e::system::string &x, const e::system::string &separator, std::optional<intptr_t> limit = std::nullopt)
                {
                    return Split(x, std::optional(std::cref(separator)), limit);
                }
                e::system::string ReplaceSubText(const e::system::string &x,
                    const e::system::string &oldText,
                    std::optional<std::reference_wrapper<const e::system::string>> newText = std::nullopt,
                    std::optional<intptr_t> startIndex = std::nullopt,
                    std::optional<intptr_t> limit = std::nullopt,
                    std::optional<bool> caseSensitive = std::nullopt);
                inline auto ReplaceSubText(const e::system::string &x,
                    const e::system::string &oldText,
                    const e::system::string &newText,
                    std::optional<intptr_t> startIndex = std::nullopt,
                    std::optional<intptr_t> limit = std::nullopt,
                    std::optional<bool> caseSensitive = std::nullopt)
                {
                    return ReplaceSubText(x, oldText, std::optional(std::cref(newText)), startIndex, limit, caseSensitive);
                }
            }
        }
    }
}