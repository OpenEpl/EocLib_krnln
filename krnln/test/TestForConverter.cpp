#include <catch2/catch.hpp>
#include <e/lib/krnln/Converter.h>
using namespace e::lib;
TEST_CASE("krnln::ToString", "[Converter]")
{
    CHECK(krnln::ToString(123) == "123");
    CHECK(krnln::ToString(e::system::bin{0x52, 0x49, 0x46, 0x46}) == "RIFF");
    CHECK(krnln::ToString(e::system::array<uint8_t>{0x52, 0x49, 0x46, 0x46}) == "RIFF");
    int32_t t = 0x46464952;
    CHECK(krnln::ToString(e::system::array<int32_t>{t}) == "RIFF");
    CHECK(krnln::ToString(e::system::array<float>{*reinterpret_cast<float *>(&t)}) == "RIFF");
}