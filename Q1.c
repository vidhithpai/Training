#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxSeat 50
#define maxPassengers 100

typedef struct {
    char name[50];
    int age;
    char contact[15];
    int seatNumber;
} Passenger;

typedef struct {
    char busNumber[20];
    char route[100];
    char time[20];
    int totalSeats;
    int availableSeats;
    Passenger passengers[maxPassengers];
} Bus;

Bus bus;

void busDetails() {
    printf("Enter Bus Number: ");
    scanf("%s", bus.busNumber);
    printf("Enter Route: ");
    scanf(" %[^\n]", bus.route);
    printf("Enter Departure Time: ");
    scanf("%s", bus.time);
    printf("Enter Total Number of Seats: ");
    scanf("%d", &bus.totalSeats);
    bus.availableSeats = bus.totalSeats;
}

void allocateSeat() {
    if (bus.availableSeats <= 0) {
        printf("No seats available!\n");
        return;
    }

    Passenger newPassenger;
    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", newPassenger.name);
    printf("Enter Passenger Age: ");
    scanf("%d", &newPassenger.age);
    printf("Enter Contact Number: ");
    scanf("%s", newPassenger.contact);

    for (int i = 0; i < bus.totalSeats; i++) {
        if (bus.passengers[i].seatNumber == 0) { 
            newPassenger.seatNumber = i + 1; 
            bus.passengers[i] = newPassenger;
            bus.availableSeats--;
            printf("Seat allocated: %d\n", newPassenger.seatNumber);
            return;
        }
    }
}

void displayAllocatedSeats() {
    printf("\nAllocated Seats:\n");
    printf("%-15s %-10s %-10s %-10s\n", "Seat Number", "Name", "Age", "Contact");
    for (int i = 0; i < bus.totalSeats; i++) {
        if (bus.passengers[i].seatNumber != 0) {
            printf("%-15d %-10s %-10d %-10s\n",bus.passengers[i].seatNumber,bus.passengers[i].name,bus.passengers[i].age,bus.passengers[i].contact);
        }
    }
}

void cancelSeat() {
    int seatNumber;
    printf("Enter Seat Number to Cancel: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > bus.totalSeats) {
        printf("Invalid seat number!\n");
        return;
    }
    int loc = seatNumber - 1;
    if (bus.passengers[loc].seatNumber == 0) {
        printf("Seat %d is not allocated!\n", seatNumber);
    } else {
        printf("Seat cancelled\n");
        bus.passengers[loc].seatNumber = 0; 
        bus.availableSeats++;
    }
}

int main() {
    int choice;
    busDetails();

    while(1){
        printf("1. Seat allocation\n");
        printf("2. Display Allocated Seats\n");
        printf("3. Cancel Seat\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                allocateSeat();
                break;
            case 2:
                displayAllocatedSeats();
                break;
            case 3:
                cancelSeat();
                break;
            case 4:
                printf("Exit\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } 

    return 0;
}