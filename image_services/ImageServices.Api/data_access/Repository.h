#pragma once
#include "../models/Dataset.h"
#include "../models/configuration/DataAccessSettings.h"
#include "../utils/LoggerFactory.h"
#include "mysql_connection.h"
#include <cppconn/resultset.h>
#include "boost/uuid/uuid.hpp";
#include <list>

class Repository {
private:
    DataAccessSettings _settings;
    Logger* _logger;

    sql::Connection* openConnection();
    void deleteStatement(sql::Statement* statement);
    void closeConnection(sql::Connection* connection);
    string generateUUID();
    Dataset getDatasetById(sql::Connection* connection, string id);
    std::list<Dataset> mapToDatasetList(sql::ResultSet* resultSet);
public:
    Repository();
    Repository(LoggerFactory loggerFactory, DataAccessSettings settings);
    ~Repository();
    Dataset createDataset(Dataset dataset);
    Dataset getDatasetById(string id);
};