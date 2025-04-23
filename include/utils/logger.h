/**
 * LuminaChain Wallet - Logger Utility
 * 
 * This file defines the Logger class which provides logging functionality
 * for the LuminaChain wallet application.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#ifndef LUMINA_LOGGER_H
#define LUMINA_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>

namespace lumina {

/**
 * Log levels for different types of messages
 */
enum class LogLevel {
    DEBUG,    // Debug information (development only)
    INFO,     // General information
    WARNING,  // Warning messages
    ERROR,    // Error messages
    CRITICAL  // Critical errors
};

/**
 * Provides logging functionality for the application
 */
class Logger {
public:
    /**
     * Gets the singleton instance of the logger
     * 
     * @return The logger instance
     */
    static Logger& getInstance();
    
    /**
     * Initializes the logger
     * 
     * @param logFilePath Path to the log file
     * @param consoleOutput Whether to output logs to console
     * @return true if initialization was successful
     */
    bool initialize(const std::string& logFilePath, bool consoleOutput = true);
    
    /**
     * Logs a message with the specified log level
     * 
     * @param level The log level
     * @param message The message to log
     */
    void log(LogLevel level, const std::string& message);
    
    /**
     * Logs a debug message
     * 
     * @param message The message to log
     */
    void debug(const std::string& message);
    
    /**
     * Logs an info message
     * 
     * @param message The message to log
     */
    void info(const std::string& message);
    
    /**
     * Logs a warning message
     * 
     * @param message The message to log
     */
    void warning(const std::string& message);
    
    /**
     * Logs an error message
     * 
     * @param message The message to log
     */
    void error(const std::string& message);
    
    /**
     * Logs a critical error message
     * 
     * @param message The message to log
     */
    void critical(const std::string& message);
    
    /**
     * Sets the minimum log level to output
     * 
     * @param level The minimum log level
     */
    void setLogLevel(LogLevel level);
    
    /**
     * Gets the current minimum log level
     * 
     * @return The current minimum log level
     */
    LogLevel getLogLevel() const;
    
    /**
     * Enables or disables console output
     * 
     * @param enabled Whether console output should be enabled
     */
    void setConsoleOutput(bool enabled);

private:
    // Private constructor for singleton pattern
    Logger();
    
    // Prevent copying and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    // Logger data
    std::string m_logFilePath;
    std::ofstream m_logFile;
    bool m_consoleOutput;
    LogLevel m_logLevel;
    std::mutex m_mutex;
    
    // Internal methods
    std::string getTimestamp() const;
    std::string logLevelToString(LogLevel level) const;
};

} // namespace lumina

#endif // LUMINA_LOGGER_H