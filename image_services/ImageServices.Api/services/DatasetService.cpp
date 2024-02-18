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
    auto result = _repository.createDataset(dataset);

    DatasetDto resultDto;
    resultDto.id = result.id;
    resultDto.name = result.name;
    resultDto.domain = result.domain;

    return resultDto;
}
