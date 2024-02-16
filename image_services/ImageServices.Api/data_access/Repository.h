#pragma once
#include "../models/Dataset.h"
#include "../models/configuration/DataAccessSettings.h"
#include "../utils/Logger.h"
#include "mysql_connection.h"

class Repository {
private:
    DataAccessSettings _settings;
    Logger _logger;

    sql::Connection* openConnection();
    void deleteStatement(sql::Statement* statement);
    void closeConnection(sql::Connection* connection);

public:
    Repository();
    Repository(Logger logger, DataAccessSettings settings);
    Dataset createDataset(Dataset dataset);
};