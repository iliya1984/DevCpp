#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

class ConfigurationManager {
private:
    nlohmann::json _config;

public:
    ConfigurationManager(string configFileName);
    nlohmann::json getSection(string sectionName);
};