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
				intptr_t Len(const e::system::string &x);
				e::system::string Left(const e::system::string &x, intptr_t length);
				e::system::string Right(const e::system::string &x, intptr_t length);
				e::system::string SubStr(const e::system::string &x, intptr_t start, intptr_t length);
				intptr_t IndexOf(const e::system::string &str, const e::system::string &subStr, std::optional<intptr_t> startIndex = std::nullopt, std::optional<bool> caseInsensitive = std::nullopt);
				intptr_t LastIndexOf(const e::system::string &str, const e::system::string &subStr, std::optional<intptr_t> startIndex = std::nullopt, std::optional<bool> caseInsensitive = std::nullopt);
				e::system::string ToLower(const e::system::string &x);
				e::system::string ToUpper(const e::system::string &x);
			}
		}
	}
}