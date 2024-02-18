#pragma once
#include "Logger.h"
#include "boost/uuid/uuid.hpp";
#include <boost/uuid/uuid_generators.hpp>
#include "boost/uuid/uuid_io.hpp";

class LoggerFactory {
public:
    Logger* getLogger(string loggerName) {
        try
        {
            auto id = boost::uuids::random_generator()();
            std::stringstream ss;
            ss << id;
            auto logger_ptr = spdlog::daily_logger_mt(loggerName + "_" + ss.str(), "logs/daily.txt", 0, 0);
            auto logger = new Logger(logger_ptr);
            return logger;
        }
        catch (const spdlog::spdlog_ex& logex)
        {
            std::string error(logex.what());
            throw std::runtime_error("Failed to create a logger instance." + error);
        }
        catch (std::exception& e)
        {
            std::string error(e.what());
            throw std::runtime_error("Failed to create a logger instance." + error);
        }
    }
};