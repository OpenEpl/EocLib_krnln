#pragma once
#include <e/system/basic_type.h>
namespace e
{
	namespace lib
	{
		namespace krnln
		{
			namespace RandomUtils
			{
                void SetSeed(std::optional<int32_t> seed = std::nullopt);
				int32_t NextInt32(std::optional<int32_t> min = std::nullopt, std::optional<int32_t> max = std::nullopt);
			}
		}
	}
}