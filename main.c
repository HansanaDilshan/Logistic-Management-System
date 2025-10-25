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


int main() {
    printf("\n========================================\n");
    printf("   LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("Initializing system...\n");

    initializeSystem();

    printf("System ready! Starting main menu...\n");

    int choice;
    do {
        displayMainMenu();
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\n>>> Navigating to City Management...\n");
                cityManagement();
                break;
            case 2:
                printf("\n>>> Navigating to Distance Management...\n");
                distanceManagement();
                break;
            case 3:
                printf("\n>>> Navigating to Vehicle Management...\n");
                vehicleManagement();
                break;
            case 4:
                printf("\n>>> Navigating to Delivery Request...\n");
                deliveryRequest();
                break;
            case 5:
                printf("\n>>> Navigating to Performance Reports...\n");
                performanceReports();
                break;
            case 6:
                printf("\n>>> Saving system data...\n");
                saveData();
                break;
            case 7:
                printf("\n>>> Saving data and exiting system...\n");
                saveData();
                printf("Thank you for using Logistics Management System!\n");
                break;
            default:
                printf("Error: Invalid choice! Please enter a number between 1-7.\n");
        }
    } while(choice != 7);

    return 0;
}


void initializeSystem() {
    printf("\n--- SYSTEM INITIALIZATION ---\n");

    printf("Initializing vehicle types...\n");

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

    printf("✓ Vehicle types initialized: Van, Truck, Lorry\n");

    printf("Initializing default cities...\n");

    strcpy(cities[0], "Colombo");
    strcpy(cities[1], "Kandy");
    strcpy(cities[2], "Galle");
    strcpy(cities[3], "Jaffna");
    strcpy(cities[4], "Matara");
    strcpy(cities[5], "Anuradhapura");
    city_count = 6;

    printf("✓ Cities initialized: %d cities loaded\n", city_count);

    printf("Initializing distance matrix...\n");

    for(int i = 0; i < MAX_CITIES; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
            distances[i][j] = 0;
        }
    }

    distances[0][1] = distances[1][0] = 120;
    distances[0][2] = distances[2][0] = 115;
    distances[0][3] = distances[3][0] = 400;
    distances[0][4] = distances[4][0] = 150;
    distances[0][5] = distances[5][0] = 200;

    distances[1][2] = distances[2][1] = 200;
    distances[1][3] = distances[3][1] = 350;
    distances[1][4] = distances[4][1] = 250;
    distances[1][5] = distances[5][1] = 120;

    distances[2][4] = distances[4][2] = 40;
    distances[2][5] = distances[5][2] = 280;

    distances[3][5] = distances[5][3] = 250;

    printf("✓ Distance matrix initialized: %dx%d grid\n", MAX_CITIES, MAX_CITIES);

    printf("Initializing delivery system...\n");
    delivery_count = 0;

    for(int i = 0; i < MAX_DELIVERIES; i++) {
        deliveries[i].id = 0;
        deliveries[i].completed = 0;
    }

    printf("✓ Delivery system ready for %d records\n", MAX_DELIVERIES);

    printf("\n--- SYSTEM STATUS ---\n");
    printf("• Data Structures: READY\n");
    printf("• Vehicle Types: %d initialized\n", 3);
    printf("• Cities: %d/%d loaded\n", city_count, MAX_CITIES);
    printf("• Distance Matrix: %dx%d initialized\n", MAX_CITIES, MAX_CITIES);
    printf("• Delivery Capacity: %d records\n", MAX_DELIVERIES);
    printf("• Current Deliveries: %d\n", delivery_count);
    printf("• Fuel Price: LKR %.2f per liter\n", FUEL_PRICE);
    printf("----------------------------------------\n");
    printf("System initialization completed successfully!\n");
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
    printf("7. Exit System\n");
    printf("========================================\n");
}

void cityManagement() {
    printf("\n--- CITY MANAGEMENT MODULE ---\n");
    printf("Current cities in system: %d\n\n", city_count);

    printf("%-4s %-20s %s\n", "No.", "City Name", "Status");
    printf("----------------------------------------\n");
    for(int i = 0; i < city_count; i++) {
        printf("%-4d %-20s %s\n", i, cities[i], "Active");
    }

    printf("\nModule Features:\n");
    printf("• Add new cities (Capacity: %d/%d)\n", city_count, MAX_CITIES);
    printf("• Rename existing cities\n");
    printf("• Remove cities from system\n");
    printf("• Display city information\n");
    printf("\nFeature implementation: IN PROGRESS\n");
}

void distanceManagement() {
    printf("\n--- DISTANCE MANAGEMENT MODULE ---\n");
    printf("Distance Matrix Overview:\n\n");

    printf("%-15s", "Cities");
    for(int i = 0; i < city_count && i < 5; i++) {
        printf("%-10s", cities[i]);
    }
    printf("\n");

    for(int i = 0; i < city_count && i < 5; i++) {
        printf("%-15s", cities[i]);
        for(int j = 0; j < city_count && j < 5; j++) {
            printf("%-10.0f", distances[i][j]);
        }
        printf("\n");
    }

    printf("\nModule Features:\n");
    printf("• Input/Edit distances between cities\n");
    printf("• Display complete distance table\n");
    printf("• Automatic symmetrical distance updates\n");
    printf("\nFeature implementation: IN PROGRESS\n");
}

void vehicleManagement() {
    printf("\n--- VEHICLE MANAGEMENT MODULE ---\n");
    printf("Available Vehicle Types:\n\n");

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

    printf("\nVehicle Specifications:\n");
    printf("• Van: Light deliveries, high efficiency\n");
    printf("• Truck: Medium capacity, balanced performance\n");
    printf("• Lorry: Heavy cargo, maximum capacity\n");
    printf("\nFeature implementation: READY\n");
}

void deliveryRequest() {
    printf("\n--- DELIVERY REQUEST MODULE ---\n");
    printf("Delivery System Status:\n");
    printf("• Maximum Capacity: %d deliveries\n", MAX_DELIVERIES);
    printf("• Current Deliveries: %d records\n", delivery_count);
    printf("• Available Capacity: %d deliveries\n", MAX_DELIVERIES - delivery_count);

    printf("\nDelivery Process Flow:\n");
    printf("1. Select source and destination cities\n");
    printf("2. Enter package weight\n");
    printf("3. Choose appropriate vehicle type\n");
    printf("4. Calculate optimal route and costs\n");
    printf("5. Confirm and record delivery\n");

    printf("\nCost Calculation Components:\n");
    printf("• Base delivery cost with weight factor\n");
    printf("• Fuel consumption and cost calculation\n");
    printf("• Operational costs and profit margin\n");
    printf("• Final customer charge\n");
    printf("\nFeature implementation: IN PROGRESS\n");
}

void performanceReports() {
    printf("\n--- PERFORMANCE REPORTS MODULE ---\n");
    printf("Reporting Capabilities:\n\n");

    printf("Delivery Metrics:\n");
    printf("• Total deliveries completed\n");
    printf("• Total distance covered\n");
    printf("• Average delivery time\n");
    printf("• Total revenue and profit\n");
    printf("• Longest and shortest routes\n");

    printf("\nCurrent Statistics:\n");
    printf("• Completed Deliveries: %d\n", delivery_count);
    printf("• System Utilization: %.1f%%\n", (delivery_count * 100.0) / MAX_DELIVERIES);
    printf("• Available Reports: Basic metrics ready\n");

    printf("\nFeature implementation: IN PROGRESS\n");
}

void saveData() {
    printf("\n--- DATA PERSISTENCE MODULE ---\n");
    printf("File Storage System:\n\n");

    printf("Data Files to be Created:\n");
    printf("• routes.txt - City list and distance matrix\n");
    printf("• deliveries.txt - Delivery history and costs\n");
    printf("• system_config.txt - Vehicle specifications and settings\n");

    printf("\nStorage Status:\n");
    printf("• Cities data: Ready to save (%d cities)\n", city_count);
    printf("• Distance matrix: Ready to save\n");
    printf("• Vehicle data: Ready to save (%d types)\n", 3);
    printf("• Delivery records: Ready to save (%d records)\n", delivery_count);

    printf("\nFile Operations:\n");
    printf("• Automatic load on program start\n");
    printf("• Automatic save on program exit\n");
    printf("• Manual save option available\n");
    printf("\nFeature implementation: IN PROGRESS\n");
}

void loadData() {

    printf("Data loading system ready for implementation.\n");
}
