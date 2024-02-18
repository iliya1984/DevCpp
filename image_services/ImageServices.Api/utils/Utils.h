#pragma once
#include <string>
#include <sstream> 
#include "boost/uuid/uuid.hpp";
#include <boost/uuid/uuid_generators.hpp>
#include "boost/uuid/uuid_io.hpp";

using namespace std;
using namespace boost::uuids;

class Utils {
public:
    static string generateUUID(){
        auto id = random_generator()();
        stringstream ss;
        ss << id;
        return ss.str();
    }
};