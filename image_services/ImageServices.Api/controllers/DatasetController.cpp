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

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DatasetDto, id, name, domain)
response DatasetController::createDataset(const request& req)
{
    rvalue inputValue = load(req.body);
    DatasetDto input = nlohmann::json::parse(req.body);

    if (!inputValue) {
        return response(status::BAD_REQUEST); // same as crow::response(400)
    }

    DatasetDto createdDataset = _datasetService.createDataset(input);

    nlohmann::json output = createdDataset;
    return response{ output.dump() };
}
