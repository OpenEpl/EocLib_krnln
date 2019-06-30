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
