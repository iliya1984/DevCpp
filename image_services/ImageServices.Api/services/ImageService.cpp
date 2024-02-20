#include "ImageService.h"
#include "../models/ImageMetadata.h"

ImageService::ImageService()
{
}

ImageService::ImageService(StorageClient storageClient, LoggerFactory loggerFactory)
{
    _storageClient = storageClient;
    _logger = loggerFactory.getLogger("ImageService");
}

ImageUploadResultDto ImageService::upload(string fileName, ImagePropertiesDto properties, string content)
{
    ImageMetadata metadata;
    metadata.domainId = properties.domainId;

    auto splitIndex = fileName.find(".");
    metadata.name = fileName.substr(0, splitIndex);
    metadata.extension = fileName.substr(splitIndex + 1, fileName.length() - splitIndex);

    _storageClient.upload(metadata, content);

    return ImageUploadResultDto();
}
