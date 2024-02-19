#pragma once
#include "Logger.h"
#include "Utils.h"


class LoggerFactory {
public:
    Logger getLogger(string loggerName) {
        try
        {
            auto loggerId = Utils::generateUUID();
            auto logger_ptr = spdlog::daily_logger_mt(loggerName + "_" + loggerId, "logs/daily.txt", 0, 0);
            return Logger(logger_ptr);
        }
        catch (std::exception& e)
        {
            std::string error(e.what());
            throw std::runtime_error("Failed to create a logger instance." + error);
        }
    }
};