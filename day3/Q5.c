#include <stdio.h>

#define microservices 5  
#define latency 0.1 

int main() {
    double totalLatency = 0.0;
    int i, j;
    
    printf("Latency of each each microservice %.1f seconds.\n\n", latency);
    
    printf("Microservice Communication Latencies:\n");
    for (i = 0; i < microservices; i++) {
        for (j = 0; j < microservices; j++) {
            if (i != j) {
                printf("Microservice %d -> Microservice %d: %.1f sec\n", i+1, j+1, latency);
                totalLatency += latency;
            }
        }
    }
    
    printf("\nTotal communication latency: %.2f seconds\n", totalLatency);
    return 0;
}
