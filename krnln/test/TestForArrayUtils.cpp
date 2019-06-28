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
}