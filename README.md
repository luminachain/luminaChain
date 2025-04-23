
# 💼 LuminaChain Wallet

**LuminaChain Wallet** is the official command-line wallet for the [LuminaChain](https://luminachain.pro) cryptocurrency network, implemented in C/C++.  
It offers core wallet functionality such as balance checking, asset transfers, smart contract execution, and network synchronization — all through a lightweight terminal interface.

---

## 🔧 Features

- 🔐 Wallet creation, recovery (12-word seed), and backup
- 💰 View balance and transaction history
- 💸 Transfer LMT and tokens to other addresses
- 🧠 Execute Lumina smart contract files
- 🔄 Synchronize with the LuminaChain network
- 📊 Monitor wallet and network status

---

## 🗂 Project Structure

```
├── src/
│   ├── core/           # Wallet logic (creation, keys, seed, transfer)
│   ├── contract/       # Smart contract parser and executor
│   ├── network/        # Network sync, RPC, and peer handling
│   ├── utils/          # Utilities and helpers
│   ├── cli/            # Command-line interaction
│   └── main.cpp        # Entry point
├── include/            # C++ header files
├── lib/                # External or third-party libraries
├── tests/              # Unit tests and test cases
└── CMakeLists.txt      # Build system (CMake)
```

---

## ⚙️ Building

### Requirements:
- CMake 3.10+
- GCC / Clang (C++17 support)

### Build Steps:
```bash
mkdir build
cd build
cmake ..
make
```

---

## 🚀 Usage

Run the wallet:

```bash
./lumina_wallet
```

### 🧪 Available Commands

| Command | Description |
|---------|-------------|
| `welcome` | Show welcome message |
| `help` | Show all available commands |
| `wallet_info` | Display wallet main address and metadata |
| `balance` | Show LMT balance |
| `transfer <address> <amount> [<token>]` | Send LMT or other tokens to a target address |
| `seed` | Display your 12-word mnemonic seed phrase |
| `execute_contract <file_path>` | Run a smart contract (.luma file) |
| `refresh` | Synchronize with the LuminaChain network |
| `status` | Show current wallet/network sync status |
| `version` | Display current wallet version |
| `donate <amount>` | Donate LMT to support LuminaChain development |
| `exit` | Exit the wallet |

> ⚠️ Please securely store your seed phrase. It is the **only way** to recover your wallet.

---

## 📄 License

Open-sourced under the [MIT License](LICENSE)

---

## 🤝 Contributing

We welcome community contributions!

To contribute:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/your-feature`)
5. Submit a pull request

---

## 🌐 Resources

- 🔗 Website: [https://luminachain.pro](https://luminachain.pro)
- 🧠 Smart Contract Language: [LumaLang](https://medium.com/@luminachainorg)
- ⛏️ Miner: [lmtig Mining Software](https://github.com/luminachain/lmtig_mining)

