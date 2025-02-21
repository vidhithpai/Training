#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define THRESHOLD 100

typedef struct {
    char name[50];
    int heartRate;
    int bloodPressure;
    int oxygenSaturation;
} PatientData;

void collectData(PatientData *p) {
    printf("Enter patient name: ");
    scanf("%s", p->name);
    
    printf("Enter heart rate: ");
    if (scanf("%d", &p->heartRate) != 1 || p->heartRate <= 0) {
        printf("Error: Invalid heart rate input!\n");
        exit(1);
    }
    
    printf("Enter blood pressure: ");
    if (scanf("%d", &p->bloodPressure) != 1 || p->bloodPressure <= 0) {
        printf("Error: Invalid blood pressure input!\n");
        exit(1);
    }
    
    printf("Enter oxygen saturation: ");
    if (scanf("%d", &p->oxygenSaturation) != 1 || p->oxygenSaturation <= 0) {
        printf("Error: Invalid oxygen saturation input!\n");
        exit(1);
    }
}

bool detectAnomaly(PatientData *p) {
    if (p->heartRate > THRESHOLD || p->bloodPressure > THRESHOLD || p->oxygenSaturation < 90) {
        printf("Warning: Anomaly detected in patient %s's data!\n", p->name);
        return true;
    }
    return false;
}

void sendAlert(PatientData *p, bool anomaly) {
    if (anomaly) {
        bool alertSuccess = rand() % 2;
        if (!alertSuccess) {
            printf("Error: Failed to send alert for patient %s to healthcare professionals!\n", p->name);
        } else {
            printf("Alert sent successfully for patient %s!\n", p->name);
        }
    }
}

void encryptData(char *data, int key) {
    if (!data) {
        printf("Error: Null data cannot be encrypted!\n");
        return;
    }
    for (int i = 0; i < strlen(data); i++) {
        data[i] ^= key;
    }
}

void decryptData(char *data, int key) {
    if (!data) {
        printf("Error: Null data cannot be decrypted!\n");
        return;
    }
    for (int i = 0; i < strlen(data); i++) {
        data[i] ^= key;
    }
}

PatientData* allocateMemory(int numPatients) {
    PatientData *patients = (PatientData *)malloc(numPatients * sizeof(PatientData));
    if (!patients) {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    return patients;
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add Patient Data\n");
    printf("2. Detect Anomalies\n");
    printf("3. Encrypt Data\n");
    printf("4. Decrypt Data\n");
    printf("5. Exit\n");
}

int main() {
    srand(time(NULL));
    int choice, numPatients = 0, capacity = 2;
    PatientData *patients = allocateMemory(capacity);
    
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (numPatients == capacity) {
                    capacity *= 2;
                    patients = (PatientData *)realloc(patients, capacity * sizeof(PatientData));
                    if (!patients) {
                        printf("Error: Memory reallocation failed!\n");
                        exit(1);
                    }
                }
                collectData(&patients[numPatients]);
                numPatients++;
                break;
            case 2:
                for (int i = 0; i < numPatients; i++) {
                    if (detectAnomaly(&patients[i])) {
                        sendAlert(&patients[i], true);
                    } else {
                        printf("No anomalies detected for patient %s.\n", patients[i].name);
                    }
                }
                break;
            case 3:
                for (int i = 0; i < numPatients; i++) {
                    encryptData(patients[i].name, 5);
                    printf("Encrypted name for patient %s: %s\n", patients[i].name, patients[i].name);
                }
                break;
            case 4:
                for (int i = 0; i < numPatients; i++) {
                    decryptData(patients[i].name, 5);
                    printf("Decrypted name for patient %s: %s\n", patients[i].name, patients[i].name);
                }
                break;
            case 5:
                free(patients);
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
