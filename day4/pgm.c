#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define maxLineLength 256
#define maxEmails 5
#define maxSubjectLength 100
#define maxBodyLength 256

typedef struct {
    char subject[maxSubjectLength];
    char body[maxBodyLength];
    int effectiveness; 
} PhishingEmail;

int evaluatePasswordStrength(const char *password) {
    int length = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    if (length >= 12 && hasUpper && hasLower && hasDigit && hasSpecial) return 3; 
    if (length >= 8 && ((hasUpper && hasLower) || (hasLower && hasDigit))) return 2; 
    return 1; 
}

void simulationbreach() {
    FILE *file = fopen("cerdentials.txt", "r");
    if (!file) {
        perror("Error opening credentials file");
        return;
    }

    char line[maxLineLength];
    printf("Compromised Data:\n");
    while (fgets(line, sizeof(line), file)) {
        char username[50], password[50], businessInfo[100];
        sscanf(line, "%49[^,], %49[^,], %99[^\n]", username, password, businessInfo);
        printf("Username: %s, Password: %s, Business Info: %s\n", username, password, businessInfo);
    }
    fclose(file);
}

void checkPasswordStrength() {
    FILE *file = fopen("cerdentials.txt", "r");
    if (!file) {
        perror("Error opening credentials file");
        return;
    }

    char line[maxLineLength];
    printf("\nPassword Strength Evaluation:\n");
    while (fgets(line, sizeof(line), file)) {
        char username[50], password[50], businessInfo[100];
        sscanf(line, "%49[^,], %49[^,], %99[^\n]", username, password, businessInfo);
        int strength = evaluatePasswordStrength(password);
        printf("Username: %s, Password Strength: %s\n", username, 
               strength == 3 ? "Strong" : strength == 2 ? "Medium" : "Weak");
    }
    fclose(file);
}

void generatePhishingEmail(PhishingEmail emails[]) {
    strcpy(emails[0].subject, "Urgent: Your account has been compromised!");
    strcpy(emails[0].body, "Dear user, your account has been compromised. Click here to reset your password immediately.");
    emails[0].effectiveness = 9;

    strcpy(emails[1].subject, "Congratulations! You've won a gift card!");
    strcpy(emails[1].body, "Dear winner, you have won a $100 gift card! Click to claim your prize.");
    emails[1].effectiveness = 8;

    strcpy(emails[2].subject, "Action Required: Verify your account!");
    strcpy(emails[2].body, "Dear user, please verify your account to avoid suspension. Click here to verify.");
    emails[2].effectiveness = 7;

    strcpy(emails[3].subject, "Limited Time Offer: Get 50% off!");
    strcpy(emails[3].body, "Dear customer, enjoy a 50% discount on your next purchase. Click here to redeem.");
    emails[3].effectiveness = 6;

    strcpy(emails[4].subject, "Important: Update your payment information.");
    strcpy(emails[4].body, "Dear user, please update your payment information to continue using our services.");
    emails[4].effectiveness = 5;
}

void evalulatePhishingEmail(PhishingEmail emails[], int count) {
    FILE *file = fopen("phishingEmails.txt", "w");
    if (!file) {
        perror("Error opening phishing emails file");
        return;
    }
    
    fprintf(file, "Generated Phishing Emails and Their Effectiveness:\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "Email %d:\n", i + 1);
        fprintf(file, "Subject: %s\n", emails[i].subject);
        fprintf(file, "Body: %s\n", emails[i].body);
        fprintf(file, "Effectiveness Score: %d/10\n", emails[i].effectiveness);
        fprintf(file, "-----------------------------------\n");
    }
    
    fclose(file);
    printf("Phishing email data has been stored in phishingEmails.txt\n");
}

void analyzeNetworkVulnerabilities() {
    FILE *file = fopen("networkDevices.txt", "r");
    if (!file) {
        perror("Error opening network devices file");
        return;
    }

    char line[maxLineLength];
    printf("\nIdentified Network Vulnerabilities:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int main() {
    int choice;
    do {
        printf("\nSelect an option:\n");
        printf("1. Simulate Breach\n");
        printf("2. Check Password Strength\n");
        printf("3. Generate and Evaluate Phishing Emails\n");
        printf("4. Analyze Network Vulnerabilities\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                simulationbreach();
                break;
            case 2:
                checkPasswordStrength();
                break;
            case 3: {
                PhishingEmail emails[maxEmails]; 
                generatePhishingEmail(emails);
                evalulatePhishingEmail(emails, maxEmails);
                break;
            }
            case 4:
                analyzeNetworkVulnerabilities();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
