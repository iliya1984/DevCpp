#include "pch.h"
#include "HttpClients.h"

DatasetClient::DatasetClient()
{
}

DatasetDto DatasetClient::createDataset(DatasetDto dataset)
{
    tcp::socket socket = socketManager.createAndConnectSocket(io_context);

    // Create the HTTP request
    http::request<http::string_body> req(http::verb::post, "/datasets", 11);
    req.set(http::field::host, "localhost");
    req.set(http::field::user_agent, "Boost Beast HTTP Client");
    req.set(http::field::content_type, "application/json");

    // Set the request body if needed
    string body = JsonSerializer<DatasetDto>::serialize(dataset);
    req.body() = body;
    req.prepare_payload();

    // Send the HTTP request
    http::write(socket, req);

    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Receive the HTTP response
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);

    auto resultCode = res.result_int();
    string response = beast::buffers_to_string(res.body().data());
    DatasetDto resultDataset = JsonSerializer<DatasetDto>::deserialize(response);

    socketManager.closeSocket(socket);

    return resultDataset;
}

void DatasetClient::deleteDataset(string datasetId)
{
    tcp::socket socket = socketManager.createAndConnectSocket(io_context);

    // Create the HTTP request
    http::request<http::string_body> req(http::verb::delete_, "/datasets/" + datasetId, 11);
    req.set(http::field::host, "localhost");
    req.set(http::field::content_type, "application/json");

    http::write(socket, req);

    socketManager.closeSocket(socket);
}

DatasetDto DatasetClient::getDatasetById(string datasetId) {
    tcp::socket socket = socketManager.createAndConnectSocket(io_context);

    http::request<http::string_body> req(http::verb::get, "/datasets/" + datasetId, 11);
    req.set(http::field::host, "localhost");
    req.set(http::field::content_type, "application/json");

    http::write(socket, req);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);

    auto resultCode = res.result_int();
    string response = beast::buffers_to_string(res.body().data());
    DatasetDto resultDataset = JsonSerializer<DatasetDto>::deserialize(response);

    socketManager.closeSocket(socket);

    return resultDataset;
}
