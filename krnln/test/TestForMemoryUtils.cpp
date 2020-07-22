#include <catch2/catch.hpp>
#include <e/lib/krnln/MemoryUtils.h>
using namespace e::lib::krnln;
TEST_CASE("MemoryUtils", "[MemoryUtils]")
{
    char data[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    intptr_t dataPtr = (intptr_t)&data;
    SECTION("MemoryUtils::ReadText")
    {
        CHECK(MemoryUtils::ReadText(dataPtr) == "\x01\x02\x03\x04\x05\x06\x07\x08");
    }
    SECTION("MemoryUtils::ReadInt32")
    {
        CHECK(MemoryUtils::ReadInt32(dataPtr) == *(int32_t *)dataPtr);
    }
    SECTION("MemoryUtils::ReadFloat")
    {
        CHECK(MemoryUtils::ReadFloat(dataPtr) == *(float *)dataPtr);
    }
    SECTION("MemoryUtils::ReadDouble")
    {
        CHECK(MemoryUtils::ReadDouble(dataPtr) == *(double *)dataPtr);
    }
    SECTION("MemoryUtils::ReadDouble")
    {
        CHECK(MemoryUtils::ReadToBin(dataPtr, 9) == e::system::bin{1, 2, 3, 4, 5, 6, 7, 8, 0});
    }
}

TEST_CASE("MemoryUtils::WriteMemory", "[MemoryUtils]")
{
    std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(9);
    MemoryUtils::WriteMemory(0x1020304050607080LL, (intptr_t)data.get());
    CHECK((*(int64_t *)data.get()) == 0x1020304050607080LL);
    MemoryUtils::WriteMemory(EOC_STR_CONST("asd"), (intptr_t)data.get());
    CHECK(memcmp(data.get(), "asd", 4) == 0);
    MemoryUtils::WriteMemory(e::system::any(e::system::bin{1, 2, 3}), (intptr_t)data.get());
    CHECK(memcmp(data.get(), "\x01\x02\x03", 3) == 0);
    MemoryUtils::WriteMemory(e::system::any(e::system::bin{4, 5, 6}), (intptr_t)data.get(), 2);
    CHECK(memcmp(data.get(), "\x04\x05\x03", 3) == 0);
}