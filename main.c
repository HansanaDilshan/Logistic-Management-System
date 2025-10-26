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
void inputDistance();
void displayDistanceTable();
void findLeastCostRoute(int source, int destination, int* path, int* path_length, float* min_distance);
float calculateDeliveryCost(int source, int destination, int vehicle_type, float weight);

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
    int choice;
    do {
        printf("\n--- DISTANCE MANAGEMENT ---\n");
        printf("1. Input/Edit Distance\n");
        printf("2. Display Distance Table\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                inputDistance();
                break;
            case 2:
                displayDistanceTable();
                break;
            case 3:
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 3);
}

void inputDistance() {
    if(city_count < 2) {
        printf("Need at least 2 cities to set distances!\n");
        return;
    }

    displayCities();
    int city1, city2;
    float distance;

    printf("Enter source city index: ");
    scanf("%d", &city1);
    printf("Enter destination city index: ");
    scanf("%d", &city2);

    if(city1 < 0 || city1 >= city_count || city2 < 0 || city2 >= city_count) {
        printf("Invalid city indices!\n");
        return;
    }

    if(city1 == city2) {
        printf("Distance from a city to itself is always 0!\n");
        return;
    }

    printf("Enter distance between %s and %s (km): ", cities[city1], cities[city2]);
    scanf("%f", &distance);

    if(distance < 0) {
        printf("Distance cannot be negative!\n");
        return;
    }

    distances[city1][city2] = distance;
    distances[city2][city1] = distance;
    printf("Distance updated successfully!\n");
}

void displayDistanceTable() {
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    printf("\n--- DISTANCE TABLE (km) ---\n");
    printf("%-15s", "");
    for(int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");

    for(int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
        for(int j = 0; j < city_count; j++) {
            printf("%-15.2f", distances[i][j]);
        }
        printf("\n");
    }
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
    if(city_count < 2) {
        printf("Need at least 2 cities for delivery!\n");
        return;
    }

    if(delivery_count >= MAX_DELIVERIES) {
        printf("Maximum delivery limit reached!\n");
        return;
    }

    displayCities();
    int source, destination, vehicle_type;
    float weight;

    printf("Enter source city index: ");
    scanf("%d", &source);
    printf("Enter destination city index: ");
    scanf("%d", &destination);

    if(source < 0 || source >= city_count || destination < 0 || destination >= city_count) {
        printf("Invalid city indices!\n");
        return;
    }

    if(source == destination) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    printf("Enter package weight (kg): ");
    scanf("%f", &weight);

    if(weight <= 0) {
        printf("Weight must be positive!\n");
        return;
    }

    vehicleManagement();
    printf("Select vehicle type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicle_type);

    if(vehicle_type < 1 || vehicle_type > 3) {
        printf("Invalid vehicle type!\n");
        return;
    }

    if(weight > vehicles[vehicle_type - 1].capacity) {
        printf("Weight exceeds vehicle capacity! Maximum: %d kg\n", vehicles[vehicle_type - 1].capacity);
        return;
    }

    int path[MAX_CITIES];
    int path_length = 0;
    float min_distance = 0;

    findLeastCostRoute(source, destination, path, &path_length, &min_distance);

    if(min_distance == 0) {
        printf("No valid route found between %s and %s!\n", cities[source], cities[destination]);
        return;
    }

    float base_cost = min_distance * vehicles[vehicle_type - 1].rate_per_km * (1 + weight / 10000.0);
    float fuel_used = min_distance / vehicles[vehicle_type - 1].fuel_efficiency;
    float fuel_cost = fuel_used * FUEL_PRICE;
    float operational_cost = base_cost + fuel_cost;
    float profit = base_cost * 0.25;
    float customer_charge = operational_cost + profit;
    float delivery_time = min_distance / vehicles[vehicle_type - 1].avg_speed;

    printf("\n==============================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("==============================================================\n");
    printf("From: %s\n", cities[source]);
    printf("To: %s\n", cities[destination]);
    printf("Route: ");
    for(int i = 0; i < path_length; i++) {
        printf("%s", cities[path[i]]);
        if(i < path_length - 1) printf(" → ");
    }
    printf("\n");
    printf("Minimum Distance: %.2f km\n", min_distance);
    printf("Vehicle: %s\n", vehicles[vehicle_type - 1].type);
    printf("Weight: %.2f kg\n", weight);
    printf("==============================================================\n");
    printf("Base Cost: %.2f LKR\n", base_cost);
    printf("Fuel Used: %.2f L\n", fuel_used);
    printf("Fuel Cost: %.2f LKR\n", fuel_cost);
    printf("Operational Cost: %.2f LKR\n", operational_cost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customer_charge);
    printf("Estimated Time: %.2f hours\n", delivery_time);
    printf("==============================================================\n");
}

void findLeastCostRoute(int source, int destination, int* path, int* path_length, float* min_distance) {
    if(distances[source][destination] > 0) {
        path[0] = source;
        path[1] = destination;
        *path_length = 2;
        *min_distance = distances[source][destination];
        return;
    }

    for(int i = 0; i < city_count; i++) {
        if(i != source && i != destination &&
           distances[source][i] > 0 && distances[i][destination] > 0) {

            float total_distance = distances[source][i] + distances[i][destination];

            if(*min_distance == 0 || total_distance < *min_distance) {
                *min_distance = total_distance;
                path[0] = source;
                path[1] = i;
                path[2] = destination;
                *path_length = 3;
            }
        }
    }

    if(*min_distance == 0) {
        for(int i = 0; i < city_count; i++) {
            for(int j = 0; j < city_count; j++) {
                if(i != source && i != destination && j != source && j != destination && i != j &&
                   distances[source][i] > 0 && distances[i][j] > 0 && distances[j][destination] > 0) {

                    float total_distance = distances[source][i] + distances[i][j] + distances[j][destination];

                    if(*min_distance == 0 || total_distance < *min_distance) {
                        *min_distance = total_distance;
                        path[0] = source;
                        path[1] = i;
                        path[2] = j;
                        path[3] = destination;
                        *path_length = 4;
                    }
                }
            }
        }
    }
}

float calculateDeliveryCost(int source, int destination, int vehicle_type, float weight) {
    float distance = distances[source][destination];
    return distance * vehicles[vehicle_type - 1].rate_per_km * (1 + weight / 10000.0);
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
