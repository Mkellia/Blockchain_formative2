#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> // For SHA256 hashing

// Define a Block structure with linked-list capability
typedef struct Block {
    int index;                  // Block number
    char timestamp[100];        // Time when block was created
    char data[256];             // Block content (e.g., transaction info)
    char previousHash[65];      // Hash of the previous block
    char hash[65];              // SHA256 hash of this block
    int nonce;                  // Used for Proof of Work
    struct Block *next;         // Pointer to the next block (linked list)
} Block;

// Function to calculate the SHA256 hash of a block
void calculateHash(Block *block, char *output) {
    char input[512]; // Concatenate block info for hashing

    // Combine block index, timestamp, data, previous hash, and nonce
    sprintf(input, "%d%s%s%s%d", block->index, block->timestamp,
            block->data, block->previousHash, block->nonce);

    unsigned char hash[SHA256_DIGEST_LENGTH]; // Raw SHA256 bytes
    SHA256((unsigned char *)input, strlen(input), hash); // Compute SHA256 hash

    // Convert raw bytes into a hexadecimal string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0'; // Null-terminate the hash string
}

// Proof of Work: find a nonce so that the hash has 'difficulty' leading zeros
void proofOfWork(Block *block, int difficulty) {
    char prefix[65];            // Required leading zeros
    memset(prefix, '0', difficulty); // Fill prefix with '0's
    prefix[difficulty] = '\0';       // Null-terminate string

    // Keep incrementing nonce until hash meets difficulty
    do {
        block->nonce++;             // Try a new nonce
        calculateHash(block, block->hash); // Recalculate hash
    } while (strncmp(block->hash, prefix, difficulty) != 0); // Check prefix
}

// Function to create a new block
Block *createBlock(int index, char *data, char *previousHash, int difficulty) {
    Block *newBlock = (Block *)malloc(sizeof(Block)); // Allocate memory
    newBlock->index = index;            // Set block index
    strcpy(newBlock->data, data);       // Copy block data
    strcpy(newBlock->previousHash, previousHash); // Link to previous block
    newBlock->nonce = 0;                // Start nonce at 0

    // Set timestamp to current time
    time_t now = time(NULL);
    strcpy(newBlock->timestamp, ctime(&now));

    proofOfWork(newBlock, difficulty);  // Mine the block

    return newBlock; // Return pointer to newly created block
}

int main() {
    // Create the genesis block (first block in the chain)
    Block *genesis = createBlock(0, "Genesis Block", "0", 4);

    // Create a second block linking to the genesis block
    Block *block1 = createBlock(1, "Transaction: Kenny -> Colette", genesis->hash, 4);

    // Print hashes of the blocks
    printf("Genesis Hash: %s\n", genesis->hash);
    printf("Block1 Hash: %s\n", block1->hash);

    // Free allocated memory
    free(genesis);
    free(block1);

    return 0;
}
