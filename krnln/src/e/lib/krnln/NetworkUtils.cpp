#include "NetworkUtils.h"
#include <Ws2tcpip.h>
#include <Wspiapi.h>
namespace e::lib::krnln::NetworkUtils
{
    SocketInitializer::SocketInitializer(uint16_t versionRequested)
    {
        WSADATA wsaData;
        this->error = WSAStartup(versionRequested, &wsaData);
    }

    SocketInitializer::SocketInitializer() : SocketInitializer(INT16_C(0x0202))
    {
    }

    SocketInitializer::~SocketInitializer()
    {
        if (!this->error)
        {
            WSACleanup();
        }
    }

    e::system::string HostNameToAddress(const e::system::string &hostname)
    {
        SocketInitializer wsa;
        addrinfo *info;
        int error = getaddrinfo(hostname.c_str(), nullptr, nullptr, &info);
        if (error != 0)
        {
            return e::system::string(nullptr);
        }
        e::system::string result(NI_MAXHOST);
        // For compatibility reasons, return the IPv4 address if available
        addrinfo *ptr;
        for (ptr = info; ptr != NULL; ptr = ptr->ai_next)
        {
            if (ptr->ai_family == AF_INET)
                break;
        }
        // When IPv4 is not available, return the first address (usually IPv6 address)
        if (ptr == nullptr)
        {
            ptr = info;
        }
        getnameinfo(ptr->ai_addr, (socklen_t)ptr->ai_addrlen, result.c_str(), NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
        freeaddrinfo(info);
        return result;
    }

    e::system::string AddressToHostName(const e::system::string &hostname)
    {
        SocketInitializer wsa;
        addrinfo *info;
        int error = getaddrinfo(hostname.c_str(), nullptr, nullptr, &info);
        if (error != 0)
        {
            return e::system::string(nullptr);
        }
        e::system::string result(NI_MAXHOST);
        getnameinfo(info->ai_addr, (socklen_t)info->ai_addrlen, result.c_str(), NI_MAXHOST, nullptr, 0, 0);
        freeaddrinfo(info);
        return result;
    }

    e::system::string GetHostName()
    {
        SocketInitializer wsa;
        e::system::string result(256);
        gethostname(result.c_str(), 256);
        return result;
    }
}