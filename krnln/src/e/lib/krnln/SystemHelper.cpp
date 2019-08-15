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

e::system::string e::lib::krnln::SystemUtils::GetStartupPath()
{
    auto buf_raw = std::make_unique<wchar_t[]>(32768 + 1);
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

e::system::string e::lib::krnln::SystemUtils::GetExecutableName()
{
    auto buf_raw = std::make_unique<wchar_t[]>(32768 + 1);
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

void e::lib::krnln::SystemUtils::Exit()
{
    std::exit(0);
}
