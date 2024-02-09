#include "DatasetController.h"
#include "crow.h"
#include <nlohmann/json.hpp>

using namespace crow;
using namespace crow::json;
using namespace std;

struct Dataset {
    string name;
};

DatasetController::DatasetController() {
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Dataset, name)
response DatasetController::createDataset(const request& req)
{
    rvalue x = load(req.body);
    Dataset inputDataset = nlohmann::json::parse(req.body);

    if (!x) {
        return response(status::BAD_REQUEST); // same as crow::response(400)
    }
    nlohmann::json output = inputDataset;
    return response{ output.dump() };
}
