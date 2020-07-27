#include "ConsoleUtils.h"
#include <e/system/native_string.h>
#include <Windows.h>
namespace e::lib::krnln::ConsoleUtils
{
    e::system::string Input(std::optional<bool> echo)
    {
        auto hInput = GetStdHandle(STD_INPUT_HANDLE);
        if (!hInput)
        {
            return e::system::string(nullptr);
        }
        DWORD mode;
        if (GetConsoleMode(hInput, &mode))
        {
            DWORD newMode = (mode & ~ENABLE_ECHO_INPUT) | ENABLE_LINE_INPUT;
            if (echo.value_or(true))
            {
                newMode |= ENABLE_ECHO_INPUT;
            }
            SetConsoleMode(hInput, newMode);

            constexpr int BUFSIZE = 2048;
            auto contentW = std::make_unique<wchar_t[]>(BUFSIZE);
            DWORD numberOfCharsRead = 0;
            if (ReadConsoleW(hInput, contentW.get(), BUFSIZE, &numberOfCharsRead, nullptr))
            {
                if (numberOfCharsRead > 0 && contentW.get()[numberOfCharsRead - 1] == '\n')
                {
                    numberOfCharsRead--;
                }
                if (numberOfCharsRead > 0 && contentW.get()[numberOfCharsRead - 1] == '\r')
                {
                    numberOfCharsRead--;
                }
            }
            contentW.get()[numberOfCharsRead] = L'\0';

            SetConsoleMode(hInput, mode);
            return e::system::ReceiveNativeWideString(contentW.get());
        }
        else
        {
            constexpr int BUFSIZE = 4096;
            auto contentCP = std::make_unique<char[]>(BUFSIZE);
            char *start = contentCP.get();
            DWORD numberOfBytesRead;
            while (true)
            {
                if (!ReadFile(hInput, start, 1, &numberOfBytesRead, nullptr))
                {
                    *start = '\0';
                    break;
                }
                if (numberOfBytesRead == 0)
                {
                    *start = '\0';
                    break;
                }
                if (*start == '\n')
                {
                    if (start[-1] == '\r')
                    {
                        start--;
                    }
                    *start = '\0';
                    break;
                }
                start++;
                if (start >= contentCP.get() + BUFSIZE)
                {
                    start--;
                    *start = '\0';
                    break;
                }
            }
            int ocpLen = static_cast<int>((start - contentCP.get()) + 1);
            auto cp = GetConsoleCP();
            auto wideLen = MultiByteToWideChar(cp, 0, contentCP.get(), ocpLen, nullptr, 0);
            auto contentW = std::make_unique<wchar_t[]>(wideLen);
            MultiByteToWideChar(cp, 0, contentCP.get(), ocpLen, contentW.get(), wideLen);

            return e::system::ReceiveNativeWideString(contentW.get());
        }
    }

    void Print(std::optional<int32_t> target, const e::system::string &content)
    {
        auto hOutput = GetStdHandle(target.value_or(constant::StdOut) == constant::StdOut ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE);
        if (!hOutput)
        {
            return;
        }
        if (content.isEmpty())
        {
            return;
        }
        auto contentW = e::system::ToNativeWideString(content);
        auto wideLen = int(wcslen(contentW.get()));
        DWORD numberOfCharsWritten;
        if (!WriteConsoleW(hOutput, contentW.get(), wideLen, &numberOfCharsWritten, nullptr))
        {
            auto outCp = GetConsoleOutputCP();
            auto ocpLen = WideCharToMultiByte(outCp, 0, contentW.get(), wideLen, nullptr, 0, nullptr, nullptr);
            if (ocpLen)
            {
                auto contentOCP = std::make_unique<char[]>(ocpLen);
                DWORD numberOfBytesWritten;
                WideCharToMultiByte(outCp, 0, contentW.get(), wideLen, contentOCP.get(), ocpLen, nullptr, nullptr);
                WriteFile(hOutput, contentOCP.get(), ocpLen, &numberOfBytesWritten, nullptr);
            }
        }
    }
}