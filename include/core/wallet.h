/**
 * LuminaChain Wallet - Core Wallet Functionality
 * 
 * This file defines the Wallet class which is responsible for managing
 * wallet addresses, balances, and transactions.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#ifndef LUMINA_WALLET_H
#define LUMINA_WALLET_H

#include <string>
#include <vector>
#include <map>
#include <memory>

// Forward declarations
namespace lumina {
    class Transaction;
}

namespace lumina {

/**
 * Represents a wallet in the LuminaChain network
 */
class Wallet {
public:
    /**
     * Constructor - Creates a new wallet or loads an existing one
     * 
     * @param walletPath Path to the wallet file
     * @param password Password to encrypt/decrypt the wallet
     */
    Wallet(const std::string& walletPath, const std::string& password);
    
    /**
     * Destructor
     */
    ~Wallet();
    
    /**
     * Creates a new wallet with a random seed
     * 
     * @return true if wallet creation was successful
     */
    bool create();
    
    /**
     * Recovers a wallet using a 12-word seed phrase
     * 
     * @param seedPhrase The 12-word seed phrase
     * @return true if wallet recovery was successful
     */
    bool recoverFromSeed(const std::string& seedPhrase);
    
    /**
     * Gets the main address of the wallet
     * 
     * @return The main wallet address
     */
    std::string getMainAddress() const;
    
    /**
     * Gets the balance of the wallet
     * 
     * @param tokenSymbol The token symbol (default: LMT)
     * @return The balance amount
     */
    double getBalance(const std::string& tokenSymbol = "LMT") const;
    
    /**
     * Transfers funds to another address
     * 
     * @param toAddress The recipient address
     * @param amount The amount to transfer
     * @param tokenSymbol The token symbol (default: LMT)
     * @return true if the transfer was successful
     */
    bool transfer(const std::string& toAddress, double amount, const std::string& tokenSymbol = "LMT");
    
    /**
     * Gets the seed phrase for backup purposes
     * 
     * @param password The wallet password for verification
     * @return The 12-word seed phrase
     */
    std::string getSeedPhrase(const std::string& password) const;
    
    /**
     * Synchronizes the wallet with the network
     * 
     * @return true if synchronization was successful
     */
    bool synchronize();
    
    /**
     * Gets the current status of the wallet
     * 
     * @return A string describing the current status
     */
    std::string getStatus() const;
    
    /**
     * Makes a donation to the development team
     * 
     * @param amount The amount to donate
     * @return true if the donation was successful
     */
    bool donate(double amount);

private:
    // Wallet data
    std::string m_walletPath;
    std::string m_mainAddress;
    std::string m_encryptedSeed;
    std::map<std::string, double> m_balances; // Token symbol -> balance
    
    // Transaction history
    std::vector<std::shared_ptr<Transaction>> m_transactions;
    
    // Wallet state
    bool m_isInitialized;
    bool m_isSynchronized;
    
    // Internal methods
    bool saveWallet() const;
    bool loadWallet();
    std::string generateSeed() const;
    std::string encryptSeed(const std::string& seed, const std::string& password) const;
    std::string decryptSeed(const std::string& encryptedSeed, const std::string& password) const;
};

} // namespace lumina

#endif // LUMINA_WALLET_H