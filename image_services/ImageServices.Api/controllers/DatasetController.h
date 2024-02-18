#pragma once

#include "crow.h"
#include "../services/DatasetService.h";

using namespace crow;

class DatasetController {
private:
    DatasetService _datasetService;
public:
    DatasetController();
    DatasetController(DatasetService datasetService);
    response createDataset(const request& req);
    response getDatasetById(string id);
};