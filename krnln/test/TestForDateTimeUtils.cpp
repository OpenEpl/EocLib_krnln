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

TEST_CASE("DateTimeUtils::DayOfWeek", "[DateTimeUtils]")
{
    CHECK(DateTimeUtils::DayOfWeek(D_18990101_111213) == 1);
    CHECK(DateTimeUtils::DayOfWeek(D_20191231_050607) == 3);
    CHECK(DateTimeUtils::DayOfWeek(D_20200101_050607) == 4);
    CHECK(DateTimeUtils::DayOfWeek(D_20200102_050607) == 5);
}