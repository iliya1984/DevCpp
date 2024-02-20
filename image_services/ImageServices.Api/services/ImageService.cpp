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

ImageUploadResultDto ImageService::upload(ImagePropertiesDto properties, string content)
{
    auto fileName = properties.fileName;

    ImageMetadata metadata;
    metadata.domainId = properties.domain;

    auto splitIndex = fileName.find(".");
    metadata.name = fileName.substr(0, splitIndex);
    metadata.extension = fileName.substr(splitIndex + 1, fileName.length() - splitIndex);

    _storageClient.upload(metadata, content);

    return ImageUploadResultDto();
}
