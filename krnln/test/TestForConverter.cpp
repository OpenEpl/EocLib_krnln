#include <catch2/catch.hpp>
#include <e/lib/krnln/Converter.h>
using namespace e::lib;
TEST_CASE("krnln::ToString", "[Converter]")
{
    CHECK(krnln::ToString(UINT8_C(123)) == "123");
    CHECK(krnln::ToString(INT16_C(123)) == "123");
    CHECK(krnln::ToString(INT16_C(-123)) == "-123");
    CHECK(krnln::ToString(INT32_C(123)) == "123");
    CHECK(krnln::ToString(INT32_C(-123)) == "-123");
    CHECK(krnln::ToString(INT64_C(123456789123456)) == "123456789123456");
    CHECK(krnln::ToString(INT64_C(-123456789123456)) == "-123456789123456");
    CHECK(krnln::ToString(e::system::bin{0x52, 0x49, 0x46, 0x46}) == "RIFF");
    CHECK(krnln::ToString(e::system::array<uint8_t>{0x52, 0x49, 0x46, 0x46}) == "RIFF");
    int32_t t = 0x46464952;
    CHECK(krnln::ToString(e::system::array<int32_t>{t}) == "RIFF");
    CHECK(krnln::ToString(e::system::array<float>{*reinterpret_cast<float *>(&t)}) == "RIFF");
}

TEST_CASE("krnln::ToInt32(e::system::string)", "[Converter]")
{
    CHECK(krnln::ToInt32(EOC_STR_CONST("123")) == 123);
    CHECK(krnln::ToInt32(EOC_STR_CONST("-123")) == -123);

    CHECK(krnln::ToInt32(EOC_STR_CONST("0")) == 0);
    CHECK(krnln::ToInt32(EOC_STR_CONST("2147483647")) == 2147483647);
    CHECK(krnln::ToInt32(EOC_STR_CONST("-2147483648")) == -(int32_t)2147483648);

    //Wrap-Around Mode
    CHECK(krnln::ToInt32(EOC_STR_CONST("68719476735")) == -1);
    CHECK(krnln::ToInt32(EOC_STR_CONST("66571993087")) == 2147483647);
}

TEST_CASE("krnln::ToUInt8(e::system::string)", "[Converter]")
{
    CHECK(krnln::ToUInt8(EOC_STR_CONST("123")) == 123);

    //Wrap-Around Mode
    CHECK(krnln::ToUInt8(EOC_STR_CONST("-123")) == 133);
}