/**
 * LuminaChain Wallet - Configuration Utility Implementation
 * 
 * This file implements the Config class which manages application configuration
 * settings for the LuminaChain wallet.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#include "utils/config.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "utils/logger.h"

namespace lumina {

/**
 * Constructor
 */
Config::Config()
    : m_configFilePath("") {
}

/**
 * Gets the singleton instance of the configuration manager
 */
Config& Config::getInstance() {
    static Config instance;
    return instance;
}

/**
 * Loads configuration from a file
 */
bool Config::loadFromFile(const std::string& configFilePath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    // Open the configuration file
    std::ifstream configFile(configFilePath);
    if (!configFile) {
        Logger::getInstance().warning("Failed to open configuration file: " + configFilePath);
        return false;
    }
    
    // Store the file path for later use
    m_configFilePath = configFilePath;
    
    // Clear existing configuration
    m_configData.clear();
    
    // Read and parse each line
    std::string line;
    int lineNumber = 0;
    while (std::getline(configFile, line)) {
        lineNumber++;
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Parse the line
        std::string key, value;
        if (parseConfigLine(line, key, value)) {
            m_configData[key] = value;
        } else {
            Logger::getInstance().warning("Invalid configuration line " + 
                                          std::to_string(lineNumber) + ": " + line);
        }
    }
    
    Logger::getInstance().info("Loaded configuration from " + configFilePath);
    return true;
}

/**
 * Saves configuration to a file
 */
bool Config::saveToFile(const std::string& configFilePath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    // Use the provided file path or the one from loading
    std::string filePath = configFilePath.empty() ? m_configFilePath : configFilePath;
    if (filePath.empty()) {
        Logger::getInstance().error("No configuration file path specified for saving");
        return false;
    }
    
    // Open the configuration file
    std::ofstream configFile(filePath);
    if (!configFile) {
        Logger::getInstance().error("Failed to open configuration file for writing: " + filePath);
        return false;
    }
    
    // Write header
    configFile << "# LuminaChain Wallet Configuration\n";
    configFile << "# Generated on " << Logger::getInstance().getTimestamp() << "\n\n";
    
    // Write each configuration entry
    for (const auto& entry : m_configData) {
        configFile << entry.first << " = " << serializeValue(entry.second) << "\n";
    }
    
    Logger::getInstance().info("Saved configuration to " + filePath);
    return true;
}

/**
 * Gets a string configuration value
 */
std::string Config::getString(const std::string& key, const std::string& defaultValue) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    
    auto it = m_configData.find(key);
    if (it != m_configData.end()) {
        return deserializeValue(it->second);
    }
    
    return defaultValue;
}

/**
 * Gets an integer configuration value
 */
int Config::getInt(const std::string& key, int defaultValue) const {
    std::string strValue = getString(key, "");
    if (strValue.empty()) {
        return defaultValue;
    }
    
    try {
        return std::stoi(strValue);
    } catch (const std::exception& e) {
        Logger::getInstance().warning("Failed to convert configuration value to int: " + 
                                     key + " = " + strValue);
        return defaultValue;
    }
}

/**
 * Gets a double configuration value
 */
double Config::getDouble(const std::string& key, double defaultValue) const {
    std::string strValue = getString(key, "");
    if (strValue.empty()) {
        return defaultValue;
    }
    
    try {
        return std::stod(strValue);
    } catch (const std::exception& e) {
        Logger::getInstance().warning("Failed to convert configuration value to double: " + 
                                     key + " = " + strValue);
        return defaultValue;
    }
}

/**
 * Gets a boolean configuration value
 */
bool Config::getBool(const std::string& key, bool defaultValue) const {
    std::string strValue = getString(key, "");
    if (strValue.empty()) {
        return defaultValue;
    }
    
    // Convert to lowercase for case-insensitive comparison
    std::string lowerValue = strValue;
    for (char& c : lowerValue) {
        c = std::tolower(c);
    }
    
    // Check for common boolean representations
    if (lowerValue == "true" || lowerValue == "yes" || lowerValue == "1" || lowerValue == "on") {
        return true;
    } else if (lowerValue == "false" || lowerValue == "no" || lowerValue == "0" || lowerValue == "off") {
        return false;
    }
    
    Logger::getInstance().warning("Failed to convert configuration value to bool: " + 
                                 key + " = " + strValue);
    return defaultValue;
}

/**
 * Sets a string configuration value
 */
void Config::setString(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_configData[key] = value;
}

/**
 * Sets an integer configuration value
 */
void Config::setInt(const std::string& key, int value) {
    setString(key, std::to_string(value));
}

/**
 * Sets a double configuration value
 */
void Config::setDouble(const std::string& key, double value) {
    setString(key, std::to_string(value));
}

/**
 * Sets a boolean configuration value
 */
void Config::setBool(const std::string& key, bool value) {
    setString(key, value ? "true" : "false");
}

/**
 * Checks if a configuration key exists
 */
bool Config::hasKey(const std::string& key) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_configData.find(key) != m_configData.end();
}

/**
 * Removes a configuration key
 */
bool Config::removeKey(const std::string& key) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_configData.find(key);
    if (it != m_configData.end()) {
        m_configData.erase(it);
        return true;
    }
    return false;
}

/**
 * Clears all configuration settings
 */
void Config::clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_configData.clear();
}

/**
 * Parses a configuration line into key and value
 */
bool Config::parseConfigLine(const std::string& line, std::string& key, std::string& value) {
    // Find the separator
    size_t separatorPos = line.find('=');
    if (separatorPos == std::string::npos) {
        return false;
    }
    
    // Extract key and value
    key = line.substr(0, separatorPos);
    value = line.substr(separatorPos + 1);
    
    // Trim whitespace
    key = trimString(key);
    value = trimString(value);
    
    // Validate key
    if (key.empty()) {
        return false;
    }
    
    return true;
}

/**
 * Serializes a value for storage in the configuration file
 */
std::string Config::serializeValue(const std::string& value) const {
    // For now, just return the value as-is
    // In the future, this could handle escaping special characters
    return value;
}

/**
 * Deserializes a value from the configuration file
 */
std::string Config::deserializeValue(const std::string& serializedValue) const {
    // For now, just return the value as-is
    // In the future, this could handle unescaping special characters
    return serializedValue;
}

/**
 * Helper method to trim whitespace from a string
 */
std::string Config::trimString(const std::string& str) const {
    const std::string whitespace = " \t\n\r\f\v";
    
    // Find the first non-whitespace character
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        // String is all whitespace
        return "";
    }
    
    // Find the last non-whitespace character
    size_t end = str.find_last_not_of(whitespace);
    
    // Return the trimmed string
    return str.substr(start, end - start + 1);
}

} // namespace lumina