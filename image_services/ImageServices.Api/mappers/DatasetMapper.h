#pragma once
#include "../dtos/DatasetDto.h"
#include "../models/Dataset.h"

class DatasetMapper {
public:
    DatasetDto map(Dataset dataset) {
        DatasetDto datasetDto;
        datasetDto.id = dataset.id.c_str();
        datasetDto.name = dataset.name.c_str();
        datasetDto.domain = dataset.domain.c_str();
        datasetDto.createDate = dataset.createDate.c_str();
        datasetDto.updateDate = dataset.updateDate.c_str();

        return datasetDto;
    }

    Dataset map(DatasetDto datasetDto) {
        Dataset dataset;
        dataset.id = datasetDto.id.c_str();
        dataset.name = datasetDto.name.c_str();
        dataset.domain = datasetDto.domain.c_str();
        dataset.createDate = datasetDto.createDate.c_str();
        dataset.updateDate = datasetDto.updateDate.c_str();
        return dataset;
    }
};
