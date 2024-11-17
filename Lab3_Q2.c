#include <stdio.h>

// Array of transactions
int transactions [] = {200, -150, -500, -400, -50, -200, 300};
// Array to store unprocessed transactions
int tobeprocessed[100];
// Initial balance
int balance = 1000;
// Counter for unprocessed transactions
int unprocessed_count = 0;

int main() {
    // Loop through each transaction
    for (int i = 0; i < 7; i++) {
        int transaction = transactions[i];

        // Check if balance is zero or negative
        if (balance <= 0) {
            printf("\nBalance is Zero; no further transactions will be processed\n");
            break;
        }

        // Check if transaction would result in negative balance
        if ((transactions[i] + balance) < 0) {
            printf("\nInvalid Transaction");
            // Add to unprocessed transactions
            tobeprocessed[unprocessed_count] = transaction;
            unprocessed_count++;
            continue;
        }

        // Update balance
        balance = balance + transactions[i];
        printf("\n%d", balance);
    }

    // Print final balance
    printf("\n\nFinal Balance: %d\n\nTo Be Processed:", balance);

    // Print unprocessed transactions
    for (int j = 0; j < unprocessed_count; j++) {
        printf("\n%d", tobeprocessed[j]);
    }
}
