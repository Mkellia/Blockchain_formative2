Task 2: Simulating Account/Balance-Based Transactions in C
Implementation Process
The program simulates the account/balance model, like Ethereum does.
An Account struct stores:
name → user’s name
balance → the amount of funds
Three accounts are initialized: Kenny, Colette, and Muzira.
A function transferFunds(sender, receiver, amount):
Checks if the sender has enough balance.
Deducts the amount from the sender.
Adds the amount to the receiver.
Prints whether the transaction was successful or failed.
displayAccounts prints all account balances before and after transactions.
Output of the transaction
bash-3.2$ ./account_model_simulation 

---- Account Balances ----
Kenny: 150.00
Colette: 80.00
Muzira: 200.00
--------------------------
✅ Transaction successful: 50.00 transferred from Kenny to Colette.

---- Account Balances ----
Kenny: 100.00
Colette: 130.00
Muzira: 200.00
--------------------------
✅ Transaction successful: 70.00 transferred from Colette to Muzira.

---- Account Balances ----
Kenny: 100.00
Colette: 60.00
Muzira: 270.00
--------------------------
❌ Transaction failed: Muzira has insufficient funds.

---- Account Balances ----
Kenny: 100.00
Colette: 60.00
Muzira: 270.00
--------------------------
Challenges
Preventing transactions if the sender does not have enough balance.
Ensuring that balances update correctly for both the sender and the receiver.
Summary
The account/balance simulation successfully models Ethereum-style transactions: balances are updated directly, transactions are validated, and the program clearly shows the result of each transfer.
