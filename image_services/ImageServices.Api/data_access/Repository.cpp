#include "Repository.h"
#include "../models/Dataset.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <format>
#include <iostream> 

using namespace std;

Repository::Repository() {}
Repository::Repository(DataAccessSettings settings) {
    _settings = settings;
}

sql::Connection* Repository::openConnection() {
    sql::Driver* driver;

    /* Create a connection */
    driver = get_driver_instance();
    /* Connect to the MySQL test database */
    auto connection = driver->connect(_settings.host, _settings.user, _settings.password);

    connection->setSchema(_settings.schema);
    return connection;
}

void Repository::closeConnection(sql::Connection* connection) {
    delete(connection);
}

void Repository::logSQLException(sql::SQLException& e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line "
        << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

Dataset Repository::createDataset(Dataset dataset)
{
    try {
        
        sql::Connection* connection = openConnection();
        sql::Statement* statement = connection->createStatement();

        auto sqlCommand = "INSERT INTO datasets(name, domain) values ('" + dataset.name + "', '" + dataset.domain + "')";
        bool inserted = statement->execute(sqlCommand);

        delete statement;
        closeConnection(connection);

    }
    catch (sql::SQLException& e) {
        logSQLException(e);
        throw e;
    }
    return Dataset();
}
