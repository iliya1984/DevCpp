#include "ConfigurationManager.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace nlohmann;

ConfigurationManager::ConfigurationManager(string configFileName) {
    ifstream configFile(configFileName.c_str());
    if (!configFile.is_open()) {
        throw new exception("Failed to open config file");
    }

    std::string configData;
    std::string line;
    while (std::getline(configFile, line)) {
        configData += line;
    }

    _config = nlohmann::json::parse(configData);
}

json ConfigurationManager::getSection(string sectionName) {
    return _config[sectionName];
}


