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

TEST_CASE("ArrayUtils::Init", "[ArrayUtils]")
{
    e::system::array<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ArrayUtils::Init(x);
    CHECK(x == e::system::array<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
}

TEST_CASE("ArrayUtils::Insert", "[ArrayUtils]")
{
    e::system::array<int> x = {1, 2, 3, 4, 5, 6};
    ArrayUtils::Insert(x, 6, -1.0f);
    CHECK(x == e::system::array<int>{1, 2, 3, 4, 5, -1, 6});
    ArrayUtils::Insert(x, 8, -2);
    CHECK(x == e::system::array<int>{1, 2, 3, 4, 5, -1, 6, -2});
    ArrayUtils::Insert(x, 0, -3);
    CHECK(x == e::system::array<int>{1, 2, 3, 4, 5, -1, 6, -2});
    ArrayUtils::Insert(x, 1, -3);
    CHECK(x == e::system::array<int>{-3, 1, 2, 3, 4, 5, -1, 6, -2});
}

TEST_CASE("ArrayUtils::Sort", "[ArrayUtils]")
{
    e::system::array<int> x = {3, 0, 2, 7, 5, 320, 8415, 282};
    ArrayUtils::Sort(x);
    CHECK(x == e::system::array<int>{0, 2, 3, 5, 7, 282, 320, 8415});
    ArrayUtils::Sort(x, false);
    CHECK(x == e::system::array<int>{8415, 320, 282, 7, 5, 3, 2, 0});
}