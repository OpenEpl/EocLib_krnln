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

TEST_CASE("SubString", "[TextUtils]")
{
	CHECK(TextUtils::Left(EOC_STR_CONST("asdf"), -2) == nullptr);
	CHECK(TextUtils::Left(EOC_STR_CONST("asdf"), 2) == EOC_STR_CONST("as"));
	CHECK(TextUtils::Left(EOC_STR_CONST("asdf"), 5) == EOC_STR_CONST("asdf"));

	CHECK(TextUtils::Right(EOC_STR_CONST("asdf"), -2) == nullptr);
	CHECK(TextUtils::Right(EOC_STR_CONST("asdf"), 2) == EOC_STR_CONST("df"));
	CHECK(TextUtils::Right(EOC_STR_CONST("asdf"), 5) == EOC_STR_CONST("asdf"));


	CHECK(TextUtils::SubStr(EOC_STR_CONST("asdf"), 2, 2) == EOC_STR_CONST("sd"));
	CHECK(TextUtils::SubStr(EOC_STR_CONST("asdf"), 2, 6) == EOC_STR_CONST("sdf"));
	CHECK(TextUtils::SubStr(EOC_STR_CONST("asdf"), 5, 1) == nullptr);
	CHECK(TextUtils::SubStr(EOC_STR_CONST("asdf"), 1, -1) == nullptr);
	CHECK(TextUtils::SubStr(EOC_STR_CONST("asdf"), 0, 1) == nullptr);
}