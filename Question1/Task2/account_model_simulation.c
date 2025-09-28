#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    float balance;
} Account;

void transferFunds(Account *sender, Account *receiver, float amount) {
    if (amount <= 0) {
        printf("❌ Invalid transaction: Amount must be greater than 0.\n");
        return;
    }
    if (sender->balance < amount) {
        printf("❌ Transaction failed: %s has insufficient funds.\n", sender->name);
        return;
    }
    sender->balance -= amount;
    receiver->balance += amount;
    printf("✅ Transaction successful: %.2f transferred from %s to %s.\n",
           amount, sender->name, receiver->name);
}

void displayAccounts(Account accounts[], int size) {
    printf("\n---- Account Balances ----\n");
    for (int i = 0; i < size; i++) {
        printf("%s: %.2f\n", accounts[i].name, accounts[i].balance);
    }
    printf("--------------------------\n");
}

int main() {
    Account accounts[3] = {
        {"Kenny", 150.0},
        {"Colette", 80.0},
        {"Muzira", 200.0}
    };

    int n = 3;

    displayAccounts(accounts, n);
    transferFunds(&accounts[0], &accounts[1], 50.0);
    displayAccounts(accounts, n);

    transferFunds(&accounts[1], &accounts[2], 70.0);
    displayAccounts(accounts, n);

    transferFunds(&accounts[2], &accounts[0], 500.0);
    displayAccounts(accounts, n);

    return 0;
}
