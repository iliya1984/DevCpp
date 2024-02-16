#include "Logger.h"
#include <string>
#include "spdlog/spdlog.h"

using namespace std;

Logger::Logger() {}
Logger::Logger(logger_ptr logger_ptr) {
    _logger = logger_ptr;

    _logger->set_level(spdlog::level::debug);
    spdlog::flush_every(std::chrono::seconds(5));
}

void Logger::info(string message){
    _logger->info(message);
}

void Logger::debug(string message) {
    _logger->debug(message);
}

void Logger::error(exception& e) {
    _logger->error(e.what());
}

void Logger::error(string error) {
    _logger->error(error);
}