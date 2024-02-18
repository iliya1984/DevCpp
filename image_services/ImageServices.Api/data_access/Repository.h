#pragma once
#include "../models/Dataset.h"
#include "../models/configuration/DataAccessSettings.h"
#include "../utils/Logger.h"
#include "mysql_connection.h"
#include "boost/uuid/uuid.hpp";

class Repository {
private:
    DataAccessSettings _settings;
    Logger _logger;

    sql::Connection* openConnection();
    void deleteStatement(sql::Statement* statement);
    void closeConnection(sql::Connection* connection);
    string generateUUID();
    Dataset getDatasetById(sql::Connection* connection, string id);

public:
    Repository();
    Repository(Logger logger, DataAccessSettings settings);
    Dataset createDataset(Dataset dataset);
};