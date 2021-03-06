﻿#include <catch2/catch.hpp>
#include <e/lib/krnln/NetworkUtils.h>
using namespace e::lib::krnln;
TEST_CASE("NetworkUtils::HostNameToAddress", "[NetworkUtils]")
{
    CHECK(NetworkUtils::HostNameToAddress("127.0.0.1") == EOC_STR_CONST("127.0.0.1"));
    CHECK(NetworkUtils::HostNameToAddress("::1") == EOC_STR_CONST("::1"));
    CHECK(NetworkUtils::HostNameToAddress("localhost") == EOC_STR_CONST("127.0.0.1"));
}

TEST_CASE("NetworkUtils::ICMPPing", "[NetworkUtils]")
{
    CHECK(NetworkUtils::ICMPPing("127.0.0.1") != -1);
    CHECK(NetworkUtils::ICMPPing("::1") != -1);
    CHECK(NetworkUtils::ICMPPing("localhost") != -1);
}