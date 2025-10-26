#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310.0

typedef struct {
    char type[10];
    int capacity;
    float rate_per_km;
    float avg_speed;
    float fuel_efficiency;
} Vehicle;

typedef struct {
    int id;
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    float weight;
    char vehicle_type[10];
    float distance;
    float base_cost;
    float fuel_used;
    float fuel_cost;
    float operational_cost;
    float profit;
    float customer_charge;
    float delivery_time;
    int completed;
} Delivery;

char cities[MAX_CITIES][MAX_NAME_LENGTH];
float distances[MAX_CITIES][MAX_CITIES];
Delivery deliveries[MAX_DELIVERIES];
Vehicle vehicles[3];

int city_count = 0;
int delivery_count = 0;

void initializeSystem();
void displayMainMenu();
void cityManagement();
void distanceManagement();
void vehicleManagement();
void deliveryRequest();
void performanceReports();
void saveData();
void loadData();
void addCity();
void renameCity();
void removeCity();
void displayCities();

int main() {
    initializeSystem();

    int choice;
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                cityManagement();
                break;
            case 2:
                distanceManagement();
                break;
            case 3:
                vehicleManagement();
                break;
            case 4:
                deliveryRequest();
                break;
            case 5:
                performanceReports();
                break;
            case 6:
                saveData();
                break;
            case 7:
                saveData();
                printf("Thank you for using Logistics Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 7);

    return 0;
}

void initializeSystem() {
    strcpy(vehicles[0].type, "Van");
    vehicles[0].capacity = 1000;
    vehicles[0].rate_per_km = 30.0;
    vehicles[0].avg_speed = 60.0;
    vehicles[0].fuel_efficiency = 12.0;

    strcpy(vehicles[1].type, "Truck");
    vehicles[1].capacity = 5000;
    vehicles[1].rate_per_km = 40.0;
    vehicles[1].avg_speed = 50.0;
    vehicles[1].fuel_efficiency = 6.0;

    strcpy(vehicles[2].type, "Lorry");
    vehicles[2].capacity = 10000;
    vehicles[2].rate_per_km = 80.0;
    vehicles[2].avg_speed = 45.0;
    vehicles[2].fuel_efficiency = 4.0;

    strcpy(cities[0], "Colombo");
    strcpy(cities[1], "Kandy");
    strcpy(cities[2], "Galle");
    strcpy(cities[3], "Jaffna");
    city_count = 4;

    for(int i = 0; i < MAX_CITIES; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
            distances[i][j] = 0;
        }
    }

    distances[0][1] = distances[1][0] = 120;
    distances[0][2] = distances[2][0] = 115;
    distances[0][3] = distances[3][0] = 400;
    distances[1][2] = distances[2][1] = 200;
    distances[1][3] = distances[3][1] = 350;
}

void displayMainMenu() {
    printf("\n========================================\n");
    printf("   LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. City Management\n");
    printf("2. Distance Management\n");
    printf("3. Vehicle Management\n");
    printf("4. Delivery Request\n");
    printf("5. Performance Reports\n");
    printf("6. Save Data\n");
    printf("7. Exit\n");
    printf("========================================\n");
}

void cityManagement() {
    int choice;
    do {
        printf("\n--- CITY MANAGEMENT ---\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Display Cities\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addCity();
                break;
            case 2:
                renameCity();
                break;
            case 3:
                removeCity();
                break;
            case 4:
                displayCities();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
}

void addCity() {
    if(city_count >= MAX_CITIES) {
        printf("Maximum number of cities reached!\n");
        return;
    }

    char cityName[MAX_NAME_LENGTH];
    printf("Enter city name: ");
    scanf(" %[^\n]", cityName);

    for(int i = 0; i < city_count; i++) {
        if(strcmp(cities[i], cityName) == 0) {
            printf("City '%s' already exists!\n", cityName);
            return;
        }
    }

    strcpy(cities[city_count], cityName);
    city_count++;
    printf("City '%s' added successfully!\n", cityName);
}

void renameCity() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    displayCities();
    int index;
    printf("Enter city index to rename: ");
    scanf("%d", &index);

    if(index < 0 || index >= city_count) {
        printf("Invalid city index!\n");
        return;
    }

    char newName[MAX_NAME_LENGTH];
    printf("Enter new name for %s: ", cities[index]);
    scanf(" %[^\n]", newName);

    for(int i = 0; i < city_count; i++) {
        if(i != index && strcmp(cities[i], newName) == 0) {
            printf("City '%s' already exists!\n", newName);
            return;
        }
    }

    printf("City '%s' renamed to '%s'\n", cities[index], newName);
    strcpy(cities[index], newName);
}

void removeCity() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    displayCities();
    int index;
    printf("Enter city index to remove: ");
    scanf("%d", &index);

    if(index < 0 || index >= city_count) {
        printf("Invalid city index!\n");
        return;
    }

    printf("City '%s' removed successfully!\n", cities[index]);

    for(int i = index; i < city_count - 1; i++) {
        strcpy(cities[i], cities[i + 1]);
    }
    city_count--;

    for(int i = index; i < city_count; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
            distances[i][j] = distances[i + 1][j];
        }
    }
    for(int j = index; j < city_count; j++) {
        for(int i = 0; i < MAX_CITIES; i++) {
            distances[i][j] = distances[i][j + 1];
        }
    }
}

void displayCities() {
    printf("\n--- CITIES LIST ---\n");
    if(city_count == 0) {
        printf("No cities available.\n");
        return;
    }

    for(int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i, cities[i]);
    }
}

void distanceManagement() {
    printf("\n--- DISTANCE MANAGEMENT ---\n");
    printf("Feature coming soon...\n");
}

void vehicleManagement() {
    printf("\n--- VEHICLE MANAGEMENT ---\n");
    printf("%-10s %-12s %-15s %-12s %-15s\n",
           "Type", "Capacity(kg)", "Rate/km(LKR)", "Speed(km/h)", "Efficiency(km/l)");
    printf("------------------------------------------------------------------------\n");

    for(int i = 0; i < 3; i++) {
        printf("%-10s %-12d %-15.2f %-12.2f %-15.2f\n",
               vehicles[i].type,
               vehicles[i].capacity,
               vehicles[i].rate_per_km,
               vehicles[i].avg_speed,
               vehicles[i].fuel_efficiency);
    }
}

void deliveryRequest() {
    printf("\n--- DELIVERY REQUEST ---\n");
    printf("Feature coming soon...\n");
}

void performanceReports() {
    printf("\n--- PERFORMANCE REPORTS ---\n");
    printf("Feature coming soon...\n");
}

void saveData() {
    printf("\n--- SAVE DATA ---\n");
    printf("Feature coming soon...\n");
}

void loadData() {
}
