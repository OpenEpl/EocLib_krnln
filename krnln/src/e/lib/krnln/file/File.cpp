#include "File.h"
#include <windows.h>
#include <limits>
#include <algorithm>

//避免Windows.h的污染
#undef max
#undef min

e::lib::krnln::File::File()
{
    this->handle = 0;
}

e::lib::krnln::File::File(intptr_t handle)
{
    this->handle = handle;
}

e::lib::krnln::File::File(File &&file) noexcept
{
    this->handle = file.handle;
    file.handle = 0;
}

e::lib::krnln::File &e::lib::krnln::File::operator=(File &&file) noexcept
{
    if (this->handle)
        CloseHandle((HANDLE)this->handle);
    this->handle = file.handle;
    file.handle = 0;
    return *this;
}

e::lib::krnln::File::~File()
{
    if (this->handle)
        CloseHandle((HANDLE)this->handle);
}

size_t e::lib::krnln::File::Read(void *buffer, size_t length)
{
    DWORD bufferSize = static_cast<DWORD>(std::min<size_t>(length, std::numeric_limits<DWORD>::max()));
    DWORD numOfRead;
    if (!ReadFile((HANDLE)handle, buffer, bufferSize, &numOfRead, NULL))
    {
        throw std::runtime_error("Failed to read");
    }
    return numOfRead;
}

void e::lib::krnln::File::Write(const void *buffer, size_t length)
{
    DWORD numOfWritten;

    while (length)
    {
        DWORD bufferSize = static_cast<DWORD>(std::min<size_t>(length, std::numeric_limits<DWORD>::max()));
        if (!WriteFile((HANDLE)handle, buffer, bufferSize, &numOfWritten, NULL))
        {
            throw std::runtime_error("Failed to write");
        }
        length -= numOfWritten;
        buffer = &static_cast<const uint8_t *>(buffer)[numOfWritten];
    }
}

unsigned long long e::lib::krnln::File::GetLength()
{
    LARGE_INTEGER length;
    if (!GetFileSizeEx((HANDLE)handle, &length))
    {
        throw std::runtime_error("Failed to get file size");
    }
    return static_cast<unsigned long long>(length.QuadPart);
}

unsigned long long e::lib::krnln::File::GetPosition()
{
    LARGE_INTEGER li;
    li.QuadPart = 0;
    li.LowPart = SetFilePointer((HANDLE)handle, li.LowPart, &li.HighPart, FILE_CURRENT);
    if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
    {
        throw std::runtime_error("Failed to get file pointer");
    }
    return static_cast<unsigned long long>(li.QuadPart);
}

void e::lib::krnln::File::Seek(long long offset, SeekOrigin whence)
{
    DWORD moveMethod;
    switch (whence)
    {
    case SeekOrigin::Begin:
        moveMethod = FILE_BEGIN;
        break;
    case SeekOrigin::End:
        moveMethod = FILE_END;
        break;
    case SeekOrigin::Current:
        moveMethod = FILE_CURRENT;
        break;
    default:
        return;
    }

    LARGE_INTEGER li;
    li.QuadPart = offset;
    li.LowPart = SetFilePointer((HANDLE)handle, li.LowPart, &li.HighPart, moveMethod);
    if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
    {
        throw std::runtime_error("Failed to set file pointer");
    }
}

void e::lib::krnln::File::SetPosition(unsigned long long newPosition)
{
    e::lib::krnln::File::Seek(newPosition, SeekOrigin::Begin);
}

void e::lib::krnln::File::Flush()
{
    FlushFileBuffers((HANDLE)handle);
}

e::lib::krnln::File e::lib::krnln::File::Open(const e::system::string &filePath, FileAccessMode accessMode, FileShareMode shareMode)
{
    DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;
    switch (accessMode)
    {
    case FileAccessMode::ReadOnly:
        dwDesiredAccess = GENERIC_READ;
        dwCreationDisposition = OPEN_EXISTING;
        break;
    case FileAccessMode::WriteOnly:
        dwDesiredAccess = GENERIC_WRITE;
        dwCreationDisposition = OPEN_EXISTING;
        break;
    case FileAccessMode::ReadWrite:
        dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
        dwCreationDisposition = OPEN_EXISTING;
        break;
    case FileAccessMode::Rewrite:
        dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
        dwCreationDisposition = CREATE_ALWAYS;
        break;
    case FileAccessMode::WriteAlways:
        dwDesiredAccess = GENERIC_WRITE;
        dwCreationDisposition = OPEN_ALWAYS;
        break;
    case FileAccessMode::Edit:
        dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
        dwCreationDisposition = OPEN_ALWAYS;
        break;
    }
    switch (shareMode)
    {
    case FileShareMode::Unlimited:
        dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
        break;
    case FileShareMode::ShareRead:
        dwShareMode = FILE_SHARE_READ;
        break;
    case FileShareMode::ShareWrite:
        dwShareMode = FILE_SHARE_WRITE;
        break;
    case FileShareMode::Exclusive:
        dwShareMode = 0;
        break;
    }
    auto pathW = e::system::ToNativeWideString(filePath);
    intptr_t handle = (intptr_t)CreateFileW(pathW.get(), dwDesiredAccess, dwShareMode, nullptr, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
    if (handle == 0 || handle == (intptr_t)INVALID_HANDLE_VALUE)
        throw std::runtime_error("Unable to open file");
    return File(handle);
}

void e::lib::krnln::File::SetLength(unsigned long long length)
{
    auto rawPoint = GetPosition();
    SetPosition(length);
    SetEndOfFile((HANDLE)handle);
    SetPosition(std::min(rawPoint, length));
}