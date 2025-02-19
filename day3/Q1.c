#include <stdio.h>
#include <stdlib.h>

#define maxUser  1000
#define maxSimulation 1500
 
void simulatePlatform(int currentUsers) {
    if (currentUsers > maxUser ) {
        printf("Error: Platform has crashed due to exceeding maximum concurrent users!\n");
        exit(0);
    } else {
        printf("Platform is running smoothly with %d concurrent users.\n", currentUsers);
    }
}

int main() {
    for(int currentUsers = 0; currentUsers < maxSimulation; currentUsers += 100) {
        simulatePlatform(currentUsers);
    }
    return 0;
}