#include "pch.h"
#include "CppUnitTest.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

namespace beast = boost::beast;      // from <boost/beast.hpp>
namespace http = beast::http;         // from <boost/beast/http.hpp>
namespace net = boost::asio;          // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTests
{
	TEST_CLASS(DatasetTests)
	{
	public:

		TEST_METHOD(DatasetCreationSuccess)
		{
			//Arrange
             // Set up the io_context
            net::io_context io_context;

            // Resolve the hostname and port number
            tcp::resolver resolver(io_context);
            auto const results = resolver.resolve("localhost", "18080");

            // Make the connection
            tcp::socket socket(io_context);
            net::connect(socket, results.begin(), results.end());

            // Create the HTTP request
            http::request<http::string_body> req(http::verb::post, "/datasets", 11);
            req.set(http::field::host, "localhost");
            req.set(http::field::user_agent, "Boost Beast HTTP Client");

            // Set the request body if needed
            req.body() = "{ \"id\": \"\", \"name\" : \"test20\", \"domain\" : \"test_domain\", \"createDate\" : \"\", \"updateDate\" : \"\" }";

            // Send the HTTP request
            http::write(socket, req);

            // This buffer is used for reading and must be persisted
            beast::flat_buffer buffer;

            // Receive the HTTP response
            http::response<http::dynamic_body> res;
            http::read(socket, buffer, res);

            // Print the response status code and message
            std::cout << "Response code: " << res.result_int() << std::endl;
            std::cout << "Response message: " << res.reason() << std::endl;

            // Print the response body
            auto response = beast::buffers_to_string(res.body().data());
            std::cout << "Response body: " << response << std::endl;

            // Close the socket
            beast::error_code ec;
            socket.shutdown(tcp::socket::shutdown_both, ec);
            if (ec && ec != beast::errc::not_connected)
                throw beast::system_error{ ec };
		}
	};
}
