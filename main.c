#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Car structure
typedef struct {
    int id;
    char brand[50];
    char model[50];
    char status[20];
} Car;

// Rental structure
typedef struct {
    int id;
    int carId;
    char rentalDate[20];
    char returnDate[20];
} Rental;

// Function declarations
void loadCarsFromFile(Car *cars, int *numCars);
void loadRentalsFromFile(Rental *rentals, int *numRentals);
void saveCarsToFile(Car *cars, int numCars);
void saveRentalsToFile(Rental *rentals, int numRentals);
void rentCar(Car *cars, int numCars, Rental *rentals, int *numRentals);
void displayCarDescription(Car *cars, int numCars);
void removeBrokenCars(Car *cars, int *numCars);
void modifyCar(Car *cars, int numCars);
void displayRentalHistory(Rental *rentals, int numRentals);
void returnCarComplaint(Rental *rentals, int *numRentals, Car *cars);
void displayStatistics(Car *cars, int numCars, Rental *rentals, int numRentals);
void printMenu();
void executeChoice(int choice, Car *cars, int numCars, Rental *rentals, int *numRentals);

int main() {
    Car cars[100];
    Rental rentals[500];
    int numCars = 0;
    int numRentals = 0;

    loadCarsFromFile(cars, &numCars);
    loadRentalsFromFile(rentals, &numRentals);

    int choice;
    do {
        printMenu();
        printf("Choice: ");
        scanf("%d", &choice);

        executeChoice(choice, cars, numCars, rentals, &numRentals);

    } while (choice != 0);

    saveCarsToFile(cars, numCars);
    saveRentalsToFile(rentals, numRentals);

    return 0;
}

void loadCarsFromFile(Car *cars, int *numCars) {
    FILE *file = fopen("cars.txt", "r");
    if (file == NULL) {
        *numCars = 0;
        return;
    }

    while (fscanf(file, "%d %s %s %s", &cars[*numCars].id, cars[*numCars].brand, cars[*numCars].model, cars[*numCars].status) == 4) {
        (*numCars)++;
    }

    fclose(file);
}

void loadRentalsFromFile(Rental *rentals, int *numRentals) {
    FILE *file = fopen("rentals.txt", "r");
    if (file == NULL) {
        *numRentals = 0;
        return;
    }

    while (fscanf(file, "%d %d %s %s", &rentals[*numRentals].id, &rentals[*numRentals].carId, rentals[*numRentals].rentalDate, rentals[*numRentals].returnDate) == 4) {
        (*numRentals)++;
    }

    fclose(file);
}

void saveCarsToFile(Car *cars, int numCars) {
    FILE *file = fopen("cars.txt", "w");
    if (file == NULL) {
        printf("Error saving cars.\n");
        return;
    }

    for (int i = 0; i < numCars; i++) {
        fprintf(file, "%d %s %s %s\n", cars[i].id, cars[i].brand, cars[i].model, cars[i].status);
    }

    fclose(file);
}

void saveRentalsToFile(Rental *rentals, int numRentals) {
    FILE *file = fopen("rentals.txt", "w");
    if (file == NULL) {
        printf("Error saving rentals.\n");
        return;
    }

    for (int i = 0; i < numRentals; i++) {
        fprintf(file, "%d %d %s %s\n", rentals[i].id, rentals[i].carId, rentals[i].rentalDate, rentals[i].returnDate);
    }

    fclose(file);
}

void rentCar(Car *cars, int numCars, Rental *rentals, int *numRentals) {
    int carId;
    printf("Enter the ID of the car you want to rent: ");
    scanf("%d", &carId);

    int carFound = 0;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carId && strcmp(cars[i].status, "Available") == 0) {
            carFound = 1;

            rentals[*numRentals].id = *numRentals + 1;
            rentals[*numRentals].carId = carId;
            printf("Enter the rental date (format DD/MM/YYYY): ");
            scanf("%s", rentals[*numRentals].rentalDate);

            strcpy(cars[i].status, "Rented");

            (*numRentals)++;

            printf("The car has been rented successfully.\n");
            break;
        }
    }

    if (!carFound) {
        printf("The car is not available or the ID is incorrect.\n");
    }
}

void displayCarDescription(Car *cars, int numCars) {
    int carId;
    printf("Enter the ID of the car you want to display the description for: ");
    scanf("%d", &carId);

    int carFound = 0;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carId) {
            carFound = 1;
            printf("Car Description (ID %d):\n", carId);
            printf("Brand: %s\n", cars[i].brand);
            printf("Model: %s\n", cars[i].model);
            printf("Status: %s\n", cars[i].status);
            break;
        }
    }

    if (!carFound) {
        printf("No car found with ID %d.\n", carId);
    }
}

void removeBrokenCars(Car *cars, int *numCars) {
    for (int i = 0; i < *numCars; i++) {
        if (strcmp(cars[i].status, "Broken") == 0) {
            for (int j = i; j < *numCars - 1; j++) {
                cars[j] = cars[j + 1];
            }

            (*numCars)--;
            i--;
        }
    }

    printf("Broken cars have been removed successfully.\n");
}

void modifyCar(Car *cars, int numCars) {
    int carId;
    printf("Enter the ID of the car you want to modify: ");
    scanf("%d", &carId);

    int carFound = 0;
    for (int i = 0; i < numCars; i++) {
        if (cars[i].id == carId) {
            carFound = 1;

            printf("New brand: ");
            scanf("%s", cars[i].brand);
            printf("New model: ");
            scanf("%s", cars[i].model);
            printf("New status: ");
            scanf("%s", cars[i].status);

            printf("The car has been modified successfully.\n");
            break;
        }
    }

    if (!carFound) {
        printf("No car found with ID %d.\n", carId);
    }
}

void displayRentalHistory(Rental *rentals, int numRentals) {
    if (numRentals > 0) {
        printf("Rental History:\n");
        for (int i = 0; i < numRentals; i++) {
            printf("Rental %d:\n", rentals[i].id);
            printf("ID of the rented car: %d\n", rentals[i].carId);
            printf("Rental date: %s\n", rentals[i].rentalDate);
            if (strlen(rentals[i].returnDate) > 0) {
                printf("Return date: %s\n", rentals[i].returnDate);
            }
            printf("\n");
        }
    } else {
        printf("No rentals recorded.\n");
    }
}

void returnCarComplaint(Rental *rentals, int *numRentals, Car *cars) {
    int carId;
    printf("Enter the ID of the car to be returned due to a complaint: ");
    scanf("%d", &carId);

    int rentalFound = 0;
    for (int i = *numRentals - 1; i >= 0; i--) {
        if (rentals[i].carId == carId) {
            rentalFound = 1;

            printf("Enter the return date (format DD/MM/YYYY): ");
            scanf("%s", rentals[i].returnDate);

            // Update the status of the correct car
            strcpy(cars[rentals[i].carId - 1].status, "Available");

            printf("The car has been returned due to a complaint successfully.\n");
            break;
        }
    }

    if (!rentalFound) {
        printf("No rental recorded for the car with ID %d.\n", carId);
    }
}

void displayStatistics(Car *cars, int numCars, Rental *rentals, int numRentals) {
    double averageUtilizationRate = 0.0;

    if (numCars > 0 && numRentals > 0) {
        averageUtilizationRate = ((double)numRentals / numCars) * 100;
    }

    printf("Average utilization rate: %.2f%%\n", averageUtilizationRate);

    int maxRentals = -1;
    int minRentals = numRentals + 1;
    int mostRentedCarId = -1;
    int leastRentedCarId = -1;

    for (int i = 0; i < numCars; i++) {
        int carRentals = 0;

        for (int j = 0; j < numRentals; j++) {
            if (rentals[j].carId == cars[i].id) {
                carRentals++;
            }
        }

        if (carRentals > maxRentals) {
            maxRentals = carRentals;
            mostRentedCarId = cars[i].id;
        }

        if (carRentals < minRentals) {
            minRentals = carRentals;
            leastRentedCarId = cars[i].id;
        }
    }

    if (mostRentedCarId != -1) {
        printf("Most rented car (ID %d): %s %s\n", mostRentedCarId, cars[mostRentedCarId - 1].brand, cars[mostRentedCarId - 1].model);
    } else {
        printf("No rentals recorded.\n");
    }

    if (leastRentedCarId != -1) {
        printf("Least rented car (ID %d): %s %s\n", leastRentedCarId, cars[leastRentedCarId - 1].brand, cars[leastRentedCarId - 1].model);
    } else {
        printf("No rentals recorded.\n");
    }
}

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Rent a car\n");
    printf("2. Display car description\n");
    printf("3. Remove broken cars\n");
    printf("4. Modify car information\n");
    printf("5. Display rental history\n");
    printf("6. Return a car due to complaint\n");
    printf("7. Display usage statistics\n");
    printf("0. Quit\n");
}

void executeChoice(int choice, Car *cars, int numCars, Rental *rentals, int *numRentals) {
    switch (choice) {
        case 1:
            rentCar(cars, numCars, rentals, numRentals);
            break;
        case 2:
            displayCarDescription(cars, numCars);
            break;
        case 3:
            removeBrokenCars(cars, numCars);
            break;
        case 4:
            modifyCar(cars, numCars);
            break;
        case 5:
            displayRentalHistory(rentals, numRentals);
            break;
        case 6:
            returnCarComplaint(rentals, numRentals, cars);
            break;
        case 7:
            displayStatistics;
                    (cars, numCars, rentals, numRentals);
            break;
        case 0:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}
