#pragma once

#include "crow.h"

using namespace crow;

class DatasetController {
   
public:
    DatasetController();
    response createDataset(const request& req);
};