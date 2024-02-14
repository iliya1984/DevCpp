#pragma once
#include "../dtos/DatasetDto.h"
#include "../data_access/Repository.h"

class DatasetService {
private:
    Repository _repository;

public:
    DatasetService();
    DatasetService(Repository repository);
    DatasetDto createDataset(DatasetDto datasetDto);
};