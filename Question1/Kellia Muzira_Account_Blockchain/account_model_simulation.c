#include <stdio.h>
#include <string.h>

// Define a structure to represent a user account
typedef struct {
    char name[50];   // Account holder's name
    float balance;   // Current balance of the account
} Account;

// Function to transfer funds between two accounts
void transferFunds(Account *sender, Account *receiver, float amount) {
    if (amount <= 0) {   // Validate transaction amount
        printf("❌ Invalid transaction: Amount must be greater than 0.\n");
        return;
    }
    if (sender->balance < amount) {   // Check if sender has enough balance
        printf("❌ Transaction failed: %s has insufficient funds.\n", sender->name);
        return;
    }

    sender->balance -= amount;        // Deduct amount from sender
    receiver->balance += amount;      // Add amount to receiver
    printf("✅ Transaction successful: %.2f transferred from %s to %s.\n",
           amount, sender->name, receiver->name);
}

// Function to display all account balances
void displayAccounts(Account accounts[], int size) {
    printf("\n---- Account Balances ----\n");
    for (int i = 0; i < size; i++) {
        printf("%s: %.2f\n", accounts[i].name, accounts[i].balance); // Print each account
    }
    printf("--------------------------\n");
}

// Main function
int main() {
    // Initialize 3 accounts with different balances
    Account accounts[3] = {
        {"Kenny", 150.0},
        {"Colette", 80.0},
        {"Muzira", 200.0}
    };

    int n = 3; // Number of accounts

    displayAccounts(accounts, n);  // Show initial balances

    transferFunds(&accounts[0], &accounts[1], 50.0); // Kenny sends 50 to Colette
    displayAccounts(accounts, n);                     // Display balances after transaction

    transferFunds(&accounts[1], &accounts[2], 70.0); // Colette sends 70 to Muzira
    displayAccounts(accounts, n);                     // Display balances after transaction

    transferFunds(&accounts[2], &accounts[0], 500.0); // Muzira tries to send 500 to Kenny (fails)
    displayAccounts(accounts, n);                     // Display balances after failed transaction

    return 0;
}
