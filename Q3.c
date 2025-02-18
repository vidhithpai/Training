#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct {
    char name[20];
    int age;
    char contact[10];
    char date[11];
    int bustype; 
    float price;
    int iscancel;
} Passenger;

typedef struct {
    char paymentmethod[20];
    float amount;
    char transactionID[20]; 
} Payment;

Passenger tickets[MAX];
Payment payments[MAX];
int count = 0;

float calculatePrice(int bustype) {
    if (bustype == 1) { 
        return 1500.0;
    }
    if (bustype == 0) { 
        return 1000.0;
    }
    return 0.0;
}

void paymentProcess(int ID, int bustype) {
    Payment payment;
    payment.amount = calculatePrice(bustype);
    printf("Amount to be paid is %.2f: ", payment.amount);
    
    printf("\nEnter payment method: ");
    scanf("%19s", payment.paymentmethod);
    printf("Enter transaction ID: ");
    scanf("%19s", payment.transactionID); 

    payments[ID] = payment;
    printf("Payment processed successfully! Transaction ID: %s\n", payment.transactionID);
    printf("Booking Confirmation:\n");
    printf("Passenger Name: %s\n", tickets[ID].name);
    printf("Travel Date: %s\n", tickets[ID].date);
    printf("Ticket Price: %.2f\n", tickets[ID].price);
}

void bookTicket() {
    Passenger booking;
    int bustype;

    printf("Enter passenger name: ");
    scanf("%19s", booking.name); 
    printf("Enter age: ");
    scanf("%d", &booking.age);
    printf("Enter contact number: ");
    scanf("%9s", booking.contact); 
    printf("Enter travel date (DD-MM-YYYY): ");
    scanf("%10s", booking.date);
    printf("Enter bus type (0 for Seater, 1 for Sleeper): ");
    scanf("%d", &bustype);
    
    if (bustype < 0 || bustype > 1) {
        printf("Invalid bus type. Please enter 0 or 1.\n");
        return;
    }

    booking.price = calculatePrice(bustype);
    booking.bustype = bustype; 
    booking.iscancel = 0;

    tickets[count] = booking;
    count++;
    printf("Ticket booked\n");
    paymentProcess(count - 1, bustype); 
}

void cancelBooking(const char *passengerName) {
    for (int i = 0; i < count; i++) {
        if (strcmp(tickets[i].name, passengerName) == 0 && !tickets[i].iscancel) {
            tickets[i].iscancel = 1;
            printf("Booking cancelled successfully!\n");
            return;
        }
    }
    printf("Invalid passenger name.\n");
}

void displayBooking(const char *passengerName) {
    for (int i = 0; i < count; i++) {
        if (strcmp(tickets[i].name, passengerName) == 0) {
            Passenger booking = tickets[i];
            printf("Booking Details:\n");
            printf("Passenger Name: %s\n", booking.name);
            printf("Age: %d\n", booking.age);
            printf("Contact Number: %s\n", booking.contact);
            printf("Travel Date: %s\n", booking.date);
            printf("Bus Type: %s\n", booking.bustype == 0 ? "Seater" : "Sleeper");
            printf("Ticket Price: %.2f\n", booking.price);
            printf("Cancelled: %s\n", booking.iscancel ? "Yes" : "No");
            return;
        }
    }
    printf("Invalid passenger name.\n");
}

int main() {
    int choice;
    char passengerName[50];

    while (1) {
        printf("\nRedbus Ticket Booking System\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Booking\n");
        printf("3. Display Booking\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                printf("Enter passenger name to cancel: ");
                scanf("%49s", passengerName); 
                cancelBooking(passengerName);
                break;
            case 3:
                printf("Enter passenger name to display: ");
                scanf("%49s", passengerName); 
                displayBooking(passengerName);
                break;
            case 4:
                printf("Exit\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}