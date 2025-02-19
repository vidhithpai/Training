#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define totalTransactions 100
#define failureProbability 0.1

int simulateTransactions(int total, double failure) {
    int failedTransactions = 0;
    for (int i = 0; i < totalTransactions; i++) {
        double randomValue = (double)rand() / RAND_MAX;
        if (randomValue < failureProbability) {
            failedTransactions++;
        }
    }
    return failedTransactions;
}

int main() { 
    srand(time(NULL));
    int failedTransactions = simulateTransactions(totalTransactions, failureProbability);
    printf("Number of failed transactions: %d \n", failedTransactions);
    return 0;
}