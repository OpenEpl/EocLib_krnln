#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
#include "Converter.h"
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace DebugUtils
            {
                inline constexpr bool IsDebugMode()
                {
#ifdef _DEBUG
                    return true;
#else
                    return false;
#endif
                }

                inline void OutputDebugInfo()
                {
                }

                void OutputDebugInfo(const e::system::string &x);

                template <typename T>
                void OutputDebugInfo(const T &x)
                {
                    OutputDebugInfo(krnln::ToString(x));
                }

                template <typename Arg1, typename Arg2, typename... MoreArgs>
                void OutputDebugInfo(const Arg1 &arg1, const Arg2 &arg2, const MoreArgs &... moreArgs)
                {
                    int dummy[] = {
                        (OutputDebugInfo(arg1), 0),
                        (OutputDebugInfo(arg2), 0),
                        (OutputDebugInfo(moreArgs), 0)...};
                }
            }
        }
    }
}
#if _DEBUG
#define EOC_OUTPUT_DEBUG_INFO(...) e::lib::krnln::DebugUtils::OutputDebugInfo(__VA_ARGS__)
#else
#define EOC_OUTPUT_DEBUG_INFO(...)
#endif