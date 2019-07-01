#include "TextUtils.h"

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
