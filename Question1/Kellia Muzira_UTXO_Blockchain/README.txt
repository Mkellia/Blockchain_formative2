Task 1: Simulating UTXO-Based Transactions in C
Implementation Process
The program simulates the UTXO model, like Bitcoin does.
A UTXO struct has:
id → unique transaction ID
owner → the address of the receiver
amount → the value of the funds
spent → marks if the UTXO has been used


All UTXOs are stored in an array. Each user starts with one or more UTXOs.
To make a transaction:
The sender selects enough UTXOs to cover the payment.
The selected UTXOs are marked as spent.
Two new UTXOs are created:
One for the receiver with the payment amount.
One for the sender with any leftover change.
After each transaction, the program prints all unspent UTXOs so users can see the updated balances.
OUTPUT OF THE CODE
Unspent UTXOs:
TXID   OWNER        AMOUNT
1      Kellia     50.00
2      Saiba      30.00

Transaction: Kellia -> Saiba (20.00)

Unspent UTXOs:
TXID   OWNER        AMOUNT
2      Saiba      30.00
3      Saiba      20.00
4      Kellia     30.00

Transaction: Saiba -> Kellia (15.00)

Unspent UTXOs:
TXID   OWNER        AMOUNT
3      Saiba      20.00
4      Kellia     30.00
5      Kellia     15.00
6      Saiba      15.00

Challenges
Picking the right UTXOs to cover the payment.
Giving back the correct change while updating the unspent UTXO list.
Summary
The UTXO simulation successfully models how Bitcoin tracks balances using spendable outputs, instead of a single account balance.




