#pragma once
#include "../models/Dataset.h"
#include "../models/configuration/DataAccessSettings.h"
#include "mysql_connection.h"

class Repository {
private:
    DataAccessSettings _settings;

    sql::Connection* openConnection();
    void closeConnection(sql::Connection* connection);
    void logSQLException(sql::SQLException& e);

public:
    Repository();
    Repository(DataAccessSettings settings);
    Dataset createDataset(Dataset dataset);
};