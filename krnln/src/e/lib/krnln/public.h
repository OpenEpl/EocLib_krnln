#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
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
#include "ConsoleUtils.h"
#include "file/FileUtils.h"
#include "EnvironmentInfo.h"
#include "com/COMObject.h"
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace constant
            {
                const e::system::string NewLine("\r\n");

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
            e::system::any GetDataFromBin(const e::system::bin &from, int32_t type, std::optional<std::reference_wrapper<int32_t>> pos = std::nullopt);
        }
    }
}