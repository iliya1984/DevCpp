#pragma once
#include "../utils/LoggerFactory.h"
#include "../utils/Logger.h"
#include "../data_access/StorageClient.h"
#include "../dtos/ImagePropertiesDto.h"
#include "../dtos/ImageUploadResultDto.h"
#include <string>

using namespace std;

class ImageService {
private:
    StorageClient _storageClient;
    Logger _logger;

public:
    ImageService();
    ImageService(StorageClient storageClient, LoggerFactory loggerFactory);
    ImageUploadResultDto upload(ImagePropertiesDto properties, string content);
};