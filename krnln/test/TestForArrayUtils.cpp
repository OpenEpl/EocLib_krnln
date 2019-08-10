#include <catch2/catch.hpp>
#include <e/lib/krnln/ArrayUtils.h>
using namespace e::lib::krnln;
TEST_CASE("ArrayUtils", "[ArrayUtils]")
{
    e::system::array<int> test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    REQUIRE(ArrayUtils::GetSize(test) == 10);
    REQUIRE(ArrayUtils::GetUBound(test) == 10);
    REQUIRE(ArrayUtils::GetUBound(test, 1) == 10);
    ArrayUtils::Redim(test, true, 2);
    REQUIRE(ArrayUtils::GetSize(test) == 2);
    REQUIRE(test.At_CStyle(1) == 2);
    {
        e::system::array<int> bar;
        ArrayUtils::CopyTo(bar, test);
        REQUIRE(ArrayUtils::GetSize(bar) == 2);
        REQUIRE(bar.At_CStyle(1) == 2);
    }
    ArrayUtils::Clear(test);
    REQUIRE(ArrayUtils::GetSize(test) == 0);
    ArrayUtils::Append(test, 1, 2, 3);
    CHECK(test == e::system::array<int>{1, 2, 3});
}

TEST_CASE("ArrayUtils::Remove", "[ArrayUtils]")
{
    e::system::array<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ArrayUtils::Remove(x, 0, 1);
    CHECK(x == e::system::array<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    ArrayUtils::Remove(x, 1, 2);
    CHECK(x == e::system::array<int>{3, 4, 5, 6, 7, 8, 9, 10});
    ArrayUtils::Remove(x, 5, 10000);
    CHECK(x == e::system::array<int>{3, 4, 5, 6});
}