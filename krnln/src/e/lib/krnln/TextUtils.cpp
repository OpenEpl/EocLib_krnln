#include "TextUtils.h"
#include <mbstring.h>
#include <shlwapi.h>

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
	auto startPtr = str.c_str();		 //included
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
	auto result = x;
	_mbslwr((unsigned char *)result.data);
	return result;
}

e::system::string e::lib::krnln::TextUtils::ToUpper(const e::system::string &x)
{
	auto result = x;
	_mbsupr((unsigned char *)result.data);
	return result;
}
