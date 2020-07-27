#pragma once
#include <e/system/basic_type.h>
#include "Converter.h"
namespace e::lib::krnln::ConsoleUtils
{
    namespace constant
    {
        const int32_t StdOut(1);
        const int32_t StdErr(2);
    }

    void Print(std::optional<int32_t> target, const e::system::string &content);
    inline void Print(std::optional<int32_t> target)
    {
        return;
    }
    template <class T, std::enable_if_t<!std::is_same_v<T, e::system::string>, int> = 0>
    inline void Print(std::optional<int32_t> target, T content)
    {
        Print(target, krnln::ToString(content));
    }
    template <typename Arg1, typename Arg2, typename... MoreArgs>
    void Print(std::optional<int32_t> target, const Arg1 &arg1, const Arg2 &arg2, const MoreArgs &... moreArgs)
    {
        [[maybe_unused]] int dummy[] = {
            (Print(target, arg1), 0),
            (Print(target, arg2), 0),
            (Print(target, moreArgs), 0)...};
    }
    e::system::string Input(std::optional<bool> echo = std::nullopt);
}