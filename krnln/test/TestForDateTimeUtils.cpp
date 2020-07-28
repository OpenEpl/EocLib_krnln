#include <catch2/catch.hpp>
#include <e/lib/krnln/DateTimeUtils.h>
using namespace e::lib::krnln;
inline const e::system::datetime D_20191231_050607(43830.21258101852);
TEST_CASE("DateTimeUtils::BuildDateTime", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::BuildDateTime(2019) == e::system::datetime(43466.0));
    REQUIRE(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7) == D_20191231_050607);
}

TEST_CASE("DateTimeUtils::DateTimeToString", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7)) == "2019年12月31日5时6分7秒");
    REQUIRE(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31)) == "2019年12月31日");
    REQUIRE(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7), DateTimeUtils::ConvertDate) == "2019年12月31日");
    REQUIRE(DateTimeUtils::DateTimeToString(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7), DateTimeUtils::ConvertTime) == "5时6分7秒");
}

TEST_CASE("DateTimeUtils::GetTimePart", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::GetTimePart(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7)) == DateTimeUtils::BuildDateTime(2000, 1, 1, 5, 6, 7));
}

TEST_CASE("DateTimeUtils::GetDatePart", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::GetDatePart(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7)) == DateTimeUtils::BuildDateTime(2019, 12, 31));
}

TEST_CASE("DateTimeUtils::GetHourPart", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::GetHourPart(D_20191231_050607) == 5);
}

TEST_CASE("DateTimeUtils::GetMinutePart", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::GetMinutePart(D_20191231_050607) == 6);
}

TEST_CASE("DateTimeUtils::GetSecondPart", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::GetSecondPart(D_20191231_050607) == 7);
}