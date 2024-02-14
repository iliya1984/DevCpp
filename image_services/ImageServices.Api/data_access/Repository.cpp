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

Dataset Repository::createDataset(Dataset dataset)
{
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        /* Create a connection */
        driver = get_driver_instance();
        /* Connect to the MySQL test database */
        con = driver->connect(_settings.host, _settings.user, _settings.password);
        con->setSchema(_settings.schema);

        stmt = con->createStatement();

        auto sqlCommand = "INSERT INTO datasets(name, domain) values ('" + dataset.name + "', '" + dataset.domain + "')";
        bool inserted = stmt->execute(sqlCommand);

        delete stmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
            << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return Dataset();
}
