/**
 * LuminaChain Wallet - Command Handler
 * 
 * This file defines the CommandHandler class which processes user commands
 * in the LuminaChain wallet command-line interface.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#ifndef LUMINA_COMMAND_HANDLER_H
#define LUMINA_COMMAND_HANDLER_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>

// Forward declarations
namespace lumina {
    class Wallet;
    class ContractExecutor;
    class NetworkSync;
}

namespace lumina {

/**
 * Command handler result structure
 */
struct CommandResult {
    bool success;           // Whether the command was successful
    std::string message;    // Result message or error description
};

/**
 * Command handler function type
 */
typedef std::function<CommandResult(const std::vector<std::string>&)> CommandFunction;

/**
 * Handles commands in the wallet command-line interface
 */
class CommandHandler {
public:
    /**
     * Constructor
     * 
     * @param wallet Pointer to the wallet instance
     * @param contractExecutor Pointer to the contract executor
     * @param networkSync Pointer to the network synchronizer
     */
    CommandHandler(std::shared_ptr<Wallet> wallet,
                   std::shared_ptr<ContractExecutor> contractExecutor,
                   std::shared_ptr<NetworkSync> networkSync);
    
    /**
     * Destructor
     */
    ~CommandHandler();
    
    /**
     * Registers a command with its handler function
     * 
     * @param command The command name
     * @param function The handler function
     * @param description The command description
     */
    void registerCommand(const std::string& command, 
                         CommandFunction function,
                         const std::string& description);
    
    /**
     * Executes a command with arguments
     * 
     * @param command The command to execute
     * @param args The command arguments
     * @return The command execution result
     */
    CommandResult executeCommand(const std::string& command, 
                                const std::vector<std::string>& args);
    
    /**
     * Checks if a command is registered
     * 
     * @param command The command name
     * @return true if the command is registered
     */
    bool isCommandRegistered(const std::string& command) const;
    
    /**
     * Gets the description of a command
     * 
     * @param command The command name
     * @return The command description
     */
    std::string getCommandDescription(const std::string& command) const;
    
    /**
     * Gets a list of all registered commands
     * 
     * @return A map of command names to descriptions
     */
    std::map<std::string, std::string> getCommandList() const;
    
    /**
     * Initializes the command handler with default commands
     */
    void initializeDefaultCommands();

private:
    // Component references
    std::shared_ptr<Wallet> m_wallet;
    std::shared_ptr<ContractExecutor> m_contractExecutor;
    std::shared_ptr<NetworkSync> m_networkSync;
    
    // Command registry
    std::map<std::string, CommandFunction> m_commandFunctions;
    std::map<std::string, std::string> m_commandDescriptions;
    
    // Default command handlers
    CommandResult handleWelcome(const std::vector<std::string>& args);
    CommandResult handleHelp(const std::vector<std::string>& args);
    CommandResult handleWalletInfo(const std::vector<std::string>& args);
    CommandResult handleBalance(const std::vector<std::string>& args);
    CommandResult handleTransfer(const std::vector<std::string>& args);
    CommandResult handleSeed(const std::vector<std::string>& args);
    CommandResult handleExecuteContract(const std::vector<std::string>& args);
    CommandResult handleRefresh(const std::vector<std::string>& args);
    CommandResult handleStatus(const std::vector<std::string>& args);
    CommandResult handleVersion(const std::vector<std::string>& args);
    CommandResult handleDonate(const std::vector<std::string>& args);
};

} // namespace lumina

#endif // LUMINA_COMMAND_HANDLER_H