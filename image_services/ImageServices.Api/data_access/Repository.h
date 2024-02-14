#pragma once
#include "../models/Dataset.h"
#include "../models/configuration/DataAccessSettings.h"

class Repository {
private:
    DataAccessSettings _settings;

public:
    Repository();
    Repository(DataAccessSettings settings);
    Dataset createDataset(Dataset dataset);
};