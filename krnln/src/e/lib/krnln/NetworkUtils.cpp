#include "NetworkUtils.h"
#include <Ws2tcpip.h>
#include <Wspiapi.h>
#include <iphlpapi.h>
#include <IPExport.h>
#include <icmpapi.h>
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

    int32_t ICMPPing(const e::system::string &hostname, std::optional<int32_t> timeout)
    {
        SocketInitializer wsa;
        int32_t result = -1;
        addrinfo *info;
        int error = getaddrinfo(hostname.c_str(), nullptr, nullptr, &info);
        if (error == 0)
        {
            IP_OPTION_INFORMATION optionInfo;
            memset(&optionInfo, 0, sizeof(IP_OPTION_INFORMATION));
            optionInfo.Ttl = 128;

            constexpr int packetSize = 32;
            uint8_t pSend[packetSize];
            memset(pSend, 'E', packetSize);
            if (info->ai_family == AF_INET)
            {
                constexpr int replySize = sizeof(ICMP_ECHO_REPLY) + packetSize + 8;
                uint8_t pReply[replySize];
                auto pEchoReply = (ICMP_ECHO_REPLY *)pReply;

                HANDLE hIp = IcmpCreateFile();
                DWORD nPackets = IcmpSendEcho(hIp, ((sockaddr_in *)info->ai_addr)->sin_addr.s_addr, pSend, 32, &optionInfo, pReply, replySize, timeout.value_or(10000));
                if (nPackets > 0 && pEchoReply->Status == 0)
                {
                    result = pEchoReply->RoundTripTime;
                }
                IcmpCloseHandle(hIp);
            }
            else if (info->ai_family == AF_INET6)
            {
                sockaddr_in6 srcAddress;
                srcAddress.sin6_family = AF_INET6;
                srcAddress.sin6_flowinfo = 0;
                srcAddress.sin6_port = 0;
                srcAddress.sin6_scope_id = 0;
                srcAddress.sin6_addr = in6addr_any;

                constexpr int replySize = sizeof(ICMPV6_ECHO_REPLY) + packetSize + 8;
                uint8_t pReply[replySize];
                auto pEchoReply = (ICMPV6_ECHO_REPLY *)pReply;

                HANDLE hIp = Icmp6CreateFile();
                DWORD nPackets = Icmp6SendEcho2(hIp, nullptr, nullptr, nullptr, &srcAddress, (sockaddr_in6 *)(info->ai_addr), pSend, packetSize, &optionInfo, pReply, replySize, timeout.value_or(10000));
                if (nPackets > 0 && pEchoReply->Status == 0)
                {
                    result = pEchoReply->RoundTripTime;
                }
                IcmpCloseHandle(hIp);
            }
            freeaddrinfo(info);
        }
        return result;
    }
}