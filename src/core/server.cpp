#include <iostream>
#include "core/server.h"

/// Currently using https://github.com/delaemon/libuv-tutorial/blob/master/tcp-echo-server.c
/// as a skeleton to get the network code up and functional. Thank you @delaemon.
/// Under construction (Basically, it's an absolute disaster).
/// Please message me on GitHub if interested in contributing
/// as the project is still very new and subject to change (completely).
/// @cjens00 :: https://github.com/cjens00/

// Singleton, the only instance of ServerData that should exist
Author::Core::Server::ServerData sd;

void Author::Core::Server::InitializeServerData(Console *console)
{
    sd.loop = uv_default_loop();
    sd.console = console;
}

Author::Core::Server::ServerData &Author::Core::Server::GetServerData()
{
    return sd;
}

int Author::Core::ServerLauncher::Start(Console *console)
{
    Author::Core::Server::InitializeServerData(console);
    auto serverData = Author::Core::Server::GetServerData();
    uv_tcp_t server;
    uv_tcp_init(serverData.loop, &server);
    uv_ip4_addr("0.0.0.0", 12908, &serverData.addr);
    uv_tcp_bind(&server, (const struct sockaddr *) &serverData.addr, 0);
    int r = uv_listen((uv_stream_t *) &server, 128, Author::Core::Server::OnNewConnection);
    if (r)
    {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    int rv = uv_run(serverData.loop, UV_RUN_DEFAULT);
    return rv;
}

void Author::Core::Server::AllocateBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    buf->base = (char *) malloc(suggested_size);
    buf->len = suggested_size;
}

void Author::Core::Server::EchoWrite(uv_write_t *req, int status)
{
    if (status) fprintf(stderr, "Write error %s\n", uv_strerror(status));
    free(req);
}

void Author::Core::Server::EchoRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread < 0)
    {
        if (nread != UV_EOF)
        {
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
            uv_close((uv_handle_t *) client, nullptr);
        }
    } else if (nread > 0)
    {
        uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
        uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
        uv_write(req, client, &wrbuf, 1, EchoWrite);
    }
    if (buf->base) free(buf->base);
}

void Author::Core::Server::OnNewConnection(uv_stream_t *server, int status)
{
    if (status < 0)
    {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    auto *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(sd.loop, client);
    if (uv_accept(server, (uv_stream_t *) client) == 0)
        uv_read_start((uv_stream_t *) client,
                      Author::Core::Server::AllocateBuffer,
                      Author::Core::Server::EchoRead);
    else uv_close((uv_handle_t *) client, nullptr);
}
