#include "DatasetService.h"

DatasetService::DatasetService()
{
}

DatasetService::DatasetService(DatasetMapper mapper, Repository repository)
{
    _repository = repository;
    _mapper = mapper;
}

DatasetDto DatasetService::createDataset(DatasetDto datasetDto)
{
    Dataset dataset = _mapper.map(datasetDto);
    
    auto result = _repository.createDataset(dataset);

    DatasetDto resultDto = _mapper.map(result);
    return resultDto;
}

DatasetDto DatasetService::getDatasetById(string id)
{
    auto result = _repository.getDatasetById(id);

    DatasetDto resultDto = _mapper.map(result);
    return resultDto;
}

void DatasetService::deleteDataset(string id)
{
    _repository.deleteDataset(id);
}