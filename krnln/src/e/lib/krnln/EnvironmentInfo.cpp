#include "EnvironmentInfo.h"
#include <e/system/func.h>
#include <chrono>
#include <windows.h>

e::system::string e::lib::krnln::EnvironmentInfo::GetStartupPath()
{
    auto buf_raw = std::make_unique<wchar_t[]>(32768);
    auto len = GetModuleFileNameW(0, buf_raw.get(), 32768);
    buf_raw[len] = L'\0'; //For XP
    auto buf_long = std::make_unique<wchar_t[]>(32768);
    std::unique_ptr<wchar_t[]> buf;
    if (GetLongPathNameW(buf_raw.get(), buf_long.get(), 32768))
        buf = std::move(buf_long);
    else
        buf = std::move(buf_raw);
    auto x = wcsrchr(buf.get(), L'\\');
    if (x == nullptr)
        return nullptr;
    *x = L'\0';
    return e::system::ReceiveNativeWideString(buf.get());
}

e::system::string e::lib::krnln::EnvironmentInfo::GetExecutableName()
{
    auto buf_raw = std::make_unique<wchar_t[]>(32768);
    auto len = GetModuleFileNameW(0, buf_raw.get(), 32768);
    buf_raw[len] = L'\0'; //For XP
    auto buf_long = std::make_unique<wchar_t[]>(32768);
    std::unique_ptr<wchar_t[]> buf;
    if (GetLongPathNameW(buf_raw.get(), buf_long.get(), 32768))
        buf = std::move(buf_long);
    else
        buf = std::move(buf_raw);
    auto x = wcsrchr(buf.get(), L'\\');
    if (x == nullptr)
        return nullptr;
    return e::system::ReceiveNativeWideString(x + 1);
}

int32_t e::lib::krnln::EnvironmentInfo::Tick()
{
    return static_cast<int32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
}