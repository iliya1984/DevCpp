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

    DatasetDto createdDataset = _datasetService.createDataset(input);

    nlohmann::json output = createdDataset;
    return response{ output.dump() };
}

response DatasetController::getDatasetById(string id) {
    DatasetDto createdDataset = _datasetService.getDatasetById(id);
    nlohmann::json output = createdDataset;
    return response{ output.dump() };
}

response DatasetController::deleteDataset(string id)
{
    _datasetService.deleteDataset(id);
    return response { };
}
