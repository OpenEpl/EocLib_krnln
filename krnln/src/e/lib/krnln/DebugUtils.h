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

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#define EOC_DEBUGBREAK_ALWAYS() __debugbreak()
#elif defined(__i386__) || defined(__x86_64__)
static inline void EOC_DEBUGBREAK_ALWAYS()
{
    __asm__ __volatile__("int $03");
}
#elif defined(__thumb__)
static inline void EOC_DEBUGBREAK_ALWAYS()
{
    __asm__ __volatile__(".inst 0xde01");
}
#elif defined(__aarch64__)
static inline void EOC_DEBUGBREAK_ALWAYS()
{
    __asm__ __volatile__(".inst 0xd4200000");
}
#elif defined(__arm__)
static inline void EOC_DEBUGBREAK_ALWAYS()
{
    __asm__ __volatile__(".inst 0xe7f001f0");
}
#else
#include <signal.h>
#if defined(SIGTRAP)
#define EOC_DEBUGBREAK_ALWAYS() raise(SIGTRAP)
#else
#define EOC_DEBUGBREAK_ALWAYS() raise(SIGABRT)
#endif
#endif

#define EOC_ASSERT_ALWAYS(condition) if(condition) EOC_DEBUGBREAK_ALWAYS()

#if _DEBUG
#define EOC_OUTPUT_DEBUG_INFO(...) e::lib::krnln::DebugUtils::OutputDebugInfo(__VA_ARGS__)
#define EOC_DEBUGBREAK(...) EOC_DEBUGBREAK_ALWAYS(__VA_ARGS__)
#define EOC_ASSERT(...) EOC_ASSERT_ALWAYS(__VA_ARGS__)
#else
#define EOC_OUTPUT_DEBUG_INFO(...)
#define EOC_DEBUGBREAK(...)
#define EOC_ASSERT(...)
#endif