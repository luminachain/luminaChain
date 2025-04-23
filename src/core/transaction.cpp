/**
 * LuminaChain Wallet - Transaction Implementation
 * 
 * This file implements the Transaction class which represents a transaction
 * on the LuminaChain network.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#include "core/transaction.h"
#include "utils/logger.h"
#include <sstream>
#include <iomanip>
#include <random>

namespace lumina {

/**
 * Constructor - Creates a new transaction
 */
Transaction::Transaction(const std::string& fromAddress, 
                         const std::string& toAddress, 
                         double amount, 
                         const std::string& tokenSymbol)
    : m_fromAddress(fromAddress),
      m_toAddress(toAddress),
      m_amount(amount),
      m_tokenSymbol(tokenSymbol),
      m_timestamp(std::time(nullptr)),
      m_status(TransactionStatus::PENDING) {
    
    // Generate a unique transaction ID
    m_id = generateId();
    
    Logger::getInstance().info("Created new transaction: " + m_id);
}

/**
 * Gets the transaction ID
 */
std::string Transaction::getId() const {
    return m_id;
}

/**
 * Gets the sender address
 */
std::string Transaction::getFromAddress() const {
    return m_fromAddress;
}

/**
 * Gets the recipient address
 */
std::string Transaction::getToAddress() const {
    return m_toAddress;
}

/**
 * Gets the transaction amount
 */
double Transaction::getAmount() const {
    return m_amount;
}

/**
 * Gets the token symbol
 */
std::string Transaction::getTokenSymbol() const {
    return m_tokenSymbol;
}

/**
 * Gets the transaction timestamp
 */
time_t Transaction::getTimestamp() const {
    return m_timestamp;
}

/**
 * Gets the transaction status
 */
TransactionStatus Transaction::getStatus() const {
    return m_status;
}

/**
 * Sets the transaction status
 */
void Transaction::setStatus(TransactionStatus status) {
    m_status = status;
    
    std::string statusStr;
    switch (status) {
        case TransactionStatus::PENDING:
            statusStr = "PENDING";
            break;
        case TransactionStatus::CONFIRMED:
            statusStr = "CONFIRMED";
            break;
        case TransactionStatus::FAILED:
            statusStr = "FAILED";
            break;
    }
    
    Logger::getInstance().info("Transaction " + m_id + " status changed to " + statusStr);
}

/**
 * Signs the transaction with the sender's private key
 */
bool Transaction::sign(const std::string& privateKey) {
    // TODO: Implement proper transaction signing
    
    // For now, just simulate a successful signing
    m_signature = "SIGNATURE_" + m_id;
    
    Logger::getInstance().info("Transaction " + m_id + " signed successfully");
    
    return true;
}

/**
 * Verifies the transaction signature
 */
bool Transaction::verifySignature() const {
    // TODO: Implement proper signature verification
    
    // For now, just check if signature exists and has the expected format
    return !m_signature.empty() && m_signature.substr(0, 10) == "SIGNATURE_";
}

/**
 * Converts the transaction to a string representation
 */
std::string Transaction::toString() const {
    std::ostringstream oss;
    
    // Format timestamp as a readable string
    char timeBuffer[26];
    struct tm* timeInfo = localtime(&m_timestamp);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    
    // Format status as a string
    std::string statusStr;
    switch (m_status) {
        case TransactionStatus::PENDING:
            statusStr = "PENDING";
            break;
        case TransactionStatus::CONFIRMED:
            statusStr = "CONFIRMED";
            break;
        case TransactionStatus::FAILED:
            statusStr = "FAILED";
            break;
    }
    
    // Build the string representation
    oss << "Transaction ID: " << m_id << "\n"
        << "From: " << m_fromAddress << "\n"
        << "To: " << m_toAddress << "\n"
        << "Amount: " << std::fixed << std::setprecision(8) << m_amount << " " << m_tokenSymbol << "\n"
        << "Timestamp: " << timeBuffer << "\n"
        << "Status: " << statusStr << "\n";
    
    return oss.str();
}

/**
 * Generates a unique transaction ID
 */
std::string Transaction::generateId() const {
    // Generate a random transaction ID
    // In a real implementation, this would be a hash of the transaction data
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    
    const char* hexChars = "0123456789abcdef";
    std::string uuid;
    
    for (int i = 0; i < 32; ++i) {
        uuid += hexChars[dis(gen)];
        if (i == 7 || i == 11 || i == 15 || i == 19) {
            uuid += '-';
        }
    }
    
    return "TX-" + uuid;
}

} // namespace lumina