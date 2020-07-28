#include "SystemHelper.h"
#include "Windows.h"
#include <cstdlib>
#include <e/system/func.h>

int32_t e::lib::krnln::SystemUtils::ShowMessageBox(const e::system::string &content,
    int32_t flags,
    std::optional<std::reference_wrapper<const e::system::string>> title,
    std::optional<intptr_t> handle)
{
    auto contentW = e::system::ToNativeWideString(content);
    std::unique_ptr<wchar_t[]> titleW;
    if (title.has_value())
        titleW = e::system::ToNativeWideString(title.value());
    return MessageBoxW((HWND)handle.value_or(0), contentW.get(), titleW ? titleW.get() : L"信息：", flags) - 1;
}

void e::lib::krnln::SystemUtils::PlayBeep()
{
    MessageBeep(MB_OK);
}

void e::lib::krnln::SystemUtils::Exit()
{
    std::exit(0);
}

int32_t e::lib::krnln::SystemUtils::GetScreenWidth()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

int32_t e::lib::krnln::SystemUtils::GetScreenHeight()
{
    return GetSystemMetrics(SM_CYSCREEN);
}

int32_t e::lib::krnln::SystemUtils::GetCursorXPos()
{
    POINT point;
    if (GetCursorPos(&point))
    {
        return point.x;
    }
    else
    {
        return 0;
    }
}

int32_t e::lib::krnln::SystemUtils::GetCursorYPos()
{
    POINT point;
    if (GetCursorPos(&point))
    {
        return point.y;
    }
    else
    {
        return 0;
    }
}

int32_t e::lib::krnln::SystemUtils::GetDisplayColorCount()
{
    auto hdc = GetDC(nullptr);
    auto result = GetDeviceCaps(hdc, COLORRES);
    ReleaseDC(nullptr, hdc);
    return (1 << result);
}

int32_t e::lib::krnln::SystemUtils::GetLastSystemError()
{
    return GetLastError();
}
