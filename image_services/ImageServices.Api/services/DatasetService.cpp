#include "DatasetService.h"

DatasetService::DatasetService()
{
}

DatasetService::DatasetService(DatasetMapper mapper, Repository repository)
{
    _repository = repository;
    _mapper = mapper;
}

unique_ptr<DatasetDto> DatasetService::createDataset(DatasetDto datasetDto)
{
    Dataset dataset = _mapper.map(datasetDto);
    
    auto result = _repository.createDataset(dataset);

    if (result == nullptr) {
        return nullptr;
    }

    auto resultDto = make_unique<DatasetDto>(_mapper.map(*result));
    return resultDto;
}

unique_ptr<DatasetDto> DatasetService::getDatasetById(string id)
{
    auto result = _repository.getDatasetById(id);
    if (result == nullptr) {
        return nullptr;
    }

    auto resultDto = make_unique<DatasetDto>(_mapper.map(*result));
    return resultDto;
}

void DatasetService::deleteDataset(string id)
{
    _repository.deleteDataset(id);
}