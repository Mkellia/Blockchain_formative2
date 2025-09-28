#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> // Library for SHA256 hashing

// Define a block structure
typedef struct {
    int index;                  // Block number in the blockchain
    char timestamp[100];        // When the block was created
    char data[256];             // Data stored in the block (e.g., transaction info)
    char previousHash[65];      // Hash of the previous block
    char hash[65];              // SHA256 hash of this block
    int nonce;                  // Number used for Proof of Work
} Block;

// Function to calculate SHA256 hash of a block
void calculateHash(Block *block, char *output) {
    char input[512]; // Buffer to combine block info

    // Combine index, timestamp, data, previous hash, and nonce into one string
    sprintf(input, "%d%s%s%s%d", block->index, block->timestamp,
            block->data, block->previousHash, block->nonce);

    unsigned char hash[SHA256_DIGEST_LENGTH]; // Buffer for raw SHA256 output
    SHA256((unsigned char *)input, strlen(input), hash); // Compute hash

    // Convert each byte of SHA256 output to a hex string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0'; // Null-terminate the string
}

// Function to perform Proof of Work
void proofOfWork(Block *block, int difficulty) {
    char prefix[65];             // String representing required leading zeros
    memset(prefix, '0', difficulty); // Fill prefix with '0's
    prefix[difficulty] = '\0';       // Null-terminate

    // Increment nonce until hash has required number of leading zeros
    do {
        block->nonce++;             // Try a new nonce
        calculateHash(block, block->hash); // Recalculate hash
    } while (strncmp(block->hash, prefix, difficulty) != 0); // Check prefix

    printf("Mined block with hash: %s\n", block->hash); // Show mined hash
}

int main() {
    Block block;                     // Create a new block
    block.index = 1;                 // Block number
    strcpy(block.data, "Transaction Data"); // Sample transaction data
    strcpy(block.previousHash, "abc123");  // Previous block hash
    block.nonce = 0;                 // Initialize nonce

    time_t now = time(NULL);         // Get current time
    strcpy(block.timestamp, ctime(&now)); // Store timestamp as string

    proofOfWork(&block, 4);          // Mine the block with difficulty 4

    return 0;                        // Exit program
}
