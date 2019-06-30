#pragma once
#include <e/system/basic_type.h>
namespace e
{
	namespace lib
	{
		namespace krnln
		{
			namespace TextUtils
			{
				e::system::string Char(uint8_t x);
				int32_t GetCodePoint(const e::system::string &x, std::optional<intptr_t> pos = std::nullopt);
				intptr_t Len(const e::system::string& x);
			}
		}
	}
}