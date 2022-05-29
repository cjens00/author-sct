#pragma once

#include <uv.h>
#include <vector>

namespace Author::Core
{
    enum Transport{
        TCP = 0,
        UDP = 1
    };

    class Server
    {
        uv_loop_t *loop;
        sockaddr_in addr;
        uv_tcp_t server;
        int backlog;
        std::vector<int> tcpPorts;
        std::vector<int> udpPorts;
    public:
        Server();
        int Listen();
        int Start();
        int GetPort(Transport txp, int index);
    };
}