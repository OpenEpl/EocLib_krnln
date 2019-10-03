#include "DebugUtils.h"
#include <windows.h>
void e::lib::krnln::DebugUtils::OutputDebugInfo(const e::system::string &x)
{
    OutputDebugStringA(x.c_str());
    OutputDebugStringA("\r\n");
}
