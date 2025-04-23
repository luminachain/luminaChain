/**
 * LuminaChain Wallet - Transaction Functionality
 * 
 * This file defines the Transaction class which represents a transaction
 * on the LuminaChain network.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#ifndef LUMINA_TRANSACTION_H
#define LUMINA_TRANSACTION_H

#include <string>
#include <vector>
#include <ctime>

namespace lumina {

/**
 * Represents a transaction status in the network
 */
enum class TransactionStatus {
    PENDING,    // Transaction is waiting to be included in a block
    CONFIRMED,  // Transaction is confirmed and included in a block
    FAILED      // Transaction failed to be processed
};

/**
 * Represents a transaction in the LuminaChain network
 */
class Transaction {
public:
    /**
     * Constructor - Creates a new transaction
     * 
     * @param fromAddress The sender address
     * @param toAddress The recipient address
     * @param amount The amount to transfer
     * @param tokenSymbol The token symbol (default: LMT)
     */
    Transaction(const std::string& fromAddress, 
                const std::string& toAddress, 
                double amount, 
                const std::string& tokenSymbol = "LMT");
    
    /**
     * Gets the transaction ID
     * 
     * @return The transaction ID
     */
    std::string getId() const;
    
    /**
     * Gets the sender address
     * 
     * @return The sender address
     */
    std::string getFromAddress() const;
    
    /**
     * Gets the recipient address
     * 
     * @return The recipient address
     */
    std::string getToAddress() const;
    
    /**
     * Gets the transaction amount
     * 
     * @return The transaction amount
     */
    double getAmount() const;
    
    /**
     * Gets the token symbol
     * 
     * @return The token symbol
     */
    std::string getTokenSymbol() const;
    
    /**
     * Gets the transaction timestamp
     * 
     * @return The transaction timestamp
     */
    time_t getTimestamp() const;
    
    /**
     * Gets the transaction status
     * 
     * @return The transaction status
     */
    TransactionStatus getStatus() const;
    
    /**
     * Sets the transaction status
     * 
     * @param status The new transaction status
     */
    void setStatus(TransactionStatus status);
    
    /**
     * Signs the transaction with the sender's private key
     * 
     * @param privateKey The sender's private key
     * @return true if signing was successful
     */
    bool sign(const std::string& privateKey);
    
    /**
     * Verifies the transaction signature
     * 
     * @return true if the signature is valid
     */
    bool verifySignature() const;
    
    /**
     * Converts the transaction to a string representation
     * 
     * @return String representation of the transaction
     */
    std::string toString() const;

private:
    std::string m_id;             // Transaction ID
    std::string m_fromAddress;    // Sender address
    std::string m_toAddress;      // Recipient address
    double m_amount;              // Transaction amount
    std::string m_tokenSymbol;    // Token symbol
    time_t m_timestamp;           // Transaction timestamp
    TransactionStatus m_status;   // Transaction status
    std::string m_signature;      // Transaction signature
    
    // Internal methods
    std::string generateId() const;
};

} // namespace lumina

#endif // LUMINA_TRANSACTION_H