#include <iostream>
#include <format>
#include "core/server.h"

Author::Core::Server::Server() {
    loop = uv_default_loop();
    uv_tcp_init(loop, &server);
    uv_ip4_addr("0.0.0.0", 5770, &addr);
    uv_tcp_bind(&server, (const struct sockaddr *) &addr, 0);
}

int Author::Core::Server::Listen()
{
    return uv_listen((uv_stream_t*)&server, backlog, /* ConnectionHandler --> */ nullptr);
}

int Author::Core::Server::Start()
{

    int rc = uv_run(loop, UV_RUN_DEFAULT);
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

/// libuv main function for tcp server
//
//uv_loop_t* loop;
//sockaddr_in addr;
//uv_tcp_t server;
//
//loop = uv_default_loop();
//uv_tcp_init(loop, &server);
//uv_ip4_addr("0.0.0.0", 5770, &addr);
//uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
//
//int listen_err = uv_listen((uv_stream_t*)&server, <int> backlog_value, <(callable)>);
//if (listen_err)
//{
/// Listen socket error
//return 1;
//}
//
/// loop, mode
//int rc = uv_run(loop, UV_RUN_DEFAULT)
//
//return rc;
//
