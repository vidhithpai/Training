#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BUSES 100
#define MAX_ROUTE_LENGTH 100

typedef struct 
{
    char bus_id[20];
    double latitude;
    double longitude;
    time_t timestamp;
    char route[MAX_ROUTE_LENGTH];
} Bus;

Bus buses[MAX_BUSES];
int bus_count = 0;

void update_bus_location(const char* bus_id, double latitude, double longitude, const char* route) 
{
    for (int i=0;i<bus_count;i++) 
    {
        if (strcmp(buses[i].bus_id, bus_id) == 0) 
        {
            buses[i].latitude = latitude;
            buses[i].longitude = longitude;
            buses[i].timestamp = time(NULL);
            strcpy(buses[i].route, route);
            printf("Updated location for bus %s\n", bus_id);
            return;
        }
    }
    if (bus_count < MAX_BUSES) 
    {
        strcpy(buses[bus_count].bus_id, bus_id);
        buses[bus_count].latitude = latitude;
        buses[bus_count].longitude = longitude;
        buses[bus_count].timestamp = time(NULL);
        strcpy(buses[bus_count].route, route);
        bus_count++;
        printf("Added new bus %s\n", bus_id);
    } else 
    {
        printf("Bus limit reached. Cannot add more buses.\n");
    }
}
double calculate_estimated_arrival_time(double latitude, double longitude) 
{
    double distance_to_destination = 10.0;
    double speed_kmh = 40.0;
    double time_hours = distance_to_destination / speed_kmh;
    return time_hours * 60;
}
void display_bus_info() 
{
    printf("\nCurrent Bus Locations and Estimated Arrival Times:\n");
    for (int i=0;i<bus_count;i++) {
        double eta = calculate_estimated_arrival_time(buses[i].latitude, buses[i].longitude);
        printf("Bus ID: %s, Location: (%.6f, %.6f), Last Update: %s, Estimated Arrival Time: %.2f minutes\n",
               buses[i].bus_id, buses[i].latitude, buses[i].longitude,
               ctime(&buses[i].timestamp), eta);
    }
}

int main() {
    int choice;
    char bus_id[20];
    double latitude, longitude;
    char route[MAX_ROUTE_LENGTH];

    while (1) {
        printf("\nBus Tracking System Menu:\n");
        printf("1. Update Bus Location\n");
        printf("2. Display Bus Information\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Bus ID: ");
                scanf("%s", bus_id);
                printf("Enter Latitude: ");
                scanf("%lf", &latitude);
                printf("Enter Longitude: ");
                scanf("%lf", &longitude);
                printf("Enter Route: ");
                scanf("%s", route);
                update_bus_location(bus_id, latitude, longitude, route);
                break;
            case 2:
                display_bus_info();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}