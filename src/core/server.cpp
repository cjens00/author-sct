#include <iostream>
#include <format>
#include "core/server.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-cast"
Author::Core::Server::Server()
{
    this->sd = {};

    sd.loop = uv_default_loop();
    uv_tcp_init(sd.loop, &sd.tcpServer);
    uv_ip4_addr("0.0.0.0", 5770, &sd.addr);
    uv_tcp_bind(&sd.tcpServer, (const struct sockaddr *) &sd.addr, 0);
}

int Author::Core::Server::Listen()
{
    return uv_listen((uv_stream_t *) &sd.tcpServer, sd.backlog, OnClientConnected);
}

int Author::Core::Server::Start()
{
    int rc = uv_run(sd.loop, UV_RUN_DEFAULT);
    return rc;
}

int Author::Core::Server::GetPort(Author::Core::Transport txp, int index)
{
    if (txp == Transport::TCP && tcpPorts.size() > index) return tcpPorts[index];
    else std::cerr << std::format("Requested TCP port does not exist (index > tcpPorts.size()).");
    if (txp == Transport::UDP && udpPorts.size() > index) return udpPorts[index];
    else std::cerr << std::format("Requested UDP port does not exist (index > udpPorts.size()).");
    return -1;
}

void Author::Core::Server::OnClientConnected(uv_stream_t *server, int status)
{
    if (status < 0)
    {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    auto *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(sd.loop, client);
    if (uv_accept(server, (uv_stream_t *) client) == 0)
    {
        uv_read_start(
                (uv_stream_t *) client,
                static_cast<uv_alloc_cb>(WrapCallback(this, Callback::AllocateBuffer)),
                static_cast<uv_read_cb>(WrapCallback(this, Callback::EchoRead))
        );
    } else
    {
        uv_close((uv_handle_t *) client, NULL);
    }
}


void Author::Core::Server::AllocateBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{

}

void Author::Core::Server::EchoRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{

}

void Author::Core::Server::EchoWrite(uv_write_t *req, int status)
{

}


void *Author::Core::Server::WrapCallback(void *context, Callback cb)
{
    switch (cb)
    {
        case Callback::OnClientConnected:
            static_cast<Server *>(context)->OnClientConnected();
            break;
        case Callback::AllocateBuffer:
            static_cast<Server *>(context)->AllocateBuffer();
            break;
        case Callback::EchoRead:
            static_cast<Server *>(context)->EchoRead();
            break;
        case Callback::EchoWrite:
            static_cast<Server *>(context)->EchoWrite();
            break;
    }
}
#pragma clang diagnostic pop