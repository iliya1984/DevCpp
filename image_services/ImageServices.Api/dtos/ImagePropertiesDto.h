#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

struct ImagePropertiesDto {
public:
    string datasetId;
    string fileName;
    string domain;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImagePropertiesDto, datasetId, fileName, domain)