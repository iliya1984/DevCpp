#include <iostream>
#include "crow.h"
#include "crow/multipart.h"
#include "controllers/DatasetController.h"
#include "controllers/ImageController.h"
#include "dtos/DatasetDto.h"
#include "services/DatasetService.h"
#include "services/ImageService.h"
#include "data_access/Repository.h"
#include "data_access/StorageClient.h"
#include "di.hpp"
#include <nlohmann/json.hpp>
#include "models/configuration/DataAccessSettings.h"
#include "utils/ConfigurationManager.h"
#include "utils/LoggerFactory.h"
#include "mappers/DatasetMapper.h";

namespace di = boost::di;

using namespace crow;
using namespace crow::json;
using namespace std;


int main()
{
    
    auto configurationManager = new ConfigurationManager("app-settings.json");
    DataAccessSettings dataAccessSettings = configurationManager->getSection("dataAccess");
    
    SimpleApp app;

    const auto injector = di::make_injector(
        di::bind<DataAccessSettings>().to(dataAccessSettings),
        di::bind<LoggerFactory>().to<LoggerFactory>(),
        di::bind<Repository>().to<Repository>(),
        di::bind<StorageClient>().to<StorageClient>(),
        di::bind<DatasetMapper>().to<DatasetMapper>(),
        di::bind<ImageService>().to<ImageService>(),
        di::bind<DatasetService>().to<DatasetService>(),
        di::bind<ImageController>().to<ImageController>(),
        di::bind<DatasetController>().to<DatasetController>()
    );

    CROW_ROUTE(app, "/datasets")
        .methods("POST"_method)
        ([&](const request& req) {
            auto controller = injector.create<DatasetController>();
            return controller.createDataset(req);
        });

    CROW_ROUTE(app, "/datasets/<string>")
        ([&](string id) {
            auto controller = injector.create<DatasetController>();
            return controller.getDatasetById(id);
        });

    CROW_ROUTE(app, "/datasets/<string>")
        .methods("DELETE"_method)
        ([&](string id) {
            auto controller = injector.create<DatasetController>();
            return controller.deleteDataset(id);
        });

    CROW_ROUTE(app, "/images")
        .methods(crow::HTTPMethod::Post)([&](const crow::request& req) {
            auto controller = injector.create<ImageController>();
            return controller.upload(req);
        });

    app.port(18080).multithreaded().run();
}
