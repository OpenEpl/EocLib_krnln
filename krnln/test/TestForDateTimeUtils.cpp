#include <catch2/catch.hpp>
#include <e/lib/krnln/DateTimeUtils.h>
using namespace e::lib::krnln;
inline const e::system::datetime D_18990101_111213(-363.4668171296297);
inline const e::system::datetime D_20191231_050607(43830.21258101852);
inline const e::system::datetime D_20200101_050607(43831.21258101852);
inline const e::system::datetime D_20200102_050607(43832.21258101852);
TEST_CASE("DateTimeUtils::BuildDateTime", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::BuildDateTime(2019) == e::system::datetime(43466.0));
    CHECK(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7) == D_20191231_050607);
}

TEST_CASE("DateTimeUtils::DateTimeToString", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7)) == "2019年12月31日5时6分7秒");
    CHECK(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31)) == "2019年12月31日");
    CHECK(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7), DateTimeUtils::ConvertDate) == "2019年12月31日");
    CHECK(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7), DateTimeUtils::ConvertTime) == "5时6分7秒");
}

TEST_CASE("DateTimeUtils::GetTimePart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetTimePart(DateTimeUtils::BuildDateTime(1888, 12, 31, 5, 6, 7)) == DateTimeUtils::BuildDateTime(2000, 1, 1, 5, 6, 7));
    CHECK(DateTimeUtils::GetTimePart(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7)) == DateTimeUtils::BuildDateTime(2000, 1, 1, 5, 6, 7));
}

TEST_CASE("DateTimeUtils::GetDatePart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetDatePart(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7)) == DateTimeUtils::BuildDateTime(2019, 12, 31));
}

TEST_CASE("DateTimeUtils::GetHourPart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetHourPart(D_18990101_111213) == 11);
    CHECK(DateTimeUtils::GetHourPart(D_20191231_050607) == 5);
}

TEST_CASE("DateTimeUtils::GetMinutePart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetMinutePart(D_18990101_111213) == 12);
    CHECK(DateTimeUtils::GetMinutePart(D_20191231_050607) == 6);
}

TEST_CASE("DateTimeUtils::GetSecondPart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetSecondPart(D_18990101_111213) == 13);
    CHECK(DateTimeUtils::GetSecondPart(D_20191231_050607) == 7);
}

TEST_CASE("DateTimeUtils::GetYearPart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetYearPart(D_18990101_111213) == 1899);
    CHECK(DateTimeUtils::GetYearPart(D_20191231_050607) == 2019);
    CHECK(DateTimeUtils::GetYearPart(D_20200101_050607) == 2020);
    CHECK(DateTimeUtils::GetYearPart(D_20200102_050607) == 2020);
}

TEST_CASE("DateTimeUtils::GetMonthPart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetMonthPart(D_18990101_111213) == 1);
    CHECK(DateTimeUtils::GetMonthPart(D_20191231_050607) == 12);
    CHECK(DateTimeUtils::GetMonthPart(D_20200101_050607) == 1);
    CHECK(DateTimeUtils::GetMonthPart(D_20200102_050607) == 1);
}

TEST_CASE("DateTimeUtils::GetDayPart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetDayPart(D_18990101_111213) == 1);
    CHECK(DateTimeUtils::GetDayPart(D_20191231_050607) == 31);
    CHECK(DateTimeUtils::GetDayPart(D_20200101_050607) == 1);
    CHECK(DateTimeUtils::GetDayPart(D_20200102_050607) == 2);
}

TEST_CASE("DateTimeUtils::DayOfWeek", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::DayOfWeek(D_18990101_111213) == 1);
    CHECK(DateTimeUtils::DayOfWeek(D_20191231_050607) == 3);
    CHECK(DateTimeUtils::DayOfWeek(D_20200101_050607) == 4);
    CHECK(DateTimeUtils::DayOfWeek(D_20200102_050607) == 5);
}

TEST_CASE("DateTimeUtils::DaysInMonth", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::DaysInMonth(2020, 1) == 31);
    CHECK(DateTimeUtils::DaysInMonth(2020, 2) == 29);
    CHECK(DateTimeUtils::DaysInMonth(2020, 3) == 31);

    CHECK(DateTimeUtils::DaysInMonth(2019, 2) == 28);
    CHECK(DateTimeUtils::DaysInMonth(2004, 2) == 29);
    CHECK(DateTimeUtils::DaysInMonth(2000, 2) == 29);
    CHECK(DateTimeUtils::DaysInMonth(1900, 2) == 28);
}

TEST_CASE("DateTimeUtils::GetDistance", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Year) == 1);
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Quarter) == 1);
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Month) == 1);
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Week) == 0);
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Day) == 1);
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Hour) == 24);
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Minute) == 1440);
    CHECK(DateTimeUtils::GetDistance(D_20200101_050607, D_20191231_050607, DateTimeUtils::Second) == 86400);
    CHECK(DateTimeUtils::GetDistance(e::system::datetime(2020, 8, 9), e::system::datetime(2020, 8, 7), DateTimeUtils::Week) == 1);
    CHECK(DateTimeUtils::GetDistance(e::system::datetime(2020, 8, 9, 12), e::system::datetime(2020, 8, 9, 10, 45), DateTimeUtils::Hour) == 1);
    CHECK(DateTimeUtils::GetDistance(e::system::datetime(2020, 8, 9, 12), e::system::datetime(2020, 8, 9, 11, 44, 45), DateTimeUtils::Minute) == 15);
    CHECK(DateTimeUtils::GetDistance(e::system::datetime(2020, 8, 9, 12), e::system::datetime(2020, 8, 9, 11, 59, 45), DateTimeUtils::Second) == 15);
}

TEST_CASE("DateTimeUtils::GetSpecificPart", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::Year) == 2019);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::Quarter) == 4);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::Month) == 12);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::CalcWeekOfYear) == 53);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::Day) == 31);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::Hour) == 5);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::Minute) == 6);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::Second) == 7);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::CalcDayOfWeek) == 3);
    CHECK(DateTimeUtils::GetSpecificPart(D_20191231_050607, DateTimeUtils::CalcDayOfYear) == 365);
}