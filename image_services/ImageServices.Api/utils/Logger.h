#pragma once
#include <string>
#include "spdlog/sinks/daily_file_sink.h"

using namespace std;
using logger_ptr = std::shared_ptr<spdlog::logger>;

class Logger {
private:
    logger_ptr _logger;

public:
    Logger();
    Logger(logger_ptr logger_ptr);
    ~Logger();
    void info(string message);
    void debug(string message);
    void error(exception& e);
    void error(string error);
};