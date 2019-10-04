#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
#include <iostream>
#include <cmath>
#include "Converter.h"
#include "DateTimeUtils.h"
#include "ArrayUtils.h"
#include "TextUtils.h"
#include "BinUtils.h"
#include "MemoryUtils.h"
#include "RandomUtils.h"
#include "DebugUtils.h"
#include "ThreadUtils.h"
#include "LogicUtils.h"
#include "SystemHelper.h"
#include "MathUtils.h"
#include "file/FileUtils.h"
#include "EnvironmentInfo.h"
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace constant
            {
                const e::system::string NewLine("\r\n");

                const int32_t StdOut(1);
                const int32_t StdErr(2);

                const int32_t UInt8Type(1);
                const int32_t Int16Type(2);
                const int32_t Int32Type(3);
                const int32_t Int64Type(4);
                const int32_t FloatType(5);
                const int32_t DoubleType(6);
                const int32_t BoolType(7);
                const int32_t DateTimeType(8);
                const int32_t MethodPtrType(9);
                const int32_t StringType(10);
            }
            inline void Print(std::optional<int32_t> 输出方向)
            {
                return;
            }
            template <class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
            inline void Print(std::optional<int32_t> 输出方向, T 欲输出内容)
            {
                std::ostream &out = 输出方向.value_or(constant::StdOut) == constant::StdOut ? std::cout : std::cerr;
                out << 欲输出内容;
            }
            inline void Print(std::optional<int32_t> 输出方向, bool 欲输出内容)
            {
                std::ostream &out = 输出方向.value_or(constant::StdOut) == constant::StdOut ? std::cout : std::cerr;
                out << (欲输出内容 ? "真" : "假");
            }
            inline void Print(std::optional<int32_t> 输出方向, const e::system::string &欲输出内容)
            {
                std::ostream &out = 输出方向.value_or(constant::StdOut) == constant::StdOut ? std::cout : std::cerr;
                if (欲输出内容.isEmpty())
                    out << "";
                else
                    out << 欲输出内容.c_str();
            }
            inline void Print(std::optional<int32_t> 输出方向, e::system::datetime 欲输出内容)
            {
                std::ostream &out = 输出方向.value_or(constant::StdOut) == constant::StdOut ? std::cout : std::cerr;
                out << "e::system::datetime(" << 欲输出内容.value << ")";
            }
            inline void Print(std::optional<int32_t> 输出方向, const e::system::any &欲输出内容)
            {
                if (欲输出内容.type() == typeid(int32_t))
                {
                    Print(输出方向, 欲输出内容.cast<int32_t>());
                    return;
                }
                if (欲输出内容.type() == typeid(uint8_t))
                {
                    Print(输出方向, 欲输出内容.cast<uint8_t>());
                    return;
                }
                if (欲输出内容.type() == typeid(int16_t))
                {
                    Print(输出方向, 欲输出内容.cast<int16_t>());
                    return;
                }
                if (欲输出内容.type() == typeid(int64_t))
                {
                    Print(输出方向, 欲输出内容.cast<int64_t>());
                    return;
                }
                if (欲输出内容.type() == typeid(double))
                {
                    Print(输出方向, 欲输出内容.cast<double>());
                    return;
                }
                if (欲输出内容.type() == typeid(float))
                {
                    Print(输出方向, 欲输出内容.cast<float>());
                    return;
                }
                if (欲输出内容.type() == typeid(bool))
                {
                    Print(输出方向, 欲输出内容.cast<bool>());
                    return;
                }
                if (欲输出内容.type() == typeid(e::system::string))
                {
                    Print(输出方向, 欲输出内容.cast<e::system::string>());
                    return;
                }
                Print(输出方向, 欲输出内容.cast<e::system::datetime>());
            }
            template <typename Arg1, typename Arg2, typename... MoreArgs>
            void Print(std::optional<int32_t> 输出方向, const Arg1 &arg1, const Arg2 &arg2, const MoreArgs &... moreArgs)
            {
                [[maybe_unused]] int dummy[] = {
                    (Print(输出方向, arg1), 0),
                    (Print(输出方向, arg2), 0),
                    (Print(输出方向, moreArgs), 0)...};
            }
            e::system::string Input(std::optional<bool> echo = std::nullopt);
            e::system::any GetDataFromBin(const e::system::bin &from, int32_t type, std::optional<std::reference_wrapper<int32_t>> pos = std::nullopt);
        }
    }
}