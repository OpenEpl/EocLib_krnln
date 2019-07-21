#include <catch2/catch.hpp>
#include <e/lib/krnln/TextUtils.h>
using namespace e::lib::krnln;
TEST_CASE("TextUtils::GetCodePoint", "[TextUtils]")
{
    REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), 4) == 0);
    REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), -1) == 0);
    REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), 1) == int32_t('a'));
    REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd"), 3) == int32_t('d'));
    REQUIRE(TextUtils::GetCodePoint(EOC_STR_CONST("asd")) == int32_t('a'));
}

TEST_CASE("TextUtils::Len", "[TextUtils]")
{
    REQUIRE(TextUtils::Len(EOC_STR_CONST("asd")) == 3);
    REQUIRE(TextUtils::Len(EOC_STR_CONST("")) == 0);
    REQUIRE(TextUtils::Len(e::system::string(nullptr)) == 0);
}

TEST_CASE("TextUtils::SubString", "[TextUtils]")
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

TEST_CASE("TextUtils::IndexOf", "[TextUtils]")
{
    CHECK(TextUtils::IndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("S"), std::nullopt, true) == 2);
    CHECK(TextUtils::IndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("s"), -250) == 2);
    CHECK(TextUtils::IndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("s"), 2) == 2);
    CHECK(TextUtils::IndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("s"), 3) == 5);
    CHECK(TextUtils::IndexOf(EOC_STR_CONST("asdfs"), nullptr) == -1);
    CHECK(TextUtils::IndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("")) == -1);
    CHECK(TextUtils::IndexOf(nullptr, EOC_STR_CONST("s")) == -1);
    CHECK(TextUtils::IndexOf(nullptr, nullptr) == -1);
    CHECK(TextUtils::IndexOf(EOC_STR_CONST("我爱你不爱我"), EOC_STR_CONST("爱")) == 3);
}

TEST_CASE("TextUtils::LastIndexOf", "[TextUtils]")
{
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("S"), std::nullopt, true) == 5);
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("s"), -2) == -1);
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("s"), 555) == 5);
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("s"), 2) == 2);
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("s"), 1) == -1);
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("asdfs"), nullptr) == -1);
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("asdfs"), EOC_STR_CONST("")) == -1);
    CHECK(TextUtils::LastIndexOf(nullptr, EOC_STR_CONST("s")) == -1);
    CHECK(TextUtils::LastIndexOf(nullptr, nullptr) == -1);
    CHECK(TextUtils::LastIndexOf(EOC_STR_CONST("我爱你不爱我"), EOC_STR_CONST("我")) == 11);
}

TEST_CASE("TextUtils::ToLower", "[TextUtils]")
{
    CHECK(TextUtils::ToLower(nullptr).isEmpty());
    CHECK(TextUtils::ToLower("").isEmpty());
    CHECK(TextUtils::ToLower("hELLO") == "hello");
}

TEST_CASE("TextUtils::ToUpper", "[TextUtils]")
{
    CHECK(TextUtils::ToUpper(nullptr).isEmpty());
    CHECK(TextUtils::ToUpper("").isEmpty());
    CHECK(TextUtils::ToUpper("Hello") == "HELLO");
}

TEST_CASE("TextUtils::Space", "[TextUtils]")
{
    CHECK(TextUtils::Space(0).isEmpty());
    CHECK(TextUtils::Space(-1).isEmpty());
    CHECK(TextUtils::Space(5) == "     ");
}

TEST_CASE("TextUtils::Repeat", "[TextUtils]")
{
    CHECK(TextUtils::Repeat(10, "a") == "aaaaaaaaaa");
}

TEST_CASE("TextUtils::Replace", "[TextUtils]")
{
    CHECK(TextUtils::Replace("123456", 2, 3, "as") == "1as56");
    CHECK(TextUtils::Replace("123456", -2, 3, "as") == "as456");
    CHECK(TextUtils::Replace("123456", 9, 3, "as") == "123456as");
    CHECK(TextUtils::Replace("123456", 2, 0, "as") == "1as23456");
    CHECK(TextUtils::Replace("123456", 2, 2, std::nullopt) == "1456");
}

TEST_CASE("TextUtils::Split", "[TextUtils]")
{
    CHECK(TextUtils::Split("1,2,3,4,5,6", std::nullopt) == e::system::array<e::system::string>{"1", "2", "3", "4", "5", "6"});
    CHECK(TextUtils::Split("1,2,3,4,5,6,", std::nullopt) == e::system::array<e::system::string>{"1", "2", "3", "4", "5", "6"});
    CHECK(TextUtils::Split("1,2,3,4,5,6,,", std::nullopt) == e::system::array<e::system::string>{"1", "2", "3", "4", "5", "6", ""});
    CHECK(TextUtils::Split("123456", "") == e::system::array<e::system::string>{"123456"});
    CHECK(TextUtils::Split("", "") == e::system::array<e::system::string>{});
    CHECK(TextUtils::Split("", "asd") == e::system::array<e::system::string>{});
    CHECK(TextUtils::Split("1,2,3,4,5,6", std::nullopt, 8) == e::system::array<e::system::string>{"1", "2", "3", "4", "5", "6"});
    CHECK(TextUtils::Split("1,2,3,4,5,6", std::nullopt, 2) == e::system::array<e::system::string>{"1", "2"});
    CHECK(TextUtils::Split("1,2,3,4,5,6", std::nullopt, -1) == e::system::array<e::system::string>{});
    CHECK(TextUtils::Split("1$%^2$%^3$%^4$%^5$%^6$%^", "$%^") == e::system::array<e::system::string>{"1", "2", "3", "4", "5", "6"});
    CHECK(TextUtils::Split("1$%^2$%^3$%^4$%^5$%^6$%^", "$%^") == e::system::array<e::system::string>{"1", "2", "3", "4", "5", "6"});
    CHECK(TextUtils::Split("1$%^2$%^3$%^4$%^5$%^6$%^$%^", "$%^") == e::system::array<e::system::string>{"1", "2", "3", "4", "5", "6", ""});
}

TEST_CASE("TextUtils::ReplaceSubText", "[TextUtils]")
{
    CHECK(TextUtils::ReplaceSubText("1,2,3,4,5,6,", ",") == "123456");
    CHECK(TextUtils::ReplaceSubText("1,2,3,4,5,6", ",", "^^") == "1^^2^^3^^4^^5^^6");
    CHECK(TextUtils::ReplaceSubText("1,2,3,4,5,6", ",", "^^", 3) == "1,2^^3^^4^^5^^6");
    CHECK(TextUtils::ReplaceSubText("1a2a3a4a5a6", "A", "", 1, std::nullopt, std::nullopt) == "1a2a3a4a5a6");
    CHECK(TextUtils::ReplaceSubText("1a2a3a4a5a6", "A", "", 1, std::nullopt, true) == "1a2a3a4a5a6");
    CHECK(TextUtils::ReplaceSubText("1a2a3a4a5a6", "a", "", 1, std::nullopt, true) == "123456");
    CHECK(TextUtils::ReplaceSubText("1a2a3a4a5a6", "A", "", 1, std::nullopt, false) == "123456");
}