#include "StorageClient.h"
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

StorageClient::StorageClient()
{
}

StorageClient::StorageClient(LoggerFactory loggerFactory)
{
    _logger = loggerFactory.getLogger("StorageClient");
}

void StorageClient::upload(ImageMetadata metadata, string imageContent)
{
    string storagePath = "../../../Storage";
    string domainFolderPath = storagePath + "/" + metadata.domain;
    string datasetFolderPath = domainFolderPath + "/" + metadata.datasetId;

    path domainDirectory(domainFolderPath);
    create_directory(domainDirectory);

    path datasetDirectory(datasetFolderPath);
    create_directory(datasetDirectory);

    string imageFileName = datasetFolderPath + "/" + metadata.name + "." + metadata.extension;
    std::ofstream out_file(imageFileName, std::ios::out | std::ios::binary);
    if (!out_file)
    {
        _logger.error(" Write to file failed\n");
    }
    out_file << imageContent;
    out_file.close();
    _logger.info(" Contents written to " + imageFileName + '\n');
}
