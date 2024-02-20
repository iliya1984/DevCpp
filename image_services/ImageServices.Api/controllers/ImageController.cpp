#include "ImageController.h"
#include "../dtos/ImagePropertiesDto.h"
#include "crow/multipart.h"

ImageController::ImageController(ImageService service, LoggerFactory loggerFactory)
{
    _service = service;
    _logger = loggerFactory.getLogger("ImageController");
}

void ImageController::logHeaders(mph_map headers) {
    for (const auto& part_header : headers)
    {
        const auto& part_header_name = part_header.first;
        const auto& part_header_val = part_header.second;
        _logger.debug("Header: " + part_header_name + "=" + part_header_val.value);

        for (const auto& param : part_header_val.params)
        {
            const auto& param_key = param.first;
            const auto& param_val = param.second;
            _logger.debug(" Param: " + param_key + ',' + param_val);
        }
    }
}

response ImageController::upload(const request& req)
{
    string imageContent;
    ImagePropertiesDto imageProperties;

    crow::multipart::message file_message(req);
    for (const auto& part : file_message.part_map)
    {
        const auto& part_name = part.first;
        const auto& part_value = part.second;
        _logger.debug("Part: " + part_name);

        // Extract the file name
        auto contentDisposition = part_value.headers.find("Content-Disposition");
        if (contentDisposition == part_value.headers.end()) {
            _logger.error("No Content-Disposition found");
            return crow::response(400);
        }

        logHeaders(part_value.headers);

        if ("file" == part_name) {
            imageContent = part_value.body;
        }
        else if ("fileProperties" == part_name) {
            imageProperties = nlohmann::json::parse(part_value.body);
        }
    }

    auto uploadResult = _service.upload(imageProperties, imageContent);

    nlohmann::json output = uploadResult;
    return response{ output.dump() };
}
