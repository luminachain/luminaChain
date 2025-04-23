/**
 * LuminaChain Wallet - Configuration Utility
 * 
 * This file defines the Config class which manages application configuration
 * settings for the LuminaChain wallet.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#ifndef LUMINA_CONFIG_H
#define LUMINA_CONFIG_H

#include <string>
#include <map>
#include <mutex>

namespace lumina {

/**
 * Manages application configuration settings
 */
class Config {
public:
    /**
     * Gets the singleton instance of the configuration manager
     * 
     * @return The configuration manager instance
     */
    static Config& getInstance();
    
    /**
     * Loads configuration from a file
     * 
     * @param configFilePath Path to the configuration file
     * @return true if loading was successful
     */
    bool loadFromFile(const std::string& configFilePath);
    
    /**
     * Saves configuration to a file
     * 
     * @param configFilePath Path to the configuration file
     * @return true if saving was successful
     */
    bool saveToFile(const std::string& configFilePath = "");
    
    /**
     * Gets a string configuration value
     * 
     * @param key The configuration key
     * @param defaultValue The default value to return if the key is not found
     * @return The configuration value
     */
    std::string getString(const std::string& key, const std::string& defaultValue = "") const;
    
    /**
     * Gets an integer configuration value
     * 
     * @param key The configuration key
     * @param defaultValue The default value to return if the key is not found
     * @return The configuration value
     */
    int getInt(const std::string& key, int defaultValue = 0) const;
    
    /**
     * Gets a double configuration value
     * 
     * @param key The configuration key
     * @param defaultValue The default value to return if the key is not found
     * @return The configuration value
     */
    double getDouble(const std::string& key, double defaultValue = 0.0) const;
    
    /**
     * Gets a boolean configuration value
     * 
     * @param key The configuration key
     * @param defaultValue The default value to return if the key is not found
     * @return The configuration value
     */
    bool getBool(const std::string& key, bool defaultValue = false) const;
    
    /**
     * Sets a string configuration value
     * 
     * @param key The configuration key
     * @param value The configuration value
     */
    void setString(const std::string& key, const std::string& value);
    
    /**
     * Sets an integer configuration value
     * 
     * @param key The configuration key
     * @param value The configuration value
     */
    void setInt(const std::string& key, int value);
    
    /**
     * Sets a double configuration value
     * 
     * @param key The configuration key
     * @param value The configuration value
     */
    void setDouble(const std::string& key, double value);
    
    /**
     * Sets a boolean configuration value
     * 
     * @param key The configuration key
     * @param value The configuration value
     */
    void setBool(const std::string& key, bool value);
    
    /**
     * Checks if a configuration key exists
     * 
     * @param key The configuration key
     * @return true if the key exists
     */
    bool hasKey(const std::string& key) const;
    
    /**
     * Removes a configuration key
     * 
     * @param key The configuration key
     * @return true if the key was removed
     */
    bool removeKey(const std::string& key);
    
    /**
     * Clears all configuration settings
     */
    void clear();

private:
    // Private constructor for singleton pattern
    Config();
    
    // Prevent copying and assignment
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    
    // Configuration data
    std::map<std::string, std::string> m_configData;
    std::string m_configFilePath;
    mutable std::mutex m_mutex;
    
    // Internal methods
    bool parseConfigLine(const std::string& line, std::string& key, std::string& value);
    std::string serializeValue(const std::string& value) const;
    std::string deserializeValue(const std::string& serializedValue) const;
    std::string trimString(const std::string& str) const;
};

} // namespace lumina

#endif // LUMINA_CONFIG_H