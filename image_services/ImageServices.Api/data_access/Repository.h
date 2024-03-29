#pragma once
#include "../models/Dataset.h"
#include "../models/configuration/DataAccessSettings.h"
#include "../utils/LoggerFactory.h"
#include "mysql_connection.h"
#include <cppconn/resultset.h>
#include "boost/uuid/uuid.hpp";
#include <list>

using namespace std;

class Repository {
private:
    DataAccessSettings _settings;
    Logger _logger;

    sql::Connection* openConnection();
    void deleteStatement(sql::Statement* statement);
    void closeConnection(sql::Connection* connection);
    unique_ptr<Dataset> getDatasetById(sql::Connection* connection, string id);
    list<Dataset> mapToDatasetList(sql::ResultSet* resultSet);
public:
    Repository();
    Repository(LoggerFactory loggerFactory, DataAccessSettings settings);
    unique_ptr<Dataset> createDataset(Dataset dataset);
    unique_ptr<Dataset> getDatasetById(string id);
    void deleteDataset(string id);
};