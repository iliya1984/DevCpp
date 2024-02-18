#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

struct DatasetDto {
public:
    string id;
    string domain;
    string name;
    string createDate;
    string updateDate;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DatasetDto, id, name, domain, createDate, updateDate)
