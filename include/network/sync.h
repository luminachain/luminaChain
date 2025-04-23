/**
 * LuminaChain Wallet - Network Synchronization
 * 
 * This file defines the NetworkSync class which is responsible for
 * synchronizing the wallet with the LuminaChain network.
 * 
 * Copyright (c) 2023 LuminaChain Development Team
 * Licensed under MIT License
 */

#ifndef LUMINA_NETWORK_SYNC_H
#define LUMINA_NETWORK_SYNC_H

#include <string>
#include <vector>
#include <functional>

namespace lumina {

/**
 * Represents the synchronization status
 */
enum class SyncStatus {
    NOT_SYNCED,     // Wallet is not synchronized with the network
    SYNCING,        // Synchronization is in progress
    SYNCED          // Wallet is fully synchronized with the network
};

/**
 * Callback type for synchronization progress updates
 */
typedef std::function<void(float progress, const std::string& message)> SyncProgressCallback;

/**
 * Responsible for synchronizing the wallet with the LuminaChain network
 */
class NetworkSync {
public:
    /**
     * Constructor
     * 
     * @param walletAddress The wallet address to synchronize
     */
    NetworkSync(const std::string& walletAddress);
    
    /**
     * Destructor
     */
    ~NetworkSync();
    
    /**
     * Starts the synchronization process
     * 
     * @param callback Callback function for progress updates
     * @return true if synchronization started successfully
     */
    bool startSync(SyncProgressCallback callback = nullptr);
    
    /**
     * Stops the synchronization process
     * 
     * @return true if synchronization was stopped successfully
     */
    bool stopSync();
    
    /**
     * Gets the current synchronization status
     * 
     * @return The current synchronization status
     */
    SyncStatus getStatus() const;
    
    /**
     * Gets the synchronization progress
     * 
     * @return Synchronization progress as a value between 0.0 and 1.0
     */
    float getProgress() const;
    
    /**
     * Gets the latest block height from the network
     * 
     * @return The latest block height
     */
    uint64_t getLatestBlockHeight() const;
    
    /**
     * Gets the current block height of the wallet
     * 
     * @return The current block height of the wallet
     */
    uint64_t getCurrentBlockHeight() const;
    
    /**
     * Sets the network endpoint to connect to
     * 
     * @param endpoint The network endpoint URL
     */
    void setNetworkEndpoint(const std::string& endpoint);
    
    /**
     * Gets the current network endpoint
     * 
     * @return The current network endpoint URL
     */
    std::string getNetworkEndpoint() const;

private:
    std::string m_walletAddress;       // Wallet address to synchronize
    std::string m_networkEndpoint;     // Network endpoint URL
    SyncStatus m_status;               // Current synchronization status
    float m_progress;                  // Synchronization progress (0.0 - 1.0)
    uint64_t m_latestBlockHeight;      // Latest block height from the network
    uint64_t m_currentBlockHeight;     // Current block height of the wallet
    bool m_isSyncing;                  // Flag indicating if synchronization is in progress
    SyncProgressCallback m_callback;    // Callback for progress updates
    
    // Internal methods
    bool connectToNetwork();
    bool fetchLatestBlockHeight();
    bool processBlocks(uint64_t fromHeight, uint64_t toHeight);
    void updateProgress(float progress, const std::string& message);
};

} // namespace lumina

#endif // LUMINA_NETWORK_SYNC_H