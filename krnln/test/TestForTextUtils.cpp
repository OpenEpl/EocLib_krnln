#include <catch2/catch.hpp>
#include <e/lib/krnln/TextUtils.h>
using namespace e::lib::krnln;
TEST_CASE("GetCodePoint", "[TextUtils]")
{
	REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), 4) == 0);
	REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), -1) == 0);
	REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), 1) == int32_t('a'));
	REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), 3) == int32_t('d'));
	REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd")) == int32_t('a'));
}

TEST_CASE("Len", "[TextUtils]")
{
	REQUIRE(TextUtils::Len(EOC_STR_CONST("asd")) == 3);
	REQUIRE(TextUtils::Len(EOC_STR_CONST("")) == 0);
	REQUIRE(TextUtils::Len(e::system::string(nullptr)) == 0);
}