#pragma once
#include <string>

using namespace std;

struct Dataset {
public:
    string id;
    string domain;
    string name;
    string createDate;
    string updateDate;

    Dataset(){}

    Dataset(const Dataset& other) {
        this->id = other.id;
        this->domain = other.domain;
        this->name = other.name;
        this->createDate = other.createDate;
        this->updateDate = other.updateDate;
    }
};
