#pragma once
#include "../dtos/DatasetDto.h";

class DatasetService {
public:
    DatasetDto createDataset(DatasetDto datasetDto);
};