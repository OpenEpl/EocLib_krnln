#include <catch2/catch.hpp>
#include <e/lib/krnln/MathUtils.h>
using namespace e::lib::krnln;
TEST_CASE("MathUtils::FloorToInt32", "[MathUtils]")
{
    CHECK(MathUtils::FloorToInt32(7.8) == 7);
    CHECK(MathUtils::FloorToInt32(-7.8) == -8);
}
TEST_CASE("MathUtils::TruncToInt32", "[MathUtils]")
{
    CHECK(MathUtils::TruncToInt32(7.8) == 7);
    CHECK(MathUtils::TruncToInt32(-7.8) == -7);
}
TEST_CASE("MathUtils::Round", "[MathUtils]")
{
    CHECK(MathUtils::Round(1056.65, 1) == 1056.7);
    CHECK(MathUtils::Round(1056.65, 0) == 1057);
    CHECK(MathUtils::Round(1056.65, -1) == 1060);
}
TEST_CASE("MathUtils::GetSign", "[MathUtils]")
{
    CHECK(MathUtils::GetSign(123) == 1);
    CHECK(MathUtils::GetSign(0) == 0);
    CHECK(MathUtils::GetSign(-123) == -1);
}
