#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

struct DataAccessSettings {
public:
    string host;
    string user;
    string password;
    string schema;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DataAccessSettings, host, user, password, schema)
