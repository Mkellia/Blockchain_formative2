#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h> // For SHA256 hashing

// Define a Block structure
typedef struct Block {
    int index;                  // Block position in the chain
    char timestamp[100];        // Creation time
    char data[256];             // Transaction or block data
    char previousHash[65];      // Hash of previous block
    char hash[65];              // Current block hash
    int nonce;                  // For proof of work
    struct Block *next;         // Pointer to next block
} Block;

// Function to calculate hash of a block
void calculateHash(Block *block, char *output) {
    char input[512];
    sprintf(input, "%d%s%s%s%d", block->index, block->timestamp,
            block->data, block->previousHash, block->nonce);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[64] = '\0';
}

// Proof of Work: mine until hash starts with N zeros
void proofOfWork(Block *block, int difficulty) {
    char prefix[65];
    memset(prefix, '0', difficulty);
    prefix[difficulty] = '\0';

    do {
        block->nonce++;
        calculateHash(block, block->hash);
    } while (strncmp(block->hash, prefix, difficulty) != 0);

    printf("✅ Block %d mined with hash: %s\n", block->index, block->hash);
}

// Create a new block
Block *createBlock(int index, char *data, char *previousHash, int difficulty) {
    Block *newBlock = (Block *)malloc(sizeof(Block));
    newBlock->index = index;
    strcpy(newBlock->data, data);
    strcpy(newBlock->previousHash, previousHash);
    newBlock->nonce = 0;

    time_t now = time(NULL);
    strcpy(newBlock->timestamp, ctime(&now));

    proofOfWork(newBlock, difficulty);
    newBlock->next = NULL;
    return newBlock;
}

// Print a block’s details
void printBlock(Block *block) {
    printf("\n---- Block %d ----\n", block->index);
    printf("Timestamp: %s", block->timestamp);
    printf("Data: %s\n", block->data);
    printf("Previous Hash: %s\n", block->previousHash);
    printf("Hash: %s\n", block->hash);
    printf("Nonce: %d\n", block->nonce);
}

// Demonstrate how difficulty affects mining
void difficultyTest() {
    Block temp;
    temp.index = 999; // Dummy index
    strcpy(temp.data, "Difficulty Test");
    strcpy(temp.previousHash, "0");
    temp.nonce = 0;
    time_t now = time(NULL);
    strcpy(temp.timestamp, ctime(&now));

    for (int difficulty = 3; difficulty <= 5; difficulty++) {
        temp.nonce = 0;
        clock_t start = clock();
        proofOfWork(&temp, difficulty);
        clock_t end = clock();

        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("⏱ Difficulty %d took %.2f seconds\n", difficulty, timeTaken);
    }
}

int main() {
    printf("🚀 Blockchain Simulation in C\n");

    // Genesis block
    Block *genesis = createBlock(0, "Genesis Block", "0", 4);
    printBlock(genesis);

    // Next block
    Block *block1 = createBlock(1, "Transaction: Kenny -> Colette", genesis->hash, 4);
    printBlock(block1);

    // Another block
    Block *block2 = createBlock(2, "Transaction: Colette -> Muzira", block1->hash, 4);
    printBlock(block2);

    // Difficulty impact test
    printf("\n=== Difficulty Impact Test ===\n");
    difficultyTest();

    // Free memory
    free(genesis);
    free(block1);
    free(block2);

    return 0;
}
