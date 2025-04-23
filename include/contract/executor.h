/**
 * LuminaChain Wallet - Smart Contract Executor
 * 
 * This file defines the ContractExecutor class which is responsible for
 * executing Lumina smart contracts.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#ifndef LUMINA_CONTRACT_EXECUTOR_H
#define LUMINA_CONTRACT_EXECUTOR_H

#include <string>
#include <vector>
#include <map>

namespace lumina {

/**
 * Represents the result of a contract execution
 */
struct ContractResult {
    bool success;           // Whether the execution was successful
    std::string message;    // Result message or error description
    std::string txId;       // Transaction ID if a transaction was created
};

/**
 * Responsible for executing Lumina smart contracts
 */
class ContractExecutor {
public:
    /**
     * Constructor
     * 
     * @param walletAddress The wallet address to use for contract execution
     */
    ContractExecutor(const std::string& walletAddress);
    
    /**
     * Destructor
     */
    ~ContractExecutor();
    
    /**
     * Executes a smart contract from a file
     * 
     * @param filePath Path to the contract file
     * @return The result of the contract execution
     */
    ContractResult executeFromFile(const std::string& filePath);
    
    /**
     * Executes a smart contract from a string
     * 
     * @param contractCode The contract code as a string
     * @return The result of the contract execution
     */
    ContractResult executeFromString(const std::string& contractCode);
    
    /**
     * Sets a parameter for contract execution
     * 
     * @param name Parameter name
     * @param value Parameter value
     */
    void setParameter(const std::string& name, const std::string& value);
    
    /**
     * Gets the gas cost estimate for executing a contract
     * 
     * @param contractCode The contract code
     * @return Estimated gas cost in LMT
     */
    double estimateGasCost(const std::string& contractCode);

private:
    std::string m_walletAddress;                      // Wallet address for execution
    std::map<std::string, std::string> m_parameters;  // Contract parameters
    
    // Internal methods
    bool validateContract(const std::string& contractCode);
    std::string preprocessContract(const std::string& contractCode);
    ContractResult interpretContract(const std::string& processedCode);
};

} // namespace lumina

#endif // LUMINA_CONTRACT_EXECUTOR_H