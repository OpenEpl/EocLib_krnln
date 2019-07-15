#pragma once
#include <e/system/func.h>
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
            }
        }
    }
}