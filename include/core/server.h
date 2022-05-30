#pragma once

#include <uv.h>
#include <vector>
#include <functional>

namespace Author::Core
{
    enum Transport{
        TCP = 0,
        UDP = 1
    };

    enum Callback{
        OnClientConnected = 0,
        AllocateBuffer = 1,
        EchoRead = 2,
        EchoWrite = 3,
    };

    struct ServerData {
        uv_loop_t *loop;
        sockaddr_in addr;
        uv_tcp_t tcpServer;
        int backlog;
    };

    class Server
    {
        ServerData sd;
        std::vector<int> tcpPorts;
        std::vector<int> udpPorts;
    public:
        Server();
        int Listen();
        int Start();
        int GetPort(Transport txp, int index);
        void OnClientConnected(uv_stream_t *server, int status);
        void AllocateBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
        void EchoRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
        void EchoWrite(uv_write_t *req, int status);

        static void *WrapCallback(void *context, Callback cb);
    };
}