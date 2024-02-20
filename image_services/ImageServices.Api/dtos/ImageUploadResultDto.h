#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

struct ImageUploadResultDto {
public:
    string id;
    string path;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImageUploadResultDto, id, path)