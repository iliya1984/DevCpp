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

    //CROW_ROUTE(app, "/images")
    //    .methods(crow::HTTPMethod::Post)([](const crow::request& req) {
    //    crow::multipart::message file_message(req);
    //    for (const auto& part : file_message.part_map)
    //    {
    //        const auto& part_name = part.first;
    //        const auto& part_value = part.second;
    //        CROW_LOG_DEBUG << "Part: " << part_name;
    //       
    //        // Extract the file name
    //        auto headers_it = part_value.headers.find("Content-Disposition");
    //        if (headers_it == part_value.headers.end())
    //        {
    //            CROW_LOG_ERROR << "No Content-Disposition found";
    //            return crow::response(400);
    //        }
    //        auto params_it = headers_it->second.params.find("filename");
    //        if (params_it == headers_it->second.params.end())
    //        {
    //            CROW_LOG_ERROR << "Part with name \"InputFile\" should have a file";
    //            return crow::response(400);
    //        }
    //        const std::string outfile_name = params_it->second;

    //        for (const auto& part_header : part_value.headers)
    //        {
    //            const auto& part_header_name = part_header.first;
    //            const auto& part_header_val = part_header.second;
    //            CROW_LOG_DEBUG << "Header: " << part_header_name << '=' << part_header_val.value;
    //            for (const auto& param : part_header_val.params)
    //            {
    //                const auto& param_key = param.first;
    //                const auto& param_val = param.second;
    //                CROW_LOG_DEBUG << " Param: " << param_key << ',' << param_val;
    //            }
    //        }

    //        // Create a new file with the extracted file name and write file contents to it
    //        std::ofstream out_file(outfile_name, std::ios::out | std::ios::binary);
    //        if (!out_file)
    //        {
    //            CROW_LOG_ERROR << " Write to file failed\n";
    //            continue;
    //        }
    //        out_file << part_value.body;
    //        out_file.close();
    //        CROW_LOG_INFO << " Contents written to " << outfile_name << '\n';
    //    }
    //    return crow::response(200);
    //        });


    app.port(18080).multithreaded().run();
}
