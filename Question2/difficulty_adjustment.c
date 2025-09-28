#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> // OpenSSL library for SHA256 hashing

// Define a Block structure to store blockchain block data
typedef struct {
    int index;                  // Block number in the blockchain
    char timestamp[100];        // Time when block is created
    char data[256];             // Data/content stored in the block
    char previousHash[65];      // Hash of the previous block
    char hash[65];              // SHA256 hash of the current block
    int nonce;                  // Number used to satisfy Proof of Work
} Block;

// Function to calculate the SHA256 hash of a block
void calculateHash(Block *block, char *output) {
    char input[512]; // Buffer to store concatenated block info

    // Concatenate block's index, timestamp, data, previous hash, and nonce
    sprintf(input, "%d%s%s%s%d", block->index, block->timestamp,
            block->data, block->previousHash, block->nonce);

    unsigned char hash[SHA256_DIGEST_LENGTH]; // Raw SHA256 bytes
    SHA256((unsigned char *)input, strlen(input), hash); // Compute SHA256

    // Convert raw bytes to hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0'; // Null-terminate the string
}

// Function to simulate Proof of Work mining
void proofOfWork(Block *block, int difficulty) {
    char prefix[65]; // String of leading zeros required for hash
    memset(prefix, '0', difficulty); // Fill prefix with '0's
    prefix[difficulty] = '\0'; // Null-terminate

    // Increment nonce until the hash has the required number of leading zeros
    do {
        block->nonce++;           // Change nonce to get a new hash
        calculateHash(block, block->hash); // Recalculate hash with new nonce
    } while (strncmp(block->hash, prefix, difficulty) != 0); // Check if hash meets difficulty
}

int main() {
    Block block; // Create a block
    block.index = 1; // Block number
    strcpy(block.data, "Difficulty Test"); // Example data
    strcpy(block.previousHash, "0"); // Previous hash (0 for first block)
    block.nonce = 0; // Start nonce at 0

    // Get current time for block timestamp
    time_t now = time(NULL);
    strcpy(block.timestamp, ctime(&now));

    // Loop through different difficulty levels to see mining effort
    for (int difficulty = 3; difficulty <= 5; difficulty++) {
        block.nonce = 0; // Reset nonce for new difficulty

        clock_t start = clock(); // Start timing
        proofOfWork(&block, difficulty); // Mine the block
        clock_t end = clock(); // End timing

        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate elapsed time

        // Print difficulty, resulting hash, and time taken
        printf("Difficulty: %d | Hash: %s | Time: %.2f seconds\n",
               difficulty, block.hash, timeTaken);
    }

    return 0; // End program
}
