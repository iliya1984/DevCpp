#pragma once
#include <string>

using namespace std;

struct Dataset {
public:
    string id;
    string domain;
    string name;

    Dataset(){}

    Dataset(const Dataset& other) {
        id = other.id;
        name = other.name;
        domain = other.domain;
    }
};
