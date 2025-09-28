#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> // OpenSSL library for SHA256 hashing

// Define a Block structure to represent a block in the blockchain
typedef struct {
    int index;                  // Block number in the chain
    char timestamp[100];        // Time when block is created
    char data[256];             // Data stored in the block
    char previousHash[65];      // SHA256 hash of the previous block
    char hash[65];              // SHA256 hash of this block
    int nonce;                  // Number used in mining (Proof of Work)
} Block;

// Function to calculate the SHA256 hash of a block
void calculateHash(Block *block, char *output) {
    char input[512]; // String to store concatenated block info

    // Concatenate block's index, timestamp, data, previous hash, and nonce
    sprintf(input, "%d%s%s%s%d", block->index, block->timestamp,
            block->data, block->previousHash, block->nonce);

    unsigned char hash[SHA256_DIGEST_LENGTH]; // Store raw SHA256 bytes
    SHA256((unsigned char *)input, strlen(input), hash); // Calculate SHA256

    // Convert raw hash bytes to hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0'; // Null-terminate the string
}

int main() {
    Block genesis; // Create the first block (Genesis Block)
    genesis.index = 0; // Index of genesis block
    strcpy(genesis.data, "Genesis Block"); // Set block data
    strcpy(genesis.previousHash, "0"); // No previous block for genesis
    genesis.nonce = 0; // Initial nonce

    // Get current time and store as timestamp
    time_t now = time(NULL);
    strcpy(genesis.timestamp, ctime(&now));

    // Calculate hash of the genesis block
    calculateHash(&genesis, genesis.hash);

    // Print details of the genesis block
    printf("Genesis Block:\n");
    printf("Index: %d\n", genesis.index);
    printf("Timestamp: %s", genesis.timestamp);
    printf("Data: %s\n", genesis.data);
    printf("Previous Hash: %s\n", genesis.previousHash);
    printf("Hash: %s\n", genesis.hash);

    return 0; // End of program
}
