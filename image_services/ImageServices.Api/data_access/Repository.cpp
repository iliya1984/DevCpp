#include "Repository.h"
#include "../models/Dataset.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <format>
#include <iostream> 
#include "boost/uuid/uuid.hpp";
#include <boost/uuid/uuid_generators.hpp>
#include "boost/uuid/uuid_io.hpp";

using namespace std;

Repository::Repository() {}
Repository::Repository(Logger logger, DataAccessSettings settings) {
    _logger = logger;
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

string Repository::generateUUID() {
    auto id = boost::uuids::random_generator()();
    std::stringstream ss;
    ss << id;
    return ss.str();
}

Dataset Repository::createDataset(Dataset dataset)
{
    try {
        
        sql::Connection* connection = openConnection();
        sql::Statement* statement = connection->createStatement();
       
        auto id = generateUUID();
        auto sqlCommand = "INSERT INTO datasets(id, name, domain) values ('" + id + "','" + dataset.name + "', '" + dataset.domain + "')";
        statement->execute(sqlCommand);
        
        _logger.info("Dataset " + dataset.name + " was stored");

        deleteStatement(statement);
        closeConnection(connection);

    }
    catch (sql::SQLException& e) {
        _logger.error(e);
        throw e;
    }
    return Dataset();
}
