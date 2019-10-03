#pragma once
#include <e/system/basic_type.h>
#include <e/system/func.h>
#include "BaseFile.h"
#include "MemoryFile.h"
#include "File.h"
#include "../Converter.h"
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace FileUtils
            {
                intptr_t NewMemoryFile();
                intptr_t OpenFile(const e::system::string &filePath, std::optional<int32_t> accessMode = std::nullopt, std::optional<int32_t> shareMode = std::nullopt);
                void CloseFile(intptr_t id);
                e::system::bin ReadData(intptr_t id, int32_t length);
                bool WriteData(intptr_t id, const e::system::bin &data);
                template <typename... TArgs>
                bool WriteData(intptr_t id, const e::system::bin &first, const e::system::bin &second, const TArgs &... args)
                {
                    return (::e::lib::krnln::FileUtils::WriteData(id, first)) && (::e::lib::krnln::FileUtils::WriteData(id, second, args...));
                }
                bool IsEOF(intptr_t id, std::optional<bool> textMode = std::nullopt);
                int32_t GetLength(intptr_t id);
                int32_t GetPosition(intptr_t id);
                e::system::string ReadText(intptr_t id, std::optional<int32_t> limit = std::nullopt);
                e::system::string ReadLine(intptr_t id);
                bool DeleteDiskFile(const e::system::string &path);
                e::system::string GetTempFile(std::optional<std::reference_wrapper<const e::system::string>> dir = std::nullopt);
                inline e::system::string GetTempFile(const e::system::string &dir)
                {
                    GetTempFile(std::optional(std::cref(dir)));
                }
                bool Seek(intptr_t id, std::optional<int32_t> whence, int32_t offset);
                bool SeekToBegin(intptr_t id);
                bool SeekToEnd(intptr_t id);

                template <typename... T>
                bool WriteText(intptr_t id, T &... x)
                {
                    try
                    {
                        auto object = reinterpret_cast<BaseFile *>(id);
                        int dummy[] = {0,
                            (object->WriteText(krnln::ToString(x)), 0)...};
                        return true;
                    }
                    catch (...)
                    {
                        return false;
                    }
                }

                template <typename... T>
                bool WriteLine(intptr_t id, T &... x)
                {
                    try
                    {
                        auto object = reinterpret_cast<BaseFile *>(id);
                        int dummy[] = {0,
                            (object->WriteLine(krnln::ToString(x)), 0)...};
                        return true;
                    }
                    catch (...)
                    {
                        return false;
                    }
                }

                template <typename... T>
                bool ReadObject(intptr_t id, T &... x)
                {
                    try
                    {
                        auto object = reinterpret_cast<BaseFile *>(id);
                        int dummy[] = {0,
                            (object->ReadObject(x), 0)...};
                        return true;
                    }
                    catch (...)
                    {
                        return false;
                    }
                }

                template <typename... T>
                bool WriteObject(intptr_t id, const T &... x)
                {
                    try
                    {
                        auto object = reinterpret_cast<BaseFile *>(id);
                        int dummy[] = {0,
                            (object->WriteObject(x), 0)...};
                        return true;
                    }
                    catch (...)
                    {
                        return false;
                    }
                }

                e::system::bin ReadAllBytes(const e::system::string &path);
                bool WriteAllBytes(const e::system::string &path, const e::system::bin &x);

                template <typename... TArgs>
                bool WriteAllBytes(const e::system::string &path, const e::system::bin &first, const TArgs &... args)
                {
                    return e::lib::krnln::FileUtils::WriteAllBytes(path, (first + ... + static_cast<e::system::bin>(args)));
                }
            }
        }
    }
}