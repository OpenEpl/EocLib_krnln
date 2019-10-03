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
                e::system::string GetCurrentDirectory();
                bool SetCurrentDirectory(const e::system::string &path); 
                int32_t Tick();
                void GetCommandLineArguments(e::system::array<e::system::string> &arguments);
            }
        }
    }
}