#include "pch.h"
#include "CppUnitTest.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include "Utils.h"
#include "HttpClients.h"
#include "Dtos.h"
#include <nlohmann/json.hpp>

namespace beast = boost::beast;      // from <boost/beast.hpp>
namespace http = beast::http;         // from <boost/beast/http.hpp>
namespace net = boost::asio;          // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTests
{
	TEST_CLASS(DatasetTests)
	{
    private:
       DatasetDto createDatasetDto(){
            DatasetDto dataset;
            dataset.id = "";
            dataset.name = "test22";
            dataset.domain = "test_domain";
            dataset.createDate = "";
            dataset.updateDate = "";

            return dataset;
        }

	public:

		TEST_METHOD(DatasetCreationSuccess)
		{
			//Create dataset client and dataset dto
            DatasetClient client;
            DatasetDto expectedDataset = createDatasetDto();

            //Send create dataset request
            DatasetDto actualDataset = client.createDataset(expectedDataset);
            string datasetId = actualDataset.id;

            //Assert created dataset
            Assert::AreEqual(actualDataset.name, expectedDataset.name);
            Assert::AreEqual(actualDataset.domain, expectedDataset.domain);
            Assert::IsFalse(actualDataset.id.empty());
            Assert::IsFalse(actualDataset.createDate.empty());
            Assert::IsFalse(actualDataset.updateDate.empty());

            //client.deleteDataset(datasetId);
            //client.getDatasetById(datasetId);
        }
	};
}
