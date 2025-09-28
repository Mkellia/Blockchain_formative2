#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

typedef struct Block {
    int index;
    char timestamp[100];
    char data[256];
    char previousHash[65];
    char hash[65];
    int nonce;
    struct Block *next;
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

Block *createBlock(int index, char *data, char *previousHash, int difficulty) {
    Block *newBlock = (Block *)malloc(sizeof(Block));
    newBlock->index = index;
    strcpy(newBlock->data, data);
    strcpy(newBlock->previousHash, previousHash);
    newBlock->nonce = 0;

    time_t now = time(NULL);
    strcpy(newBlock->timestamp, ctime(&now));

    proofOfWork(newBlock, difficulty);

    return newBlock;
}

int main() {
    Block *genesis = createBlock(0, "Genesis Block", "0", 4);
    Block *block1 = createBlock(1, "Transaction: Kenny -> Colette", genesis->hash, 4);

    printf("Genesis Hash: %s\n", genesis->hash);
    printf("Block1 Hash: %s\n", block1->hash);

    free(genesis);
    free(block1);

    return 0;
}
