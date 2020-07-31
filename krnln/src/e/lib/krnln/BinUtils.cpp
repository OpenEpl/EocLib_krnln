#include "BinUtils.h"
#include "FindAllHelper.h"
#include "GlobalConstant.h"
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

e::system::bin e::lib::krnln::BinUtils::Repeat(intptr_t times, const e::system::bin &x)
{
    if (times <= 0)
        return nullptr;
    auto length = x.GetSize();
    if (length == 0)
        return nullptr;
    auto startPtr = x.GetElemPtr();
    auto resultLength = length * (size_t)times;
    e::system::bin result(resultLength);
    auto ptrOnResult = result.GetElemPtr();
    for (intptr_t i = 0; i < times; i++)
    {
        std::memcpy(ptrOnResult, startPtr, length);
        ptrOnResult += length;
    }
    return result;
}

inline intptr_t myMemmem_EStyle(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen, size_t s)
{
    //Sunday算法

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
    //Sunday算法

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
    return myMemmem_EStyle(haystack.GetElemPtr(), haystacklen, needle.GetElemPtr(), needlelen, size_t(start_v));
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
    return myMemrmem_EStyle(haystack.GetElemPtr(), haystacklen, needle.GetElemPtr(), needlelen, start_v);
}

e::system::bin e::lib::krnln::BinUtils::Replace(const e::system::bin &x, intptr_t start, intptr_t length, std::optional<std::reference_wrapper<const e::system::bin>> target)
{
    auto rawLength = intptr_t(x.GetSize());
    auto startPtr = x.GetElemPtr();
    if (start <= 1)
        start = 1;
    e::system::bin defaultTargetBin;
    const e::system::bin &targetBin = target.has_value() ? target.value().get() : defaultTargetBin;
    if (start > rawLength)
        return x + targetBin;
    if (start + length - 1 > rawLength)
        length = rawLength - start + 1;
    else if (length < 0)
        length = 0;
    auto targetLength = intptr_t(targetBin.GetSize());
    auto targetDataPtr = targetBin.GetElemPtr();
    auto newLength = rawLength + targetLength - length;
    e::system::bin result(newLength);
    auto resultPtr = result.GetElemPtr();
    memcpy(&resultPtr[0], startPtr, start - 1);
    memcpy(&resultPtr[start - 1], targetDataPtr, targetLength);
    memcpy(&resultPtr[start - 1 + targetLength], &startPtr[start - 1 + length], rawLength - start - length + 1);
    return result;
}

static std::vector<uint8_t *> findAllSubBin(uint8_t *startPtr, uint8_t *endPtr, uint8_t *target, size_t targetLength, size_t limit)
{
    return e::lib::krnln::findAllSubData(startPtr, endPtr, target, targetLength, limit, [endPtr, targetLength](uint8_t *a, uint8_t *b) -> uint8_t * {
        auto result = myMemmem_EStyle(a, endPtr - a, b, targetLength, 1);
        if (result == -1)
            return nullptr;
        else
            return &a[result - 1];
    });
}

e::system::array<e::system::bin> e::lib::krnln::BinUtils::Split(const e::system::bin &x,
    std::optional<std::reference_wrapper<const e::system::bin>> separator,
    std::optional<intptr_t> limit)
{
    size_t limit_value;
    if (limit.has_value())
    {
        if (limit.value() <= 0)
            return nullptr;
        else
            limit_value = size_t(limit.value());
    }
    else
    {
        limit_value = (std::numeric_limits<size_t>::max)();
    }

    auto rawLength = intptr_t(x.GetSize());
    if (rawLength == 0)
        return nullptr;

    e::system::bin defaultSeparatorBin{0};
    const e::system::bin &separatorBin = separator.has_value() ? separator.value().get() : defaultSeparatorBin;
    auto separatorLength = intptr_t(separatorBin.GetSize());
    if (separatorLength == 0)
        return {x};

    auto startPtr = x.GetElemPtr();
    auto endPtr = startPtr + rawLength;
    auto separatorPtr = separatorBin.GetElemPtr();
    auto positions = findAllSubBin(startPtr, endPtr, separatorPtr, separatorLength, limit_value);

    if (positions.size() < limit_value)
        if (positions.size() == 0 || positions.back() != endPtr - separatorLength)
            positions.push_back(endPtr);

    e::system::array<e::system::bin> result(positions.size());
    auto firstElemPtr = &result.At_CStyle(0);
    startPtr = x.GetElemPtr();
    for (std::vector<uint8_t *>::iterator it = positions.begin(); it != positions.end(); it++)
    {
        auto curLength = *it - startPtr;
        *firstElemPtr = e::system::bin(curLength);
        memcpy((*firstElemPtr).GetElemPtr(), startPtr, curLength);
        startPtr = *it + separatorLength;

        firstElemPtr++;
    }

    return result;
}

e::system::bin e::lib::krnln::BinUtils::ReplaceSubBin(const e::system::bin &x,
    const e::system::bin &oldBin,
    std::optional<std::reference_wrapper<const e::system::bin>> newBin,
    std::optional<intptr_t> startIndex,
    std::optional<intptr_t> limit)
{
    size_t limit_value = (size_t)limit.value_or(-1);

    auto rawLength = intptr_t(x.GetSize());

    auto start_v = startIndex.value_or(1);
    if (start_v <= 0)
        start_v = 1;
    if (start_v > rawLength)
        return x;

    auto startPtr = x.GetElemPtr();
    auto endPtr = startPtr + rawLength;
    auto oldBinPtr = oldBin.GetElemPtr();
    auto oldBinLength = oldBin.GetSize();
    if (oldBinLength == 0)
        return x;

    e::system::bin defaultNewBin;
    const e::system::bin &newText_Bin = newBin.has_value() ? newBin.value().get() : defaultNewBin;
    auto newBinPtr = newText_Bin.GetElemPtr();
    auto newBinLength = intptr_t(newText_Bin.GetSize());

    std::vector<uint8_t *> positions;
    positions = findAllSubBin(startPtr + (start_v - 1), endPtr, oldBinPtr, oldBinLength, limit_value);
    auto resultLength = rawLength + (newBinLength - oldBinLength) * positions.size();
    e::system::bin result(resultLength);

    auto ptrOnResult = result.GetElemPtr();
    for (std::vector<uint8_t *>::iterator it = positions.begin(); it != positions.end(); it++)
    {
        auto curLength = *it - startPtr;
        std::memcpy(ptrOnResult, startPtr, curLength);
        ptrOnResult += curLength;
        std::memcpy(ptrOnResult, newBinPtr, newBinLength);
        ptrOnResult += newBinLength;
        startPtr = *it + oldBinLength;
    }
    if (startPtr < endPtr)
    {
        auto curLength = endPtr - startPtr;
        std::memcpy(ptrOnResult, startPtr, curLength);
        ptrOnResult += curLength;
    }
    return result;
}

e::system::any e::lib::krnln::BinUtils::GetDataFromBin(const e::system::bin &from, int32_t type, std::optional<std::reference_wrapper<int32_t>> pos)
{
    int realPos = pos.has_value() ? pos.value().get() : 1;
    e::system::any result;
    auto size = from.GetSize();
    switch (type)
    {
    case e::lib::krnln::constant::UInt8Type:
        if (realPos > 0 && realPos + sizeof(uint8_t) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<uint8_t *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(uint8_t(0));
        }
        realPos += sizeof(uint8_t);
        break;
    case e::lib::krnln::constant::Int16Type:
        if (realPos > 0 && realPos + sizeof(int16_t) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<int16_t *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(int16_t(0));
        }
        realPos += sizeof(int16_t);
        break;
    case e::lib::krnln::constant::Int32Type:
        if (realPos > 0 && realPos + sizeof(int32_t) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<int32_t *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(int32_t(0));
        }
        realPos += sizeof(int32_t);
        break;
    case e::lib::krnln::constant::Int64Type:
        if (realPos > 0 && realPos + sizeof(int64_t) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<int64_t *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(int64_t(0));
        }
        realPos += sizeof(int64_t);
        break;
    case e::lib::krnln::constant::FloatType:
        if (realPos > 0 && realPos + sizeof(float) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<float *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(float(0));
        }
        realPos += sizeof(float);
        break;
    case e::lib::krnln::constant::DoubleType:
        if (realPos > 0 && realPos + sizeof(double) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<double *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(double(0));
        }
        realPos += sizeof(double);
        break;
    case e::lib::krnln::constant::BoolType:
        if (realPos > 0 && realPos + sizeof(int32_t) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<int32_t *>(&from.At(realPos)) ? true : false);
        }
        else
        {
            result = e::system::any(false);
        }
        realPos += sizeof(int32_t);
        break;
    case e::lib::krnln::constant::DateTimeType:
        if (realPos > 0 && realPos + sizeof(e::system::datetime) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<e::system::datetime *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(e::system::datetime(0));
        }
        realPos += sizeof(e::system::datetime);
        break;
    case e::lib::krnln::constant::MethodPtrType:
        if (realPos > 0 && realPos + sizeof(e::system::methodptr) - 1 <= size)
        {
            result = e::system::any(*reinterpret_cast<e::system::methodptr *>(&from.At(realPos)));
        }
        else
        {
            result = e::system::any(e::system::methodptr());
        }
        realPos += sizeof(e::system::methodptr);
        break;
    case e::lib::krnln::constant::StringType:
        if (realPos > 0 && realPos <= int32_t(size))
        {
            const char *startPtr = reinterpret_cast<const char *>(&from.At(realPos));
            size_t strSize = size - realPos + 1;
            const char *endPtr = reinterpret_cast<const char *>(std::memchr(startPtr, 0, strSize));
            if (endPtr == nullptr)
            {
                realPos = -1;
                e::system::string tempStrResult(strSize);
                std::memcpy(tempStrResult.c_str(), startPtr, strSize);
                tempStrResult.c_str()[strSize] = '\0';
                result = e::system::any(tempStrResult);
            }
            else
            {
                strSize = reinterpret_cast<intptr_t>(endPtr) - reinterpret_cast<intptr_t>(startPtr);
                realPos += (int)strSize;
                e::system::string tempStrResult(strSize);
                std::memcpy(tempStrResult.c_str(), startPtr, strSize);
                result = e::system::any(tempStrResult);
            }
        }
        else
        {
            result = e::system::any(e::system::string());
        }
        break;
    default:
        break;
    }
    if (realPos > int32_t(size))
    {
        realPos = -1;
    }
    if (pos.has_value())
    {
        pos.value() = realPos;
    }
    return result;
}