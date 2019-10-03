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
    return MessageBoxW((HWND)handle.value_or(0), contentW.get(), titleW ? titleW.get() : L"–≈œ¢£∫", flags) - 1;
}

void e::lib::krnln::SystemUtils::PlayBeep()
{
    MessageBeep(MB_OK);
}

void e::lib::krnln::SystemUtils::Exit()
{
    std::exit(0);
}
