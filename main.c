#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310.0

// Vehicle types structure
typedef struct {
    char type[10];
    int capacity;
    float rate_per_km;
    float avg_speed;
    float fuel_efficiency;
} Vehicle;

// Delivery record structure
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

// Global arrays
char cities[MAX_CITIES][MAX_NAME_LENGTH];
float distances[MAX_CITIES][MAX_CITIES];
Delivery deliveries[MAX_DELIVERIES];
Vehicle vehicles[3];

// Global counters
int city_count = 0;
int delivery_count = 0;

// Function prototypes
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
    printf("=== Logistics Management System ===\n");
    printf("Initializing system...\n");

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
                printf("Thank you for using Logistics Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 7);

    return 0;
}

void initializeSystem() {
    printf("Initializing system data structures...\n");

    // Initialize vehicles with exact specifications from requirements
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

    // Initialize cities array with default cities
    strcpy(cities[0], "Colombo");
    strcpy(cities[1], "Kandy");
    strcpy(cities[2], "Galle");
    strcpy(cities[3], "Jaffna");
    city_count = 4;

    // Initialize distance matrix
    printf("Initializing distance matrix...\n");
    for(int i = 0; i < MAX_CITIES; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
            distances[i][j] = 0;
        }
    }

    // Set sample distances for demonstration
    distances[0][1] = 120; // Colombo to Kandy
    distances[1][0] = 120; // Kandy to Colombo
    distances[0][2] = 115; // Colombo to Galle
    distances[2][0] = 115; // Galle to Colombo
    distances[0][3] = 400; // Colombo to Jaffna
    distances[3][0] = 400; // Jaffna to Colombo
    distances[1][2] = 200; // Kandy to Galle
    distances[2][1] = 200; // Galle to Kandy
    distances[1][3] = 350; // Kandy to Jaffna
    distances[3][1] = 350; // Jaffna to Kandy

    printf("System initialization completed successfully!\n");
    printf("- Defined %d vehicle types\n", 3);
    printf("- Loaded %d default cities\n", city_count);
    printf("- Initialized %dx%d distance matrix\n", MAX_CITIES, MAX_CITIES);
    printf("- Ready for %d delivery records\n", MAX_DELIVERIES);
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
    printf("\n--- CITY MANAGEMENT ---\n");
    printf("Current cities in system (%d):\n", city_count);
    for(int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i, cities[i]);
    }
    printf("\nCity management features coming in next commit...\n");
}

void distanceManagement() {
    printf("\n--- DISTANCE MANAGEMENT ---\n");
    printf("Distance matrix structure initialized.\n");
    printf("Sample distances loaded for demonstration.\n");
    printf("\nDistance management features coming in next commit...\n");
}

void vehicleManagement() {
    printf("\n--- VEHICLE MANAGEMENT ---\n");
    printf("Defined vehicle types:\n");
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
    printf("\nVehicle management features coming in next commit...\n");
}

void deliveryRequest() {
    printf("\n--- DELIVERY REQUEST ---\n");
    printf("Delivery record structure defined.\n");
    printf("Maximum delivery capacity: %d records\n", MAX_DELIVERIES);
    printf("Current deliveries: %d\n", delivery_count);
    printf("\nDelivery request features coming in next commit...\n");
}

void performanceReports() {
    printf("\n--- PERFORMANCE REPORTS ---\n");
    printf("Performance tracking structure ready.\n");
    printf("Delivery records available for analysis: %d\n", delivery_count);
    printf("\nPerformance reporting features coming in next commit...\n");
}

void saveData() {
    printf("\n--- SAVE DATA ---\n");
    printf("File handling structure defined.\n");
    printf("Ready to save: cities, distances, and delivery records\n");
    printf("\nData persistence features coming in next commit...\n");
}

void loadData() {
    printf("Data loading functionality defined - ready for implementation.\n");
}
