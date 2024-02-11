#pragma once

#include "crow.h"
#include "../services/DatasetService.h";

using namespace crow;

class DatasetController {
private:
    DatasetService _datasetService;
public:
    DatasetController(DatasetService datasetService);
    response createDataset(const request& req);
};