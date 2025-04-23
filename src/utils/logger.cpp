/**
 * LuminaChain Wallet - Logger Utility Implementation
 * 
 * This file implements the Logger class which provides logging functionality
 * for the LuminaChain wallet application.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#include "utils/logger.h"
#include <ctime>
#include <iomanip>
#include <sstream>

namespace lumina {

/**
 * Constructor
 */
Logger::Logger()
    : m_logFilePath(""),
      m_consoleOutput(true),
      m_logLevel(LogLevel::INFO) {
}

/**
 * Gets the singleton instance of the logger
 */
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

/**
 * Initializes the logger
 */
bool Logger::initialize(const std::string& logFilePath, bool consoleOutput) {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    m_logFilePath = logFilePath;
    m_consoleOutput = consoleOutput;
    
    // Open the log file
    if (!m_logFilePath.empty()) {
        m_logFile.open(m_logFilePath, std::ios::app);
        if (!m_logFile) {
            // If we can't open the log file, fall back to console output
            m_consoleOutput = true;
            return false;
        }
    }
    
    // Log initialization message
    log(LogLevel::INFO, "Logger initialized");
    
    return true;
}

/**
 * Logs a message with the specified log level
 */
void Logger::log(LogLevel level, const std::string& message) {
    // Skip if the message level is below the current log level
    if (level < m_logLevel) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(m_mutex);
    
    // Format the log message
    std::string timestamp = getTimestamp();
    std::string levelStr = logLevelToString(level);
    std::string formattedMessage = timestamp + " [" + levelStr + "] " + message;
    
    // Write to console if enabled
    if (m_consoleOutput) {
        std::cout << formattedMessage << std::endl;
    }
    
    // Write to log file if open
    if (m_logFile.is_open()) {
        m_logFile << formattedMessage << std::endl;
        m_logFile.flush();
    }
}

/**
 * Logs a debug message
 */
void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

/**
 * Logs an info message
 */
void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

/**
 * Logs a warning message
 */
void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

/**
 * Logs an error message
 */
void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

/**
 * Logs a critical error message
 */
void Logger::critical(const std::string& message) {
    log(LogLevel::CRITICAL, message);
}

/**
 * Sets the minimum log level to output
 */
void Logger::setLogLevel(LogLevel level) {
    m_logLevel = level;
}

/**
 * Gets the current minimum log level
 */
LogLevel Logger::getLogLevel() const {
    return m_logLevel;
}

/**
 * Enables or disables console output
 */
void Logger::setConsoleOutput(bool enabled) {
    m_consoleOutput = enabled;
}

/**
 * Gets a timestamp string for the current time
 */
std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    
    return ss.str();
}

/**
 * Converts a log level to a string representation
 */
std::string Logger::logLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
    }
}

} // namespace lumina