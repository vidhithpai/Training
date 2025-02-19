#include <stdio.h>

#define totalLines 1000       
#define initialDebt 0.1 
#define rateReduction 0.5      
#define simulation 50             

int main() {
    double totalDebt = totalLines * initialDebt; 
    int i;

    printf("Iteration \t Technical Debt\n");
    
    for (i = 1; i <= simulation; i++) {
        printf("%d \t\t\t %.2f\n", i, totalDebt);
        totalDebt -= totalDebt * rateReduction; 
        
        
        if (totalDebt < 0.01) {
            printf("Technical debt is almost eliminated.\n");
            break;
        }
    }
    return 0;
}
