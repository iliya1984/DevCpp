#pragma once
#include "../utils/LoggerFactory.h"
#include "../utils/Logger.h"
#include "../models/ImageMetadata.h"
#include <string>

using namespace std;
class StorageClient {
private:
    Logger _logger;
public:
    StorageClient();
    StorageClient(LoggerFactory loggerFactory);
    void upload(ImageMetadata metadata, string imageContent);
};