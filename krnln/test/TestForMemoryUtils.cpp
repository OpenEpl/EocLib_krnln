#include <catch2/catch.hpp>
#include <e/lib/krnln/MemoryUtils.h>
using namespace e::lib::krnln;
TEST_CASE("MemoryUtils", "[MemoryUtils]")
{
    char data[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    intptr_t dataPtr = (intptr_t)&data;
    SECTION("ReadText")
    {
        CHECK(MemoryUtils::ReadText(dataPtr) == "\x01\x02\x03\x04\x05\x06\x07\x08");
    }
    SECTION("ReadInt32")
    {
        CHECK(MemoryUtils::ReadInt32(dataPtr) == *(int32_t *)dataPtr);
    }
    SECTION("ReadFloat")
    {
        CHECK(MemoryUtils::ReadFloat(dataPtr) == *(float *)dataPtr);
    }
    SECTION("ReadDouble")
    {
        CHECK(MemoryUtils::ReadDouble(dataPtr) == *(double *)dataPtr);
    }
    SECTION("ReadDouble")
    {
        CHECK(MemoryUtils::ReadToBin(dataPtr, 9) == e::system::bin{1, 2, 3, 4, 5, 6, 7, 8, 0});
    }
}