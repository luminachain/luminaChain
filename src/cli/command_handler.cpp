/**
 * LuminaChain Wallet - Command Handler Implementation
 * 
 * This file implements the CommandHandler class which processes user commands
 * in the LuminaChain wallet command-line interface.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#include "cli/command_handler.h"
#include "core/wallet.h"
#include "contract/executor.h"
#include "network/sync.h"
#include "utils/logger.h"
#include "utils/config.h"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace lumina {

/**
 * Constructor
 */
CommandHandler::CommandHandler(std::shared_ptr<Wallet> wallet,
                               std::shared_ptr<ContractExecutor> contractExecutor,
                               std::shared_ptr<NetworkSync> networkSync)
    : m_wallet(wallet),
      m_contractExecutor(contractExecutor),
      m_networkSync(networkSync) {
    
    // Initialize default commands
    initializeDefaultCommands();
}

/**
 * Destructor
 */
CommandHandler::~CommandHandler() {
    // Nothing to clean up
}

/**
 * Registers a command with its handler function
 */
void CommandHandler::registerCommand(const std::string& command, 
                                    CommandFunction function,
                                    const std::string& description) {
    m_commandFunctions[command] = function;
    m_commandDescriptions[command] = description;
    
    Logger::getInstance().debug("Registered command: " + command);
}

/**
 * Executes a command with arguments
 */
CommandResult CommandHandler::executeCommand(const std::string& command, 
                                           const std::vector<std::string>& args) {
    // Check if the command exists
    if (!isCommandRegistered(command)) {
        return {false, "Unknown command: " + command + ". Type 'help' for a list of commands."};
    }
    
    // Execute the command
    try {
        Logger::getInstance().debug("Executing command: " + command);
        return m_commandFunctions[command](args);
    } catch (const std::exception& e) {
        Logger::getInstance().error("Exception in command execution: " + std::string(e.what()));
        return {false, "Command execution failed: " + std::string(e.what())};
    } catch (...) {
        Logger::getInstance().error("Unknown exception in command execution");
        return {false, "Command execution failed due to an unknown error"};
    }
}

/**
 * Checks if a command is registered
 */
bool CommandHandler::isCommandRegistered(const std::string& command) const {
    return m_commandFunctions.find(command) != m_commandFunctions.end();
}

/**
 * Gets the description of a command
 */
std::string CommandHandler::getCommandDescription(const std::string& command) const {
    auto it = m_commandDescriptions.find(command);
    if (it != m_commandDescriptions.end()) {
        return it->second;
    }
    return "";
}

/**
 * Gets a list of all registered commands
 */
std::map<std::string, std::string> CommandHandler::getCommandList() const {
    return m_commandDescriptions;
}

/**
 * Initializes the command handler with default commands
 */
void CommandHandler::initializeDefaultCommands() {
    // Basic commands
    registerCommand("welcome", 
                   std::bind(&CommandHandler::handleWelcome, this, std::placeholders::_1),
                   "Display welcome message");
    
    registerCommand("help", 
                   std::bind(&CommandHandler::handleHelp, this, std::placeholders::_1),
                   "Display help information");
    
    registerCommand("version", 
                   std::bind(&CommandHandler::handleVersion, this, std::placeholders::_1),
                   "Display wallet version information");
    
    // Wallet commands
    registerCommand("wallet_info", 
                   std::bind(&CommandHandler::handleWalletInfo, this, std::placeholders::_1),
                   "Display wallet information");
    
    registerCommand("balance", 
                   std::bind(&CommandHandler::handleBalance, this, std::placeholders::_1),
                   "Display wallet balance");
    
    registerCommand("transfer", 
                   std::bind(&CommandHandler::handleTransfer, this, std::placeholders::_1),
                   "Transfer funds to another address: transfer <address> <amount> [payment_id]");
    
    registerCommand("seed", 
                   std::bind(&CommandHandler::handleSeed, this, std::placeholders::_1),
                   "Display wallet seed phrase (WARNING: sensitive information)");
    
    // Contract commands
    registerCommand("execute", 
                   std::bind(&CommandHandler::handleExecuteContract, this, std::placeholders::_1),
                   "Execute a smart contract: execute <contract_address> <function> [args...]");
    
    // Network commands
    registerCommand("refresh", 
                   std::bind(&CommandHandler::handleRefresh, this, std::placeholders::_1),
                   "Refresh wallet by synchronizing with the network");
    
    registerCommand("status", 
                   std::bind(&CommandHandler::handleStatus, this, std::placeholders::_1),
                   "Display network status and synchronization information");
    
    // Misc commands
    registerCommand("donate", 
                   std::bind(&CommandHandler::handleDonate, this, std::placeholders::_1),
                   "Donate to the LuminaChain development team");
}

/**
 * Handles the welcome command
 */
CommandResult CommandHandler::handleWelcome(const std::vector<std::string>& args) {
    std::stringstream ss;
    ss << "\n";
    ss << "  ██╗     ██╗   ██╗███╗   ███╗██╗███╗   ██╗ █████╗  ██████╗██╗  ██╗ █████╗ ██╗███╗   ██╗\n";
    ss << "  ██║     ██║   ██║████╗ ████║██║████╗  ██║██╔══██╗██╔════╝██║  ██║██╔══██╗██║████╗  ██║\n";
    ss << "  ██║     ██║   ██║██╔████╔██║██║██╔██╗ ██║███████║██║     ███████║███████║██║██╔██╗ ██║\n";
    ss << "  ██║     ██║   ██║██║╚██╔╝██║██║██║╚██╗██║██╔══██║██║     ██╔══██║██╔══██║██║██║╚██╗██║\n";
    ss << "  ███████╗╚██████╔╝██║ ╚═╝ ██║██║██║ ╚████║██║  ██║╚██████╗██║  ██║██║  ██║██║██║ ╚████║\n";
    ss << "  ╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\n";
    ss << "\n";
    ss << "  Welcome to LuminaChain Wallet v1.0.0\n";
    ss << "  Type 'help' to see available commands\n";
    ss << "\n";
    
    return {true, ss.str()};
}

/**
 * Handles the help command
 */
CommandResult CommandHandler::handleHelp(const std::vector<std::string>& args) {
    std::stringstream ss;
    
    // If a specific command is requested, show its help
    if (!args.empty()) {
        std::string command = args[0];
        if (isCommandRegistered(command)) {
            ss << command << ": " << getCommandDescription(command) << "\n";
        } else {
            return {false, "Unknown command: " + command};
        }
    } else {
        // Otherwise, show all commands
        ss << "Available commands:\n";
        
        // Get all commands and sort them
        std::vector<std::pair<std::string, std::string>> commands;
        for (const auto& cmd : m_commandDescriptions) {
            commands.push_back(cmd);
        }
        
        std::sort(commands.begin(), commands.end());
        
        // Display commands in categories
        std::map<std::string, std::vector<std::pair<std::string, std::string>>> categories;
        
        // Basic commands
        categories["Basic"] = {
            {"welcome", getCommandDescription("welcome")},
            {"help", getCommandDescription("help")},
            {"version", getCommandDescription("version")}
        };
        
        // Wallet commands
        categories["Wallet"] = {
            {"wallet_info", getCommandDescription("wallet_info")},
            {"balance", getCommandDescription("balance")},
            {"transfer", getCommandDescription("transfer")},
            {"seed", getCommandDescription("seed")}
        };
        
        // Contract commands
        categories["Contract"] = {
            {"execute", getCommandDescription("execute")}
        };
        
        // Network commands
        categories["Network"] = {
            {"refresh", getCommandDescription("refresh")},
            {"status", getCommandDescription("status")}
        };
        
        // Misc commands
        categories["Misc"] = {
            {"donate", getCommandDescription("donate")}
        };
        
        // Display each category
        for (const auto& category : categories) {
            ss << "\n" << category.first << " commands:\n";
            
            for (const auto& cmd : category.second) {
                ss << "  " << std::left << std::setw(15) << cmd.first << cmd.second << "\n";
            }
        }
    }
    
    return {true, ss.str()};
}

/**
 * Handles the wallet info command
 */
CommandResult CommandHandler::handleWalletInfo(const std::vector<std::string>& args) {
    if (!m_wallet) {
        return {false, "Wallet is not initialized"};
    }
    
    std::stringstream ss;
    ss << "Wallet Information:\n";
    ss << "  Address: " << m_wallet->getAddress() << "\n";
    ss << "  Balance: " << m_wallet->getBalance() << " LUMI\n";
    ss << "  Transactions: " << m_wallet->getTransactionCount() << "\n";
    ss << "  Created: " << m_wallet->getCreationTime() << "\n";
    
    return {true, ss.str()};
}

/**
 * Handles the balance command
 */
CommandResult CommandHandler::handleBalance(const std::vector<std::string>& args) {
    if (!m_wallet) {
        return {false, "Wallet is not initialized"};
    }
    
    double balance = m_wallet->getBalance();
    
    std::stringstream ss;
    ss << "Balance: " << std::fixed << std::setprecision(8) << balance << " LUMI\n";
    
    return {true, ss.str()};
}

/**
 * Handles the transfer command
 */
CommandResult CommandHandler::handleTransfer(const std::vector<std::string>& args) {
    if (!m_wallet) {
        return {false, "Wallet is not initialized"};
    }
    
    // Check arguments
    if (args.size() < 2) {
        return {false, "Usage: transfer <address> <amount> [payment_id]"};
    }
    
    std::string address = args[0];
    double amount;
    
    // Parse amount
    try {
        amount = std::stod(args[1]);
    } catch (const std::exception&) {
        return {false, "Invalid amount: " + args[1]};
    }
    
    // Check amount
    if (amount <= 0) {
        return {false, "Amount must be positive"};
    }
    
    // Optional payment ID
    std::string paymentId = "";
    if (args.size() >= 3) {
        paymentId = args[2];
    }
    
    // Perform the transfer
    bool success = m_wallet->transfer(address, amount, paymentId);
    
    if (success) {
        std::stringstream ss;
        ss << "Transferred " << std::fixed << std::setprecision(8) << amount << " LUMI to " << address;
        if (!paymentId.empty()) {
            ss << " with payment ID " << paymentId;
        }
        return {true, ss.str()};
    } else {
        return {false, "Transfer failed. Please check your balance and the recipient address."};
    }
}

/**
 * Handles the seed command
 */
CommandResult CommandHandler::handleSeed(const std::vector<std::string>& args) {
    if (!m_wallet) {
        return {false, "Wallet is not initialized"};
    }
    
    // Security check - require confirmation
    if (args.empty() || args[0] != "confirm") {
        return {false, "WARNING: This command will display your seed phrase, which can be used to access your wallet.\n"
                      "Anyone with access to your seed phrase can steal your funds.\n"
                      "To confirm, type: seed confirm"};
    }
    
    std::string seed = m_wallet->getSeed();
    
    return {true, "Seed phrase: " + seed + "\n\nWARNING: Keep this seed phrase secret and secure!"};
}

/**
 * Handles the execute contract command
 */
CommandResult CommandHandler::handleExecuteContract(const std::vector<std::string>& args) {
    if (!m_contractExecutor) {
        return {false, "Contract executor is not initialized"};
    }
    
    // Check arguments
    if (args.size() < 2) {
        return {false, "Usage: execute <contract_address> <function> [args...]"};
    }
    
    std::string contractAddress = args[0];
    std::string function = args[1];
    
    // Collect function arguments
    std::vector<std::string> functionArgs;
    for (size_t i = 2; i < args.size(); i++) {
        functionArgs.push_back(args[i]);
    }
    
    // Execute the contract
    std::string result = m_contractExecutor->executeContract(contractAddress, function, functionArgs);
    
    return {true, "Contract execution result: " + result};
}

/**
 * Handles the refresh command
 */
CommandResult CommandHandler::handleRefresh(const std::vector<std::string>& args) {
    if (!m_networkSync || !m_wallet) {
        return {false, "Network synchronizer or wallet is not initialized"};
    }
    
    // Start synchronization
    bool success = m_networkSync->synchronize(m_wallet->getAddress());
    
    if (success) {
        return {true, "Wallet refreshed successfully"};
    } else {
        return {false, "Failed to refresh wallet. Check your network connection."};
    }
}

/**
 * Handles the status command
 */
CommandResult CommandHandler::handleStatus(const std::vector<std::string>& args) {
    if (!m_networkSync) {
        return {false, "Network synchronizer is not initialized"};
    }
    
    // Get network status
    int height = m_networkSync->getBlockchainHeight();
    int connections = m_networkSync->getConnectionCount();
    bool synced = m_networkSync->isSynchronized();
    
    std::stringstream ss;
    ss << "Network Status:\n";
    ss << "  Blockchain Height: " << height << "\n";
    ss << "  Connections: " << connections << "\n";
    ss << "  Synchronized: " << (synced ? "Yes" : "No") << "\n";
    
    return {true, ss.str()};
}

/**
 * Handles the version command
 */
CommandResult CommandHandler::handleVersion(const std::vector<std::string>& args) {
    std::stringstream ss;
    ss << "LuminaChain Wallet v1.0.0\n";
    ss << "Copyright (c) 2023 LuminaChain Development Team\n";
    ss << "Licensed under MIT License\n";
    
    return {true, ss.str()};
}

/**
 * Handles the donate command
 */
CommandResult CommandHandler::handleDonate(const std::vector<std::string>& args) {
    if (!m_wallet) {
        return {false, "Wallet is not initialized"};
    }
    
    // Donation address
    std::string donationAddress = "LUMI1DevelopmentTeamDonationAddressXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    
    // Default donation amount
    double amount = 1.0;
    
    // Parse custom amount if provided
    if (!args.empty()) {
        try {
            amount = std::stod(args[0]);
            if (amount <= 0) {
                return {false, "Donation amount must be positive"};
            }
        } catch (const std::exception&) {
            return {false, "Invalid donation amount: " + args[0]};
        }
    }
    
    // Confirm donation
    if (args.size() < 2 || args[1] != "confirm") {
        std::stringstream ss;
        ss << "You are about to donate " << std::fixed << std::setprecision(8) << amount << " LUMI to the LuminaChain development team.\n";
        ss << "To confirm, type: donate " << amount << " confirm";
        return {true, ss.str()};
    }
    
    // Perform the donation
    bool success = m_wallet->transfer(donationAddress, amount, "Donation");
    
    if (success) {
        return {true, "Thank you for your donation of " + std::to_string(amount) + " LUMI to the LuminaChain development team!"};
    } else {
        return {false, "Donation failed. Please check your balance."};
    }
}

} // namespace lumina