#include <stdio.h>

int transactions [] = {200, -150, -500, -400, -50, -200, 300};
int tobeprocessed[100];
int balance = 1000;
int unprocessed_count = 0;


int main() {
    for (int i=0;i<7;i++) {

        int transaction = transactions[i];

        if (balance <= 0) {
            printf("\nBalance is Zero; no further transactions will be processed\n");
            break;
        }
        
         if ((transactions[i]+balance)< 0){
            printf("\nInvalid Transaction");
            tobeprocessed[unprocessed_count] = transaction;
            unprocessed_count++;
            continue;
        }

        balance = balance + transactions[i];
        printf("\n%d",balance);

    }
    printf("\n\nFinal Balance: %d\n\nTo Be Processed:",balance);
    
    for (int j=0;j<unprocessed_count;j++) {
        printf("\n%d",tobeprocessed[j]);
    }
}