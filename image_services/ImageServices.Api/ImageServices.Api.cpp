#include <iostream>
#include "crow.h"
#include "DatasetController.h"
#include "di.hpp"

namespace di = boost::di;

using namespace crow;
using namespace crow::json;
using namespace std;
//using json = nlohmann::json;

int main()
{
    SimpleApp app;

    const auto injector = di::make_injector(
        di::bind<DatasetController>().to<DatasetController>()
    );

    CROW_ROUTE(app, "/my-test")([]() {
        return "Hello world";
        });
    
    CROW_ROUTE(app, "/datasets")
        .methods("POST"_method)
        ([&](const request& req) {
        auto controller = injector.create<DatasetController>();
            return controller.createDataset(req);
        });

    app.port(18080).multithreaded().run();
}
