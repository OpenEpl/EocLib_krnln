#pragma once
#include <e/system/basic_type.h>
namespace e::lib::krnln::NetworkUtils
{
    struct SocketInitializer
    {
        int error;
        SocketInitializer(uint16_t versionRequested);
        SocketInitializer();
        ~SocketInitializer();
    };
    e::system::string HostNameToAddress(const e::system::string &hostname);
    e::system::string AddressToHostName(const e::system::string &hostname);
    e::system::string GetHostName();
    int32_t ICMPPing(const e::system::string &hostname, std::optional<int32_t> timeout = std::nullopt);
}