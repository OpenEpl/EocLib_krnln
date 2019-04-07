#include "TextUtils.h"

e::system::string e::lib::krnln::TextUtils::Char(int8_t x)
{
	auto r = e::system::string(1);
	r.data[0] = static_cast<char>(x);
	r.data[1] = '\0';
	return r;
}

intptr_t e::lib::krnln::TextUtils::Len(const e::system::string & x)
{
	return intptr_t(x.len());
}
