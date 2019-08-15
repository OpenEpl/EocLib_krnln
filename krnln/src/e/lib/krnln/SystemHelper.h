#pragma once
#include <e/system/basic_type.h>
#include "Converter.h"
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace SystemUtils
            {
                int32_t ShowMessageBox(const e::system::string &content,
                    int32_t flags,
                    std::optional<std::reference_wrapper<const e::system::string>> title = std::nullopt,
                    std::optional<intptr_t> handle = std::nullopt);
                template <typename T>
                auto ShowMessageBox(T content,
                    int32_t flags,
                    std::optional<std::reference_wrapper<const e::system::string>> title = std::nullopt,
                    std::optional<intptr_t> handle = std::nullopt)
                {
                    return ShowMessageBox(krnln::ToString(std::forward<T>(content)), flags, std::optional(std::cref(title)), handle);
                }
                template <typename T>
                auto ShowMessageBox(T content,
                    int32_t flags,
                    const e::system::string &title,
                    std::optional<intptr_t> handle = std::nullopt)
                {
                    return ShowMessageBox(std::forward<T>(content), flags, std::optional(std::cref(title)), handle);
                }
                void PlayBeep();
                e::system::string GetStartupPath();
                e::system::string GetExecutableName();
                [[noreturn]] void Exit();
            }
        }
    }
}