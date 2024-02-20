#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

struct ImagePropertiesDto {
public:
    string domainId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImagePropertiesDto, domainId)