#include <stdio.h>
#include <string.h>

#define MAX_UTXOS 20   // Maximum number of UTXOs we can store
#define ADDR_LEN  20   // Maximum length of owner address

// Structure to represent a UTXO
typedef struct {
    int txid;                 // Unique transaction ID
    char owner[ADDR_LEN];     // Owner of the UTXO
    double amount;            // Amount of funds in the UTXO
    int spent;                // Flag to indicate if UTXO has been spent (1 = spent, 0 = unspent)
} UTXO;

UTXO utxos[MAX_UTXOS];       // Array to store all UTXOs
int utxo_count = 0;           // Current count of UTXOs
int next_txid = 1;            // ID to assign to next new UTXO

// Function to add a new UTXO to the list
int add_utxo(const char *owner, double amount) {
    utxos[utxo_count].txid = next_txid++;        // Assign unique transaction ID
    strcpy(utxos[utxo_count].owner, owner);      // Copy owner name to UTXO
    utxos[utxo_count].amount = amount;           // Set UTXO amount
    utxos[utxo_count].spent = 0;                 // Initially, UTXO is unspent
    utxo_count++;                                // Increment total UTXOs
    return utxos[utxo_count - 1].txid;          // Return the txid of the newly added UTXO
}

// Function to print all unspent UTXOs
void print_utxos() {
    printf("\nUnspent UTXOs:\n");
    printf("TXID   OWNER        AMOUNT\n");
    for (int i = 0; i < utxo_count; i++) {
        if (!utxos[i].spent) {                    // Only print unspent UTXOs
            printf("%-6d %-10s %.2f\n", utxos[i].txid, utxos[i].owner, utxos[i].amount);
        }
    }
}

// Function to find an unspent UTXO for a given owner with enough funds
int find_unspent(const char *owner, double amount, int *input_index) {
    for (int i = 0; i < utxo_count; i++) {
        if (!utxos[i].spent && strcmp(utxos[i].owner, owner) == 0 && utxos[i].amount >= amount) {
            *input_index = i;                     // Return the index of the found UTXO
            return 1;                             // Found a suitable UTXO
        }
    }
    return 0;                                     // No suitable UTXO found
}

// Function to perform a transaction
void transaction(const char *sender, const char *receiver, double amount) {
    int input_index;
    if (!find_unspent(sender, amount, &input_index)) {   // Check if sender has enough funds
        printf("\nTransaction failed: %s has insufficient funds\n", sender);
        return;
    }

    UTXO input = utxos[input_index];          // Get the input UTXO
    utxos[input_index].spent = 1;             // Mark the input UTXO as spent

    add_utxo(receiver, amount);               // Create new UTXO for receiver
    double change = input.amount - amount;    // Calculate leftover change
    if (change > 0) {
        add_utxo(sender, change);             // Return change to sender as a new UTXO
    }

    printf("\nTransaction: %s -> %s (%.2f)\n", sender, receiver, amount);
    print_utxos();                            // Print updated UTXO list
}

// Main function
int main() {
    printf("UTXO Simulation (Simplified)\n");

    add_utxo("Kellia", 50.0);  // Initial UTXO for Kellia
    add_utxo("Saiba", 30.0);   // Initial UTXO for Saiba

    print_utxos();              // Print UTXOs before transactions

    transaction("Kellia", "Saiba", 20.0);  // Kellia sends 20 to Saiba
    transaction("Saiba", "Kellia", 15.0);  // Saiba sends 15 back to Kellia

    return 0;
}
