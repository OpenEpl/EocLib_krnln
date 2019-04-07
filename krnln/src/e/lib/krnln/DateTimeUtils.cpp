#include "DateTimeUtils.h"
#include <Windows.h>
#include <sstream>
e::system::string e::lib::krnln::DateTimeUtils::DateTimeToString(e::system::datetime value, std::optional<int> mode)
{
	bool convertDate, convertTime;
	switch (mode.value_or(ConvertDateTime))
	{
	case ConvertDate:
		convertDate = true;
		convertTime = false;
		break;
	case ConvertTime:
		convertDate = false;
		convertTime = true;
		break;
	default:
		convertDate = convertTime = true;
		break;
	}

	std::stringstream s;
	SYSTEMTIME info;
	VariantTimeToSystemTime(value.value, &info);
	if (convertDate)
	{
		s << info.wYear;
		s << "年";
		s << info.wMonth;
		s << "月";
		s << info.wDay;
		s << "日";
	}
	if (convertTime && (info.wHour | info.wMinute | info.wDay))
	{
		s << info.wHour;
		s << "时";
		s << info.wMinute;
		s << "分";
		s << info.wDay;
		s << "秒";
	}
	return e::system::string(s.str().c_str());
}

e::system::datetime e::lib::krnln::DateTimeUtils::Now()
{
	SYSTEMTIME info;
	e::system::datetime result;
	GetLocalTime(&info);
	SystemTimeToVariantTime(&info, &result.value);
	return result;
}
