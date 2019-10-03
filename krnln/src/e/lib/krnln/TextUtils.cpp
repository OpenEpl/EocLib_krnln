#define _CRT_SECURE_NO_WARNINGS

#include "TextUtils.h"
#include <mbstring.h>
#include <shlwapi.h>
#include <limits>
#include "FindAllHelper.h"

e::system::string e::lib::krnln::TextUtils::Char(uint8_t x)
{
    auto r = e::system::string(1);
    r.data[0] = static_cast<char>(x);
    r.data[1] = '\0';
    return r;
}

int32_t e::lib::krnln::TextUtils::GetCodePoint(const e::system::string &x, std::optional<intptr_t> pos)
{
    auto pos_value = pos.value_or(1);
    if (pos_value <= 0 || pos_value > (intptr_t)x.len())
        return 0;
    return int32_t(static_cast<signed char>(x.c_str()[pos_value - 1]));
}

intptr_t e::lib::krnln::TextUtils::Len(const e::system::string &x)
{
    return intptr_t(x.len());
}

e::system::string e::lib::krnln::TextUtils::Left(const e::system::string &x, intptr_t length)
{
    if (length <= 0)
        return nullptr;
    if (length >= static_cast<intptr_t>(x.len()))
        return x;
    auto result = e::system::string(length);
    std::memcpy(result.data, x.data, length);
    result.data[length] = '\0';
    return result;
}

e::system::string e::lib::krnln::TextUtils::Right(const e::system::string &x, intptr_t length)
{
    if (length <= 0)
        return nullptr;
    auto rawLength = intptr_t(x.len());
    if (length >= rawLength)
        return x;
    auto result = e::system::string(length);
    std::memcpy(result.data, &x.data[rawLength - length], length);
    result.data[length] = '\0';
    return result;
}

e::system::string e::lib::krnln::TextUtils::SubStr(const e::system::string &x, intptr_t start, intptr_t length)
{
    if (start <= 0 || length <= 0)
        return nullptr;
    auto rawLength = intptr_t(x.len());
    if (start > rawLength)
        return nullptr;
    if (start + length - 1 > rawLength)
        length = rawLength - start + 1;
    auto result = e::system::string(length);
    std::memcpy(result.data, &x.data[start - 1], length);
    result.data[length] = '\0';
    return result;
}

intptr_t e::lib::krnln::TextUtils::IndexOf(const e::system::string &str, const e::system::string &subStr, std::optional<intptr_t> startIndex, std::optional<bool> caseInsensitive)
{
    if (subStr.isEmpty())
        return -1;
    auto start_v = startIndex.value_or(1);
    if (start_v <= 0)
        start_v = 1;
    if ((size_t)start_v > str.len())
        return -1;
    auto pStart = &str.c_str()[start_v - 1];
    char *pTarget;
    if (!caseInsensitive.value_or(false))
        pTarget = (char *)_mbsstr((unsigned char *)pStart, (unsigned char *)subStr.c_str());
    else
        pTarget = StrStrIA(pStart, subStr.c_str()); //MBCS-friendly
    if (pTarget == nullptr)
        return -1;
    return (pTarget - pStart) + start_v;
}

intptr_t e::lib::krnln::TextUtils::LastIndexOf(const e::system::string &str, const e::system::string &subStr, std::optional<intptr_t> startIndex, std::optional<bool> caseInsensitive)
{
    if (subStr.isEmpty())
        return -1;
    auto len = (intptr_t)str.len();
    auto start_v = startIndex.value_or(len);
    if (start_v <= 0)
        return -1;
    if (start_v > len)
        start_v = len;
    auto startPtr = str.c_str();         //included
    auto endPtr = str.c_str() + start_v; //not included
    char *curPtr;
    if (!caseInsensitive.value_or(false))
    {
        curPtr = (char *)_mbsstr((unsigned char *)startPtr, (unsigned char *)subStr.c_str());
        if (curPtr >= endPtr || curPtr == nullptr)
            return -1;
        while (true)
        {
            auto nextPtr = (char *)_mbsstr(_mbsinc((unsigned char *)curPtr), (unsigned char *)subStr.c_str());
            if (nextPtr >= endPtr || nextPtr == nullptr)
                break;
            else
                curPtr = nextPtr;
        }
    }
    else
    {
        curPtr = StrRStrIA(startPtr, endPtr, subStr.c_str());
        if (curPtr == nullptr)
            return -1;
    }
    return curPtr - startPtr + 1;
}
e::system::string e::lib::krnln::TextUtils::ToLower(const e::system::string &x)
{
    e::system::string result(x.c_str());
    _mbslwr((unsigned char *)result.data);
    return result;
}

e::system::string e::lib::krnln::TextUtils::ToUpper(const e::system::string &x)
{
    e::system::string result(x.c_str());
    _mbsupr((unsigned char *)result.data);
    return result;
}

e::system::string e::lib::krnln::TextUtils::Space(intptr_t length)
{
    if (length <= 0)
        return nullptr;
    e::system::string result(length);
    memset(result.data, ' ', length);
    result.data[length] = '\0';
    return result;
}

e::system::string e::lib::krnln::TextUtils::Repeat(intptr_t times, const e::system::string &x)
{
    if (times <= 0)
        return nullptr;
    auto length = x.len();
    if (length == 0)
        return nullptr;
    auto startPtr = x.c_str();
    auto resultLength = length * (size_t)times;
    e::system::string result(resultLength);
    auto ptrOnResult = result.c_str();
    for (intptr_t i = 0; i < times; i++)
    {
        std::memcpy(ptrOnResult, startPtr, length);
        ptrOnResult += length;
    }
    *ptrOnResult = '\0';
    return result;
}

e::system::string e::lib::krnln::TextUtils::Replace(const e::system::string &x, intptr_t start, intptr_t length, std::optional<std::reference_wrapper<const e::system::string>> target)
{
    auto rawLength = intptr_t(x.len());
    auto startPtr = x.c_str();
    if (start <= 1)
        start = 1;
    e::system::string defaultTargetStr;
    const e::system::string &targetStr = target.has_value() ? target.value().get() : defaultTargetStr;
    if (start > rawLength)
        return x + targetStr;
    if (start + length - 1 > rawLength)
        length = rawLength - start + 1;
    else if (length < 0)
        length = 0;
    auto targetLength = intptr_t(targetStr.len());
    auto targetDataPtr = targetStr.c_str();
    auto newLength = rawLength + targetLength - length;
    e::system::string result(newLength);
    auto resultPtr = result.c_str();
    memcpy(&resultPtr[0], startPtr, start - 1);
    memcpy(&resultPtr[start - 1], targetDataPtr, targetLength);
    memcpy(&resultPtr[start - 1 + targetLength], &startPtr[start - 1 + length], rawLength - start - length + 1);
    resultPtr[newLength] = '\0';
    return result;
}

static std::vector<char *> findAllSubStr(char *startPtr, char *endPtr, char *target, size_t targetLength, size_t limit)
{
    return e::lib::krnln::findAllSubData(startPtr, endPtr, target, targetLength, limit, [](char *a, char *b) {
        return (char *)_mbsstr((unsigned char *)a, (unsigned char *)b);
    });
}

static std::vector<char *> findAllSubStr_CaseInsensitive(char *startPtr, char *endPtr, char *target, size_t targetLength, size_t limit)
{
    return e::lib::krnln::findAllSubData(startPtr, endPtr, target, targetLength, limit, [](char *a, char *b) {
        return StrStrIA(a, b);
    });
}

e::system::array<e::system::string> e::lib::krnln::TextUtils::Split(const e::system::string &x,
    std::optional<std::reference_wrapper<const e::system::string>> separator,
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

    auto rawLength = intptr_t(x.len());
    if (rawLength == 0)
        return nullptr;

    auto defaultSeparatorStr = EOC_STR_CONST(",");
    const e::system::string &separatorStr = separator.has_value() ? separator.value().get() : defaultSeparatorStr;
    auto separatorLength = intptr_t(separatorStr.len());
    if (separatorLength == 0)
        return {x};

    auto startPtr = x.c_str();
    auto endPtr = startPtr + rawLength;
    auto separatorPtr = separatorStr.c_str();
    auto positions = findAllSubStr(startPtr, endPtr, separatorPtr, separatorLength, limit_value);

    if (positions.size() < limit_value)
        if (positions.size() == 0 || positions.back() != endPtr - separatorLength)
            positions.push_back(endPtr);

    e::system::array<e::system::string> result(positions.size());
    auto firstElemPtr = &result.At_CStyle(0);
    startPtr = x.c_str();
    for (std::vector<char *>::iterator it = positions.begin(); it != positions.end(); it++)
    {
        auto curLength = *it - startPtr;
        *firstElemPtr = e::system::string(curLength);
        if (curLength)
        {
            memcpy((*firstElemPtr).c_str(), startPtr, curLength);
            (*firstElemPtr).c_str()[curLength] = '\0';
        }
        startPtr = *it + separatorLength;

        firstElemPtr++;
    }

    return result;
}

e::system::string e::lib::krnln::TextUtils::ReplaceSubText(const e::system::string &x,
    const e::system::string &oldText,
    std::optional<std::reference_wrapper<const e::system::string>> newText,
    std::optional<intptr_t> startIndex,
    std::optional<intptr_t> limit,
    std::optional<bool> caseSensitive)
{
    size_t limit_value = (size_t)limit.value_or(-1);

    auto rawLength = intptr_t(x.len());

    auto start_v = startIndex.value_or(1);
    if (start_v <= 0)
        start_v = 1;
    if (start_v > rawLength)
        return x;

    auto startPtr = x.c_str();
    auto endPtr = startPtr + rawLength;
    auto oldTextPtr = oldText.c_str();
    auto oldTextLength = oldText.len();
    if (oldTextLength == 0)
        return x;

    e::system::string defaultNewText;
    const e::system::string &newText_Str = newText.has_value() ? newText.value().get() : defaultNewText;
    auto newTextLength = intptr_t(newText_Str.len());

    std::vector<char *> positions;
    if (caseSensitive.value_or(true))
        positions = findAllSubStr(startPtr + (start_v - 1), endPtr, oldTextPtr, oldTextLength, limit_value);
    else
        positions = findAllSubStr_CaseInsensitive(startPtr + (start_v - 1), endPtr, oldTextPtr, oldTextLength, limit_value);
    auto resultLength = rawLength + (newTextLength - oldTextLength) * positions.size();
    e::system::string result(resultLength);

    auto ptrOnResult = result.c_str();
    for (std::vector<char *>::iterator it = positions.begin(); it != positions.end(); it++)
    {
        auto curLength = *it - startPtr;
        std::memcpy(ptrOnResult, startPtr, curLength);
        ptrOnResult += curLength;
        std::memcpy(ptrOnResult, newText_Str.c_str(), newTextLength);
        ptrOnResult += newTextLength;
        startPtr = *it + oldTextLength;
    }
    if (startPtr < endPtr)
    {
        auto curLength = endPtr - startPtr;
        std::memcpy(ptrOnResult, startPtr, curLength);
        ptrOnResult += curLength;
    }
    *ptrOnResult = '\0';
    return result;
}
