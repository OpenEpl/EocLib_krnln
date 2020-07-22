#pragma once
#include <e/system/func.h>
#include <algorithm>
namespace e
{
    namespace lib
    {
        namespace krnln
        {
            namespace MemoryUtils
            {
                inline int32_t ReadInt32(intptr_t ptr)
                {
                    return *(int32_t *)ptr;
                }
                inline float ReadFloat(intptr_t ptr)
                {
                    return *(float *)ptr;
                }
                inline double ReadDouble(intptr_t ptr)
                {
                    return *(double *)ptr;
                }
                inline e::system::string ReadText(intptr_t ptr)
                {
                    return e::system::string((const char *)ptr);
                }
                inline e::system::bin ReadToBin(intptr_t data, intptr_t size)
                {
                    if (size <= 0)
                        return nullptr;
                    return e::system::make_bin((void *)data, (size_t)size);
                }
                inline void CopyMemoryWithLimit(const void *buffer, intptr_t length, intptr_t dest)
                {
                    memmove((void *)dest, buffer, (size_t)length);
                }
                inline void CopyMemoryWithLimit(const void *buffer, intptr_t length, intptr_t dest, std::optional<intptr_t> limit)
                {
                    if (limit.value_or(-1) == -1)
                    {
                        CopyMemoryWithLimit(buffer, length, dest);
                    }
                    else
                    {
                        CopyMemoryWithLimit(buffer, std::min(length, limit.value()), dest);
                    }
                }
                template <typename TSrc, typename... TOthers,
                    std::enable_if_t<std::is_arithmetic_v<TSrc> || std::is_same_v<TSrc, e::system::methodptr> || std::is_same_v<TSrc, e::system::datetime>, int> = 0>
                void WriteMemory(TSrc data, TOthers &&... others)
                {
                    CopyMemoryWithLimit(&data, sizeof(TSrc), std::forward<TOthers>(others)...);
                }
                template <typename... TOthers>
                void WriteMemory(const e::system::string &data, TOthers &&... others)
                {
                    auto length = data.len();
                    if (length == 0)
                    {
                        CopyMemoryWithLimit("", 1, std::forward<TOthers>(others)...);
                    }
                    else
                    {
                        CopyMemoryWithLimit(data.c_str(), length + 1, std::forward<TOthers>(others)...);
                    }
                }
                template <typename... TOthers>
                void WriteMemory(const e::system::bin &data, TOthers &&... others)
                {
                    CopyMemoryWithLimit(data.GetElemPtr(), data.GetSize(), std::forward<TOthers>(others)...);
                }
                template <typename... TOthers>
                void WriteMemory(const e::system::array<uint8_t> &data, TOthers &&... others)
                {
                    CopyMemoryWithLimit(data.GetElemPtr(), data.GetSize(), std::forward<TOthers>(others)...);
                }
                template <typename... TOthers>
                void WriteMemory(const e::system::any &data, TOthers &&... others)
                {
                    if (data.type() == typeid(uint8_t))
                    {
                        return WriteMemory(data.cast<uint8_t>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(int16_t))
                    {
                        return WriteMemory(data.cast<int16_t>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(int32_t))
                    {
                        return WriteMemory(data.cast<int32_t>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(int64_t))
                    {
                        return WriteMemory(data.cast<int64_t>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(double))
                    {
                        return WriteMemory(data.cast<double>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(float))
                    {
                        return WriteMemory(data.cast<float>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(bool))
                    {
                        return WriteMemory(data.cast<bool>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(e::system::string))
                    {
                        return WriteMemory(data.cast<e::system::string>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(e::system::bin))
                    {
                        return WriteMemory(data.cast<e::system::bin>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(e::system::methodptr))
                    {
                        return WriteMemory(data.cast<e::system::methodptr>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(e::system::datetime))
                    {
                        return WriteMemory(data.cast<e::system::datetime>(), std::forward<TOthers>(others)...);
                    }
                    if (data.type() == typeid(e::system::array<uint8_t>))
                    {
                        return WriteMemory(data.cast<e::system::array<uint8_t>>(), std::forward<TOthers>(others)...);
                    }
                    throw std::domain_error("Don't know how to write this object to memory block");
                }
            }
        }
    }
}