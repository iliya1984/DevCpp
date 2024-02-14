#include "DatasetService.h"

DatasetService::DatasetService()
{
}

DatasetService::DatasetService(Repository repository)
{
    _repository = repository;
}

DatasetDto DatasetService::createDataset(DatasetDto datasetDto)
{
    Dataset dataset;
    dataset.name = datasetDto.name;
    dataset.domain = datasetDto.domain;
    _repository.createDataset(dataset);

    DatasetDto result;
    result.name = "foo";
    return result;
}
