#pragma once
#include "crow.h"
#include "../utils/LoggerFactory.h"
#include "../utils/Logger.h"
#include "../services/ImageService.h"

using namespace crow;
using namespace crow::multipart;

class ImageController {
private:
    Logger _logger;
    ImageService _service;

    void logHeaders(mph_map headers);
public:
    ImageController() {}
    ImageController(ImageService service, LoggerFactory loggerFactory);
    response upload(const request& req);
};