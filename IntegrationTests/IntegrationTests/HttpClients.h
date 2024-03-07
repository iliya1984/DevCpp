#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include "Utils.h"
#include "Dtos.h"
#include <nlohmann/json.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class DatasetClient {
public:
	net::io_context io_context;
	WebSocketManager socketManager;

	DatasetClient();

	DatasetDto createDataset(DatasetDto dataset);
	DatasetDto getDatasetById(string datasetId);
	void deleteDataset(string datasetId);
};