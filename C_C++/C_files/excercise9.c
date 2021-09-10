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

void intializeListOfCars(struct rental_car *list, int length);
void generateValuesToListOfCars(struct rental_car car);

int main(void) {
    struct rental_car listOfCars[MAX_CAR_LIST_SIZE] = {};
    intializeListOfCars(listOfCars, MAX_CAR_LIST_SIZE);

    

    return 0;
}

void generateValuesToListOfCars(struct rental_car car) {
    int availability = 0, randomManufacturer = 0, randomModel = 0, randomLicencePlate = 0, randomCategory = 0;
    unsigned int mileage;

    time_t t;

    srand((unsigned) time(&t));

    const char* carManufacturers[7] = {
        "Saab",
        "BMW",
        "Volkswagen",
        "Ford",
        "Toyota",
        "Honda",
        "Volvo"
    };
    const char* carModels[10] = {
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
    const char* category[8] = {
        "SSME",
        "MDAH",
        "EEBQ",
        "XNMZ",
        "IWDC",
        "NSAR",
        "FTND",
        "PSDE"
    };
    const char* licencePlate[10] = {
        "ABC-123",
        "CBA-321",
        "PLO-987",
        "RFT-654",
        "OLI-498",
        "CVB-420",
        "GHB-326",
        "LKM-765",
        "UTI-427",
        "YJK-832"
    };
    randomManufacturer = rand() % 8;
    randomModel = rand() % 11;
    randomLicencePlate = rand() % 11;
    randomCategory = rand() % 8;
    mileage = (unsigned) rand() % 300000;
    availability = rand() % 2;

    strcpy(car.manufacturer, carManufacturers[randomManufacturer]);
    strcpy(car.model, carModels[randomModel]);
    strcpy(car.category, category[randomCategory]);
    strcpy(car.registerationPlate, licencePlate[randomLicencePlate]);
    car.mileage = mileage;
    car.availability = availability;


}


void intializeListOfCars(struct rental_car *list, int length) {
    for(int index = 0; index < length; index++) {
        generateValuesToListOfCars(list[index]);
    }

}