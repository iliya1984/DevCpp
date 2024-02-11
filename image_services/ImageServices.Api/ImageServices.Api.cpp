#include <iostream>
#include "crow.h"
#include "controllers/DatasetController.h"
#include "dtos/DatasetDto.h"
#include "services/DatasetService.h";
#include "di.hpp"

namespace di = boost::di;

using namespace crow;
using namespace crow::json;
using namespace std;

int main()
{
    SimpleApp app;

    const auto injector = di::make_injector(
        di::bind<DatasetService>().to<DatasetService>(),
        di::bind<DatasetController>().to<DatasetController>()
    );

    CROW_ROUTE(app, "/datasets")
        .methods("POST"_method)
        ([&](const request& req) {
            auto controller = injector.create<DatasetController>();
            return controller.createDataset(req);
        });

    app.port(18080).multithreaded().run();
}
