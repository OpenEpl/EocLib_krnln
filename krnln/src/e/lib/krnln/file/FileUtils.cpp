#include "FileUtils.h"
#include <e/system/native_string.h>
#include <windows.h>
#include <rpc.h>

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
        object = new File(std::move(File::Open(filePath,
            static_cast<FileAccessMode>(accessMode.value_or(1)),
            static_cast<FileShareMode>(shareMode.value_or(1)))));
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