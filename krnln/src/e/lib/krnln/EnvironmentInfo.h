#pragma once
#include <e/system/basic_type.h>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace EnvironmentInfo
            {
                e::system::string GetStartupPath();
                e::system::string GetExecutableName();
                int32_t Tick();
            }
        }
    }
}