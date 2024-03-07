#pragma once
#include "pch.h"
#include "Utils.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

tcp::socket WebSocketManager::createAndConnectSocket(net::io_context& ioContext) {
    // Resolve the hostname and port number
    tcp::resolver resolver(ioContext);
    auto const results = resolver.resolve("localhost", "18080");

    // Make the connection
    tcp::socket socket(ioContext);
    net::connect(socket, results.begin(), results.end());

    return socket;
}

void WebSocketManager::closeSocket(tcp::socket& socket) {
    // Close the socket
    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);
    if (ec && ec != beast::errc::not_connected)
        throw beast::system_error{ ec };
}
