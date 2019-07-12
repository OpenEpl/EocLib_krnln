#include "BinUtils.h"

intptr_t e::lib::krnln::BinUtils::Len(const e::system::bin &x)
{
    return intptr_t(x.GetSize());
}

e::system::bin e::lib::krnln::BinUtils::Left(const e::system::bin &x, intptr_t length)
{
    if (length <= 0)
        return nullptr;
    if (length >= static_cast<intptr_t>(x.GetSize()))
        return x;
    auto result = e::system::bin(length);
    std::memcpy(&result.At_CStyle(0), &x.At_CStyle(0), length);
    return result;
}

e::system::bin e::lib::krnln::BinUtils::Right(const e::system::bin &x, intptr_t length)
{
    if (length <= 0)
        return nullptr;
    auto rawLength = intptr_t(x.GetSize());
    if (length >= rawLength)
        return x;
    auto result = e::system::bin(length);
    std::memcpy(&result.At_CStyle(0), &x.At_CStyle(rawLength - length), length);
    return result;
}

e::system::bin e::lib::krnln::BinUtils::SubBin(const e::system::bin &x, intptr_t start, intptr_t length)
{
    if (start <= 0 || length <= 0)
        return nullptr;
    auto rawLength = intptr_t(x.GetSize());
    if (start > rawLength)
        return nullptr;
    if (start + length - 1 > rawLength)
        length = rawLength - start + 1;
    auto result = e::system::bin(length);
    std::memcpy(&result.At_CStyle(0), &x.At(start), length);
    return result;
}

e::system::bin e::lib::krnln::BinUtils::Space(intptr_t length)
{
    if (length <= 0)
        return nullptr;
    return e::system::bin(length);
}

inline intptr_t myMemmem_EStyle(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen, size_t s)
{
    //SundayÀ„∑®

    size_t next[256];
    const uint8_t *internalHaystack = static_cast<const uint8_t *>(haystack);
    const uint8_t *internalNeedle = static_cast<const uint8_t *>(needle);

    for (size_t i = 0; i < 256; i++)
    {
        next[i] = needlelen + 1;
    }
    for (size_t i = 0; i < needlelen; i++)
    {
        next[internalNeedle[i]] = needlelen - i;
    }

    size_t j;
    s--; //EStyle To CStyle
    while (s < haystacklen - needlelen)
    {
        j = 0;
        while (internalHaystack[s + j] == internalNeedle[j])
        {
            j++;
            if (j >= needlelen)
            {
                s++; //CStyle To EStyle
                return (intptr_t)s;
            }
        }
        s += next[internalHaystack[s + needlelen]];
    }
    if (s == haystacklen - needlelen)
    {
        j = 0;
        while (internalHaystack[s + j] == internalNeedle[j])
        {
            j++;
            if (j >= needlelen)
            {
                s++; //CStyle To EStyle
                return (intptr_t)s;
            }
        }
    }
    return -1;
}

inline intptr_t myMemrmem_EStyle(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen, intptr_t s)
{
    //SundayÀ„∑®

    intptr_t next[256];
    const uint8_t *internalHaystack = static_cast<const uint8_t *>(haystack);
    const uint8_t *internalNeedle = static_cast<const uint8_t *>(needle);

    for (intptr_t i = 0; i < 256; i++)
    {
        next[i] = needlelen + 1;
    }
    for (intptr_t i = (intptr_t)needlelen; i > 0; i--)
    {
        next[internalNeedle[i - 1]] = i;
    }

    intptr_t j;
    s -= needlelen;
    while (s > 0)
    {
        j = needlelen - 1;
        while (internalHaystack[s + j] == internalNeedle[j])
        {
            if (j <= 0)
            {
                s++; //CStyle To EStyle
                return s;
            }
            j--;
        }
        s -= next[internalHaystack[s - 1]];
    }
    if (s == 0)
    {
        j = needlelen - 1;
        while (internalHaystack[s + j] == internalNeedle[j])
        {
            if (j <= 0)
            {
                s++; //CStyle To EStyle
                return s;
            }
            j--;
        }
    }
    return -1;
}

intptr_t e::lib::krnln::BinUtils::IndexOf(const e::system::bin &haystack, const e::system::bin &needle, std::optional<intptr_t> startIndex)
{
    auto haystacklen = haystack.GetSize(), needlelen = needle.GetSize();
    if (needlelen == 0)
        return -1;
    auto start_v = startIndex.value_or(1);
    if (start_v <= 0)
        start_v = 1;
    if ((size_t)start_v > haystacklen)
        return -1;
    return myMemmem_EStyle(&haystack.At_CStyle(0), haystacklen, &needle.At_CStyle(0), needlelen, size_t(start_v));
}

intptr_t e::lib::krnln::BinUtils::LastIndexOf(const e::system::bin &haystack, const e::system::bin &needle, std::optional<intptr_t> startIndex)
{
    auto haystacklen = haystack.GetSize(), needlelen = needle.GetSize();
    if (needlelen == 0)
        return -1;
    auto start_v = startIndex.value_or((intptr_t)haystacklen);
    if (start_v <= 0)
        return -1;
    if ((size_t)start_v > haystacklen)
        start_v = haystacklen;
    return myMemrmem_EStyle(&haystack.At_CStyle(0), haystacklen, &needle.At_CStyle(0), needlelen, start_v);
}
