#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CAR_LIST_SIZE 15

/*
* Structure for car rental
* manufacturer = name of the cars manufacturer (example: Volkswagen)
* model = cars model (example: Polo)
* category = the category of the car, based on the ACRISS/SIPP-car code system
* registerationPlate = registeration plate of the car (example: HEL-123)
* mileage = current mileage of the car (123456)
* availability = availiability of the car, 1 = available for rental | 0 = in use/not available
*/
struct rental_car {
    char manufacturer[30];
    char model[15];
    char category[6];
    char registerationPlate[15];
    unsigned int mileage;
    int availability;
};
/*
* Function to intialize values to the list of cars
* Takes 2 parameters: list, which is the list of cars and length, which is length of the list
*/
void intializeListOfCars(struct rental_car *list, int length);
/*
* Function to generate "random" values to the list of the cars, this function was made due to the fact that
* creator of the code didn't want to write 15 rental_car structures to an array
* Takes 1 parameter: index, which is the index number of the loop in order to get unique licence plates to cars
*/
struct rental_car generateRandomRentalCar(int index);
/*
* This function prints all of the cars on the list
* It takes 2 parameters: list, which is the list of cars and length, which is the length of the list
*/
void printAllCars(struct rental_car *list, int length);
/*
* This function prints all available cars based on searched category, and if it can't find the car based on category
* or there is no available car on that category, the function will print a message to notify the user
* Takes 3 parameters: list, which is the list of cars, length, which is the length of the list and 
* searchCategory which is a string that contains the searhed category that user wrote
*/
void printAvailableCarsBasedOnCategory(struct rental_car *list, int length, char *searchCategory);
/*
* This function changes the status of the car from available to currently rented and vice versa
* It has 3 parameters: 1. list, which is the list of rental cars 2. listLength, which is the length of the list
* 3. searchedRegisterationPlate, which is the registeration plate, that user wanted to be found
* Return value: the function will return a value of 0 if the change was successful or an value above 0 if it was not 
*/
int changeCarState(struct rental_car *list, int listLength, char *searchedRegisterationPlate);


int main(void) {
    struct rental_car listOfCars[MAX_CAR_LIST_SIZE] = {};
    intializeListOfCars(listOfCars, MAX_CAR_LIST_SIZE);
    int usersInput = 0;

    printf("This is a car rental program\n");
    printf("Thorugh this program, user can list all cars, search cars based on category, change state of car or quit program\n");
    printf("The program will list corresponding nubmer for the action, that user wants to perform\n");

    do {
        printf("What do you want to do?\n");
        printf("\t1. print all cars\n");
        printf("\t2. print free cars of given category\n");
        printf("\t3. change state of car\n");
        printf("\t4. quit program\n");
        printf("Write the corresponding number here: ");
        scanf("%d", &usersInput);

        switch (usersInput)
        {
        case 1 :
            printAllCars(listOfCars, MAX_CAR_LIST_SIZE);
            break;
        case 2 : ;
            char searchCategory[5] = {};

            printf("To search for a car, you need to write the full 4-letter category of the car and it will print all available cars from given category.\n");
            printf("if you write \"*\"-character, all cars will be printed\n");
            printf("Write down the category from which you want the car (the four letters, write letters in upper case):");
            fflush(stdin);
            fgets(searchCategory, 5, stdin);
            printAvailableCarsBasedOnCategory(listOfCars, MAX_CAR_LIST_SIZE, searchCategory);
            fflush(stdin);

            break;
        case 3 : ;
            char searchedLicencePlate[8] = {};
            printf("To change the state of the car, write the registeration plate of the car\n");
            printf("The program will automatically search for the car with that plate, and change the status (either from available to rented or from rented to available)\n");
            printf("Write the registeration plate here: ");
            fflush(stdin);
            fgets(searchedLicencePlate, 8, stdin);
            int statusChangeSuccess = changeCarState(listOfCars, MAX_CAR_LIST_SIZE, searchedLicencePlate);
            fflush(stdin);
            if(statusChangeSuccess == 1) {
                printf("State of the car with registeration plate %s was changed successefully\n", searchedLicencePlate);
            } else {
                printf("State of the car with registeration plate %s could not be change successefully, check input and try again\n", searchedLicencePlate);
            }

            break;
        case 4 :
            printf("You chose to quit the program\n"); 
            break;
        default:
            printf("Number picked did not match any of the actions, please choose correct number corresponding to an available action\n");
            break;
        }
    } while(usersInput != 4);

    return 0;
}


void intializeListOfCars(struct rental_car *list, int length) {
    for(int index = 0; index < length; index++) {
        struct rental_car car = generateRandomRentalCar(index);
        list[index] = car;
    }

}

struct rental_car generateRandomRentalCar(int index) {
    int availability = 0, randomManufacturer = 0, randomModel = 0, randomLicencePlate = 0, randomCategory = 0;
    unsigned int mileage;
    struct rental_car car = {};

    time_t t;

    t = time(&t);

    unsigned int time = (unsigned) t * (unsigned) index;

    srand(time);

    char* carManufacturers[7] = {
        "Saab",
        "BMW",
        "Volkswagen",
        "Ford",
        "Toyota",
        "Honda",
        "Volvo"
    };
    char* carModels[10] = {
        "335d",
        "9-3",
        "Polo",
        "XC90",
        "Civic",
        "Camry",
        "550",
        "9-5",
        "Passat",
        "Mondeo"
    };
    char* categories[8] = {
        "SSME",
        "MDAH",
        "EEBQ",
        "XNMZ",
        "IWDC",
        "NSAR",
        "FTND",
        "PSDE"
    };
    char* licencePlate[15] = {
        "ABC-123",
        "CBA-321",
        "PLO-987",
        "RFT-654",
        "OLI-498",
        "CVB-420",
        "GHB-326",
        "LKM-765",
        "UTI-427",
        "YJK-832",
        "LKM-874",
        "HJK-864",
        "BNV-442",
        "NBL-321",
        "NBC-115"
    };

    randomManufacturer = rand() % 7;
    randomModel = rand() % 10;
    randomCategory = rand() % 8;
    mileage = (unsigned) rand() % 300000;
    availability = rand() % 2;

    char* manufacturer = carManufacturers[randomManufacturer];
    char* model = carModels[randomModel];
    char* category = categories[randomCategory];
    char* registerationPlate = licencePlate[index];

    strncpy(car.manufacturer, manufacturer, strlen(manufacturer));
    strncpy(car.model, model, strlen(model));
    strncpy(car.category, category, strlen(category));
    strncpy(car.registerationPlate, registerationPlate, strlen(registerationPlate));
    car.mileage = mileage;
    car.availability = availability;

    return car;
}

void printAllCars(struct rental_car *list, int length) {
    for(int index = 0; index < length; index++) {
        struct rental_car currentCar = list[index];

        printf("| Manufacturer: %s | Model: %s | Category: %s | Registeration Plate: %s | Availability: %s | Mileage: %d |\n", 
        currentCar.manufacturer, currentCar.model, currentCar.category, currentCar.registerationPlate, (currentCar.availability == 1 ? "Available" : "Currently Rented"), currentCar.mileage);

    }
}

void printAvailableCarsBasedOnCategory(struct rental_car *list, int length, char *searchCategory) {
    int foundCarsCounter = 0;
    if((strncmp(searchCategory, "*", 1)) == 0) {
        printAllCars(list, length);
    } else {
        for(int index = 0; index < length; index++) {
            struct rental_car currentCar = list[index];
            if(((strncmp(currentCar.category, searchCategory, 4)) == 0) && (currentCar.availability == 1)) {
                printf("| Manufacturer: %s | Model: %s | Category: %s | Registeration Plate: %s | Availability: %s | Mileage: %d |\n", 
                currentCar.manufacturer, currentCar.model, currentCar.category, currentCar.registerationPlate, (currentCar.availability == 1 ? "Available" : "Currently Rented"), currentCar.mileage);
                foundCarsCounter++;
            }
        }
        if(foundCarsCounter == 0) {
            printf("No cars found based on your search, prehaps try another category?\n");
        } else {
            printf("Based on your search, there were %d cars available\n", foundCarsCounter);
        }
    }
}

int changeCarState(struct rental_car *list, int listLength, char *searchedRegisterationPlate) {
    int wasSuccess = 0;
    printf("Registeration plate: %s\n", searchedRegisterationPlate);
    for(int index = 0; index < listLength; index++) {
        struct rental_car currentCar = list[index];

        if(((strncmp(currentCar.registerationPlate, searchedRegisterationPlate, 7)) == 0) && wasSuccess == 0) {
            int currentStatus = currentCar.availability;

            if(currentStatus == 1) {
                list[index].availability = 0;
            } else {
                list[index].availability = 1;
            }
            wasSuccess = 1;
        }
    }
    return wasSuccess;
}
