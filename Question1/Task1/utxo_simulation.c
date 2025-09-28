#include <stdio.h>
#include <string.h>

#define MAX_UTXOS 20
#define ADDR_LEN  20

typedef struct {
    int txid;
    char owner[ADDR_LEN];
    double amount;
    int spent;
} UTXO;

UTXO utxos[MAX_UTXOS];
int utxo_count = 0;
int next_txid = 1;

int add_utxo(const char *owner, double amount) {
    utxos[utxo_count].txid = next_txid++;
    strcpy(utxos[utxo_count].owner, owner);
    utxos[utxo_count].amount = amount;
    utxos[utxo_count].spent = 0;
    utxo_count++;
    return utxos[utxo_count - 1].txid;
}

void print_utxos() {
    printf("\nUnspent UTXOs:\n");
    printf("TXID   OWNER        AMOUNT\n");
    for (int i = 0; i < utxo_count; i++) {
        if (!utxos[i].spent) {
            printf("%-6d %-10s %.2f\n", utxos[i].txid, utxos[i].owner, utxos[i].amount);
        }
    }
}

int find_unspent(const char *owner, double amount, int *input_index) {
    for (int i = 0; i < utxo_count; i++) {
        if (!utxos[i].spent && strcmp(utxos[i].owner, owner) == 0 && utxos[i].amount >= amount) {
            *input_index = i;
            return 1;
        }
    }
    return 0;
}

void transaction(const char *sender, const char *receiver, double amount) {
    int input_index;
    if (!find_unspent(sender, amount, &input_index)) {
        printf("\nTransaction failed: %s has insufficient funds\n", sender);
        return;
    }

    UTXO input = utxos[input_index];
    utxos[input_index].spent = 1;

    add_utxo(receiver, amount);
    double change = input.amount - amount;
    if (change > 0) {
        add_utxo(sender, change);
    }

    printf("\nTransaction: %s -> %s (%.2f)\n", sender, receiver, amount);
    print_utxos();
}

int main() {
    printf("UTXO Simulation (Simplified)\n");

    add_utxo("Kellia", 50.0);
    add_utxo("Saiba", 30.0);

    print_utxos();

    transaction("Kellia", "Saiba", 20.0);
    transaction("Saiba", "Kellia", 15.0);

    return 0;
}
