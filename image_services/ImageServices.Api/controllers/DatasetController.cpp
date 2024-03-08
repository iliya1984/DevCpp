#include "DatasetController.h"
#include "crow.h"
#include <nlohmann/json.hpp>
#include "../dtos/DatasetDto.h"
#include "../services/DatasetService.h";

using namespace crow;
using namespace crow::json;
using namespace std;

DatasetController::DatasetController() { }

DatasetController::DatasetController(DatasetService datasetService) {
    _datasetService = datasetService;
}

response DatasetController::createDataset(const request& req)
{
    rvalue inputValue = load(req.body);
    DatasetDto input = nlohmann::json::parse(req.body);

    if (!inputValue) {
        return response(status::BAD_REQUEST);
    }

    auto createdDataset = _datasetService.createDataset(input);
    if (createdDataset == nullptr) {
        auto errorResponse = response();
        errorResponse.code = 500;
        errorResponse.body = "Dataset creation failed";
        return errorResponse;
    }


    nlohmann::json output = *createdDataset;
    return response{ output.dump() };
}

response DatasetController::getDatasetById(string id) {
    auto dataset = _datasetService.getDatasetById(id);
    if (dataset == nullptr) {
        auto notFound = response();
        notFound.code = 404;
        return notFound;
    }
    
    nlohmann::json output = *dataset;
    return response{ output.dump() };
}

response DatasetController::deleteDataset(string id)
{
    _datasetService.deleteDataset(id);
    return response { };
}
