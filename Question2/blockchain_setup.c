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

int main() {
    Block genesis;
    genesis.index = 0;
    strcpy(genesis.data, "Genesis Block");
    strcpy(genesis.previousHash, "0");
    genesis.nonce = 0;

    time_t now = time(NULL);
    strcpy(genesis.timestamp, ctime(&now));

    calculateHash(&genesis, genesis.hash);

    printf("Genesis Block:\n");
    printf("Index: %d\n", genesis.index);
    printf("Timestamp: %s", genesis.timestamp);
    printf("Data: %s\n", genesis.data);
    printf("Previous Hash: %s\n", genesis.previousHash);
    printf("Hash: %s\n", genesis.hash);

    return 0;
}
