#include "Repository.h"
#include "../models/Dataset.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <format>
#include <iostream> 
#include "../utils/Utils.h"
#include <list>

using namespace std;

static string DATASET_ENTITY_SCHEMA = "id, name, domain, createDate, updateDate";

Repository::Repository() {}
Repository::Repository(LoggerFactory loggerFactory, DataAccessSettings settings) {
    _logger = loggerFactory.getLogger("Repostory");
    _settings = settings;
}

sql::Connection* Repository::openConnection() {
    sql::Driver* driver;
    driver = get_driver_instance();
    _logger.debug("MySql driver instance was created");

    auto connection = driver->connect(_settings.host, _settings.user, _settings.password);
    connection->setSchema(_settings.schema);

    _logger.debug("MySql database connection was created for the host " + _settings.host + " and schema " + _settings.schema);
    return connection;
}

void Repository::closeConnection(sql::Connection* connection) {
    delete(connection);
    _logger.debug("MySql connection was closed");
}

void Repository::deleteStatement(sql::Statement* statement) {
    delete(statement);
    _logger.debug("MySql statement was deleted");
}

std::list<Dataset> Repository::mapToDatasetList(sql::ResultSet* resultSet) {
    list<Dataset> resultList;
    Dataset result;
    while (resultSet->next()) {
        result.id = resultSet->getString("id");
        result.name = resultSet->getString("name");
        result.domain = resultSet->getString("domain");
        result.createDate = resultSet->getString("createDate");
        result.updateDate = resultSet->getString("updateDate");
        resultList.push_back(result);
    }

    return resultList;
}

unique_ptr<Dataset> Repository::getDatasetById(sql::Connection* connection, string id)
{
    sql::ResultSet* resultDs;

    auto statement = connection->createStatement();
    auto sqlCommand = "SELECT " + DATASET_ENTITY_SCHEMA + " FROM datasets WHERE id = '" + id + "'";
    resultDs = statement->executeQuery(sqlCommand);

    auto resultList = mapToDatasetList(resultDs);

    deleteStatement(statement);

    auto size = resultList.size();
    if (size == 0) {
        return nullptr;
    }

    auto result = make_unique<Dataset>(Dataset(resultList.front()));
    return result;
}

unique_ptr<Dataset> Repository::createDataset(Dataset dataset)
{
    unique_ptr<Dataset> result = nullptr;
    try {
        sql::Connection *connection = openConnection();
        sql::Statement *statement = connection->createStatement();
       
        auto id = Utils::generateUUID();
        auto sqlCommand = "INSERT INTO datasets(" + DATASET_ENTITY_SCHEMA + ") values ('" + id + "','" + dataset.name + "', '" + dataset.domain + "', UTC_TIMESTAMP(), UTC_TIMESTAMP())";
        statement->execute(sqlCommand);
        
        _logger.info("Dataset " + dataset.name + " was stored");
        deleteStatement(statement);

        result = getDatasetById(connection, id);

        closeConnection(connection);
    }
    catch (std::exception& e){
        _logger.error(e);
        throw e;
    }
    return result;
}

void Repository::deleteDataset(string id) {
    Dataset result;
    try {
        sql::Connection* connection = openConnection();
        sql::Statement* statement = connection->createStatement();

        auto sqlCommand = "DELETE FROM datasets WHERE id = '" + id + "'";
        statement->execute(sqlCommand);

        _logger.info("Dataset with id " + id + " was deleted");

        deleteStatement(statement);
        closeConnection(connection);
    }
    catch (std::exception& e) {
        _logger.error(e);
        throw e;
    }
}

unique_ptr<Dataset> Repository::getDatasetById(string id)
{
    unique_ptr<Dataset> result = nullptr;
    try {
        sql::Connection* connection = openConnection();
        result = getDatasetById(connection, id);
        closeConnection(connection);
    }
    catch (std::exception& e) {
        _logger.error(e);
        throw e;
    }
    return result;
}
