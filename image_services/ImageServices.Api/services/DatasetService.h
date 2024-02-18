#pragma once
#include "../dtos/DatasetDto.h"
#include "../data_access/Repository.h"
#include "../mappers/DatasetMapper.h"

class DatasetService {
private:
    Repository _repository;
    DatasetMapper _mapper;

public:
    DatasetService();
    DatasetService(DatasetMapper mapper, Repository repository);
    DatasetDto createDataset(DatasetDto datasetDto);
    DatasetDto getDatasetById(string id);
};