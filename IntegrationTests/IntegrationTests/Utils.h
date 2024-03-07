#pragma once
#include "pch.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class WebSocketManager {
public:
	tcp::socket createAndConnectSocket(net::io_context& ioContext);
	void closeSocket(tcp::socket& socket);
};

template<typename T>
class JsonSerializer {
public:
    static string serialize(const T& obj) {
        nlohmann::json datasetJson = obj;
        return datasetJson.dump();
    }

    static T deserialize(const string& jsonString) {
        return nlohmann::json::parse(jsonString).get<T>();
    }
};