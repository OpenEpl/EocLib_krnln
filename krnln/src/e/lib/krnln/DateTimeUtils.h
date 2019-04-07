#pragma once
#include <e/system/basic_type.h>
namespace e
{
	namespace lib
	{
		namespace krnln
		{
			namespace DateTimeUtils
			{
				const int32_t ConvertDateTime(1);
				const int32_t ConvertDate(2);
				const int32_t ConvertTime(3);
				e::system::string DateTimeToString(e::system::datetime value, std::optional<int> mode = ConvertDateTime);
				e::system::datetime Now();
			}
		}
	}
}