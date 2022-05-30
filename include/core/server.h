#pragma once

#include <uv.h>
#include <vector>
#include <functional>
#include "core/ui/console.h"

namespace Author::Core::Server
{
    struct ServerData
    {
        uv_loop_t *loop;
        Console *console;
        struct sockaddr_in addr;
    };

    void InitializeServerData(Console *console);

    ServerData &GetServerData();

    void AllocateBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);

    void EchoWrite(uv_write_t *req, int status);

    void EchoRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);

    void OnNewConnection(uv_stream_t *server, int status);
}

namespace Author::Core
{
    class ServerLauncher
    {
    public:
        ServerLauncher() = default;

        int Start(Console *console);
    };
}