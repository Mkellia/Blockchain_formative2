#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

typedef struct {
    int index;
    char timestamp[100];
    char data[256];
    char previousHash[65];
    char hash[65];
    int nonce;
} Block;

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

void proofOfWork(Block *block, int difficulty) {
    char prefix[65];
    memset(prefix, '0', difficulty);
    prefix[difficulty] = '\0';

    do {
        block->nonce++;
        calculateHash(block, block->hash);
    } while (strncmp(block->hash, prefix, difficulty) != 0);
}

int main() {
    Block block;
    block.index = 1;
    strcpy(block.data, "Difficulty Test");
    strcpy(block.previousHash, "0");
    block.nonce = 0;

    time_t now = time(NULL);
    strcpy(block.timestamp, ctime(&now));

    for (int difficulty = 3; difficulty <= 5; difficulty++) {
        block.nonce = 0;

        clock_t start = clock();
        proofOfWork(&block, difficulty);
        clock_t end = clock();

        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Difficulty: %d | Hash: %s | Time: %.2f seconds\n",
               difficulty, block.hash, timeTaken);
    }

    return 0;
}
