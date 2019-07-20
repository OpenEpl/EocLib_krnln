#include <catch2/catch.hpp>
#include <e/lib/krnln/DateTimeUtils.h>
using namespace e::lib::krnln;
TEST_CASE("DateTimeUtils::BuildDateTime", "[DateTimeUtils]")
{
    REQUIRE(DateTimeUtils::BuildDateTime(2019) == 43466.0);
    REQUIRE(DateTimeUtils::BuildDateTime(2019, 12, 31, 5, 6, 7).value == 43830.21258101852);
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