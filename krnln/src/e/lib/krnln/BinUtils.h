#pragma once
#include <e/system/basic_type.h>
namespace e
{
	namespace lib
	{
		namespace krnln
		{
			namespace BinUtils
			{
				intptr_t Len(const e::system::bin &x);
				e::system::bin Left(const e::system::bin &x, intptr_t length);
				e::system::bin Right(const e::system::bin &x, intptr_t length);
				e::system::bin SubBin(const e::system::bin &x, intptr_t start, intptr_t length);
				e::system::bin Space(intptr_t length);
				intptr_t IndexOf(const e::system::bin &haystack, const e::system::bin &needle, std::optional<intptr_t> startIndex = std::nullopt);
				intptr_t LastIndexOf(const e::system::bin &haystack, const e::system::bin &needle, std::optional<intptr_t> startIndex = std::nullopt);
            }
        }
    }
}