#include <catch2/catch.hpp>
#include <e/lib/krnln/LogicUtils.h>
using namespace e::lib::krnln;
TEST_CASE("LogicUtils::IIf", "[LogicUtils]")
{
    CHECK(LogicUtils::IIf(true, 1, 2) == e::system::any(1));
    CHECK(LogicUtils::IIf(false, 1, 2) == e::system::any(2));
}
TEST_CASE("LogicUtils::Choose", "[LogicUtils]")
{
    CHECK(LogicUtils::Choose(1, 1.0, 2.0, 3.0, 4.0) == e::system::any(1.0));
    CHECK(LogicUtils::Choose(2, 1.0, 2.0, 3.0, 4.0) == e::system::any(2.0));
    CHECK(LogicUtils::Choose(3, 1.0, 2.0, 3.0, 4.0) == e::system::any(3.0));
    CHECK(LogicUtils::Choose(4, 1.0, 2.0, 3.0, 4.0) == e::system::any(4.0));
    CHECK_THROWS_AS(LogicUtils::Choose(-5, 1.0, 2.0, 3.0, 4.0), std::out_of_range);
    CHECK_THROWS_AS(LogicUtils::Choose(0, 1.0, 2.0, 3.0, 4.0), std::out_of_range);
    CHECK_THROWS_AS(LogicUtils::Choose(5, 1.0, 2.0, 3.0, 4.0), std::out_of_range);
}