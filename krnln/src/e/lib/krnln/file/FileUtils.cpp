#include "FileUtils.h"
#include <e/system/native_string.h>
#include <windows.h>
#include <rpc.h>

#undef max
#undef min

intptr_t e::lib::krnln::FileUtils::NewMemoryFile()
{
    auto object = static_cast<BaseFile *>(new MemoryFile());
    return reinterpret_cast<intptr_t>(object);
}

intptr_t e::lib::krnln::FileUtils::OpenFile(const e::system::string &filePath, std::optional<int32_t> accessMode, std::optional<int32_t> shareMode)
{
    BaseFile *object;
    try
    {
        object = new File(File::Open(filePath,
            static_cast<FileAccessMode>(accessMode.value_or(1)),
            static_cast<FileShareMode>(shareMode.value_or(1))));
    }
    catch (...)
    {
        object = nullptr;
    }
    return reinterpret_cast<intptr_t>(object);
}

void e::lib::krnln::FileUtils::CloseFile(intptr_t id)
{
    auto object = reinterpret_cast<BaseFile *>(id);
    delete object;
}

e::system::bin e::lib::krnln::FileUtils::ReadData(intptr_t id, int32_t length)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        e::system::bin result((size_t)length);
        auto actualLength = object->Read(result.GetElemPtr(), (size_t)length);
        if (actualLength != (size_t)length)
            result.Redim(true, actualLength);
        return result;
    }
    catch (...)
    {
        return nullptr;
    }
}

bool e::lib::krnln::FileUtils::WriteData(intptr_t id, const e::system::bin &data)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        object->Write(data.GetElemPtr(), data.GetSize());
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool e::lib::krnln::FileUtils::IsEOF(intptr_t id, std::optional<bool> textMode)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        if (textMode.value_or(false))
            return object->IsEndOfTextFile();
        else
            return object->IsEndOfFile();
    }
    catch (...)
    {
        return true;
    }
}

int32_t e::lib::krnln::FileUtils::GetLength(intptr_t id)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        return static_cast<int32_t>(object->GetLength());
    }
    catch (...)
    {
        return -1;
    }
}

int32_t e::lib::krnln::FileUtils::GetPosition(intptr_t id)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        return static_cast<int32_t>(object->GetPosition());
    }
    catch (...)
    {
        return -1;
    }
}

e::system::string e::lib::krnln::FileUtils::ReadText(intptr_t id, std::optional<int32_t> limit)
{
    auto object = reinterpret_cast<BaseFile *>(id);
    if (limit.has_value())
        return object->ReadText(limit.value());
    else
        return object->ReadText();
}

bool e::lib::krnln::FileUtils::Seek(intptr_t id, std::optional<int32_t> whence, int32_t offset)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        object->Seek(offset, whence.has_value() ? static_cast<SeekOrigin>(whence.value()) : SeekOrigin::Current);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool e::lib::krnln::FileUtils::SeekToBegin(intptr_t id)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        object->SeekToBegin();
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool e::lib::krnln::FileUtils::SeekToEnd(intptr_t id)
{
    try
    {
        auto object = reinterpret_cast<BaseFile *>(id);
        object->SeekToEnd();
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool e::lib::krnln::FileUtils::DeleteDiskFile(const e::system::string &path)
{
    auto pathW = e::system::ToNativeWideString(path);
    return DeleteFileW(pathW.get()) != FALSE;
}

e::system::string e::lib::krnln::FileUtils::ReadLine(intptr_t id)
{
    auto object = reinterpret_cast<BaseFile *>(id);
    return object->ReadLine();
}

e::system::string e::lib::krnln::FileUtils::GetTempFile(std::optional<std::reference_wrapper<const e::system::string>> dir)
{
    e::system::string defaultDir;
    if (!dir.has_value())
    {
        auto dirW = std::make_unique<wchar_t[]>(MAX_PATH);
        GetTempPathW(MAX_PATH, dirW.get());
        defaultDir = e::system::ReceiveNativeWideString(dirW.get());
        dir = std::optional(std::cref(defaultDir));
    }
    const e::system::string &dirVal = dir.value().get();
    e::system::string result;

    UUID id;
    RPC_CSTR idStr;
    UuidCreate(&id);
    UuidToStringA(&id, &idStr);
    auto lastChar = dirVal.isEmpty() ? 0 : dirVal.c_str()[dirVal.len() - 1];
    if (lastChar != '\\' && lastChar != '/')
    {
        result = dirVal + EOC_STR_CONST("\\") + e::system::string((const char *)idStr) + EOC_STR_CONST(".tmp");
    }
    else
    {
        result = dirVal + e::system::string((const char *)idStr) + EOC_STR_CONST(".tmp");
    }
    RpcStringFreeA(&idStr);
    return result;
}

e::system::bin e::lib::krnln::FileUtils::ReadAllBytes(const e::system::string &path)
{
    e::system::bin result;
    auto pathW = e::system::ToNativeWideString(path);
    auto handle = CreateFileW(pathW.get(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (handle == 0 || handle == INVALID_HANDLE_VALUE)
        return nullptr;
    LARGE_INTEGER fileSizeStruct;
    unsigned long long fileSize;
    size_t binLen;
    size_t numOfRead = 0;
    DWORD numOfReadThisTime;
    uint8_t *buffer;

    if (!GetFileSizeEx(handle, &fileSizeStruct))
        goto cleanup;
    fileSize = static_cast<unsigned long long>(fileSizeStruct.QuadPart);
    if (fileSize > std::numeric_limits<size_t>::max())
        goto cleanup;
    binLen = static_cast<size_t>(fileSize);
    result.Redim(false, binLen);
    buffer = result.GetElemPtr();
    while (numOfRead < binLen)
    {
        DWORD bufferSize = static_cast<DWORD>(std::min<size_t>(binLen - numOfRead, static_cast<size_t>(std::numeric_limits<DWORD>::max())));
        if (!ReadFile(handle, buffer, bufferSize, &numOfReadThisTime, NULL))
        {
            result = nullptr;
            goto cleanup;
        }
        numOfRead += static_cast<size_t>(numOfReadThisTime);
        buffer += numOfReadThisTime;
    }

cleanup:
    CloseHandle(handle);
    return result;
}

bool e::lib::krnln::FileUtils::WriteAllBytes(const e::system::string &path, const e::system::bin &x)
{
    bool success = false;
    auto pathW = e::system::ToNativeWideString(path);
    auto handle = CreateFileW(pathW.get(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (handle == 0 || handle == INVALID_HANDLE_VALUE)
        return false;
    
    auto buffer = x.GetElemPtr();
    auto length = x.GetSize();
    while (length)
    {
        DWORD numOfWritten;
        DWORD bufferSize = static_cast<DWORD>(std::min<size_t>(length, std::numeric_limits<DWORD>::max()));
        if (!WriteFile((HANDLE)handle, buffer, bufferSize, &numOfWritten, NULL))
        {
            goto cleanup;
        }
        length -= numOfWritten;
        buffer = &static_cast<uint8_t *>(buffer)[numOfWritten];
    }

    success = true;
cleanup:
    CloseHandle(handle);
    return success;
}
