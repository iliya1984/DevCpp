#pragma once
#include "../dtos/DatasetDto.h"
#include "../data_access/Repository.h"
#include "../mappers/DatasetMapper.h"

using namespace std;

class DatasetService {
private:
    Repository _repository;
    DatasetMapper _mapper;

public:
    DatasetService();
    DatasetService(DatasetMapper mapper, Repository repository);
    unique_ptr<DatasetDto> createDataset(DatasetDto datasetDto);
    unique_ptr<DatasetDto> getDatasetById(string id);
    void deleteDataset(string id);
};