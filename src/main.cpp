/**
 * LuminaChain Wallet - Command Line Interface
 * 
 * This is the main entry point for the LuminaChain wallet application.
 * It implements a command-line interface for interacting with the LuminaChain network.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <sstream>

// Core wallet functionality
#include "core/wallet.h"
#include "core/transaction.h"

// Smart contract execution
#include "contract/executor.h"

// Network communication
#include "network/sync.h"

// Utilities
#include "utils/logger.h"
#include "utils/config.h"

// CLI interface
#include "cli/command_handler.h"

// Version information
const std::string VERSION = "0.1.0";
const std::string WALLET_NAME = "LuminaChain Wallet";

// Function prototypes
bool parseCommandLine(const std::string& input, std::string& command, std::vector<std::string>& args);

/**
 * Main function - entry point of the application
 */
int main(int argc, char* argv[]) {
    // Initialize logger
    lumina::Logger::getInstance().initialize("lumina_wallet.log");
    lumina::Logger::getInstance().info("Starting " + WALLET_NAME + " v" + VERSION);
    
    // Load configuration
    std::string configPath = "lumina_wallet.conf";
    if (argc > 1) {
        configPath = argv[1];
    }
    
    lumina::Config::getInstance().loadFromFile(configPath);
    lumina::Logger::getInstance().info("Configuration loaded from " + configPath);
    
    // Initialize wallet components
    auto wallet = std::make_shared<lumina::Wallet>();
    auto contractExecutor = std::make_shared<lumina::ContractExecutor>();
    auto networkSync = std::make_shared<lumina::NetworkSync>();
    
    // Initialize command handler
    lumina::CommandHandler commandHandler(wallet, contractExecutor, networkSync);
    
    // Display welcome message on startup
    lumina::CommandResult welcomeResult = commandHandler.executeCommand("welcome", {});
    std::cout << welcomeResult.message << std::endl;
    
    // Main command processing loop
    std::string input;
    std::string command;
    std::vector<std::string> args;
    bool running = true;
    
    while (running) {
        std::cout << "lumina> ";
        std::getline(std::cin, input);
        
        if (parseCommandLine(input, command, args)) {
            if (command == "exit") {
                running = false;
                std::cout << "Exiting LuminaChain Wallet. Goodbye!" << std::endl;
                lumina::Logger::getInstance().info("Application exit requested by user");
            } else {
                lumina::CommandResult result = commandHandler.executeCommand(command, args);
                std::cout << result.message << std::endl;
                
                if (!result.success) {
                    lumina::Logger::getInstance().warning("Command failed: " + command);
                }
            }
        }
    }
    
    // Save configuration before exit
    lumina::Config::getInstance().saveToFile();
    lumina::Logger::getInstance().info("Configuration saved");
    lumina::Logger::getInstance().info("Application terminated normally");
    
    return 0;
}



/**
 * Parses the command line input into command and arguments
 * 
 * @param input The raw input string from the user
 * @param command Output parameter for the parsed command
 * @param args Output parameter for the parsed arguments
 * @return true if parsing was successful, false otherwise
 */
bool parseCommandLine(const std::string& input, std::string& command, std::vector<std::string>& args) {
    args.clear();
    std::istringstream iss(input);
    
    if (!(iss >> command)) {
        return false; // Empty input
    }
    
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    
    return true;
}