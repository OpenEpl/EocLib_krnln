#include <catch2/catch.hpp>
#include <e/lib/krnln/BinUtils.h>
using namespace e::lib::krnln;
TEST_CASE("BinUtils::Len", "[BinUtils]")
{
    CHECK(BinUtils::Len(e::system::bin(size_t(0))) == 0);
    CHECK(BinUtils::Len(e::system::bin{1, 2, 3, 4, 5, 6}) == 6);
}
TEST_CASE("BinUtils::Left", "[BinUtils]")
{
    CHECK(BinUtils::Left(e::system::bin{1, 2, 3, 4, 5, 6}, -5) == e::system::bin{});
    CHECK(BinUtils::Left(e::system::bin{1, 2, 3, 4, 5, 6}, 3) == e::system::bin{1, 2, 3});
    CHECK(BinUtils::Left(e::system::bin{1, 2, 3, 4, 5, 6}, 8) == e::system::bin{1, 2, 3, 4, 5, 6});
}
TEST_CASE("BinUtils::Right", "[BinUtils]")
{
    CHECK(BinUtils::Right(e::system::bin{1, 2, 3, 4, 5, 6}, -5) == e::system::bin{});
    CHECK(BinUtils::Right(e::system::bin{1, 2, 3, 4, 5, 6}, 3) == e::system::bin{4, 5, 6});
    CHECK(BinUtils::Right(e::system::bin{1, 2, 3, 4, 5, 6}, 8) == e::system::bin{1, 2, 3, 4, 5, 6});
}

TEST_CASE("BinUtils::SubBin", "[BinUtils]")
{
    CHECK(BinUtils::SubBin(e::system::bin{1, 2, 3, 4, 5, 6}, 7, 1) == e::system::bin{});
    CHECK(BinUtils::SubBin(e::system::bin{1, 2, 3, 4, 5, 6}, 1, -1) == e::system::bin{});
    CHECK(BinUtils::SubBin(e::system::bin{1, 2, 3, 4, 5, 6}, 4, 2) == e::system::bin{4, 5});
    CHECK(BinUtils::SubBin(e::system::bin{1, 2, 3, 4, 5, 6}, 4, 8) == e::system::bin{4, 5, 6});
}

TEST_CASE("BinUtils::Space", "[BinUtils]")
{
    CHECK(BinUtils::Space(-1) == e::system::bin{});
    CHECK(BinUtils::Space(5) == e::system::bin{0, 0, 0, 0, 0});
}

TEST_CASE("BinUtils::IndexOf", "[BinUtils]")
{
    CHECK(BinUtils::IndexOf(e::system::bin{1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1, 1, 2, 2}, e::system::bin{2, 3, 3, 2}) == 2);
    CHECK(BinUtils::IndexOf(e::system::bin{1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1, 1, 2, 2}, e::system::bin{2, 3, 3, 2}, 3) == 8);
    CHECK(BinUtils::IndexOf(e::system::bin{2, 2, 3, 3, 2}, e::system::bin{2, 3, 3, 2}) == 2);
    CHECK(BinUtils::IndexOf(e::system::bin{9, 9, 9, 9, 9, 9, 9}, e::system::bin{2, 3, 3}) == -1);
    CHECK(BinUtils::IndexOf(e::system::bin{9, 9, 9, 9, 2, 3, 3}, e::system::bin{2, 3, 3}) == 5);
}

TEST_CASE("BinUtils::LastIndex", "[BinUtils]")
{
    CHECK(BinUtils::LastIndexOf(e::system::bin{5, 4, 4, 1, 2, 1, 2, 5, 4, 4, 4, 8, 7, 4, 6, 7, 8, 8, 8, 9, 10, 11}, e::system::bin{5, 4, 4}) == 8);
    CHECK(BinUtils::LastIndexOf(e::system::bin{9, 9, 9, 9, 9, 9, 9}, e::system::bin{2, 3, 3}) == -1);
    CHECK(BinUtils::LastIndexOf(e::system::bin{2, 3, 3, 9, 9, 9, 9}, e::system::bin{2, 3, 3}) == 1);
}