#ifndef PROJECT_TRIP_INCLUDED
#define PROJECT_TRIP_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <iomanip>

using namespace std;

/**
 * @brief This is the Trip-class, used to handle all of the operations for trips.
 * 
 */

class Trip {
    friend ostream &operator<<(ostream &out, const Trip &trip);
    friend istream &operator>>(istream &in, Trip &trip);
    public:
    Trip(string initStartLoc, string initStartTime, int initStartOdo, string initEndLoc, string initEndTime, int initEndOdo, int fuel);
    Trip();
    void printTripReport();
    void askTripFromUser();
    string getTripTime();
    string tripReportString();
    string getTripHeader();
    int getTripHours();
    int getTripMinutes();
    int getDistanceDriven();
    double getFuelConsumption();
    bool isEmptyTrip();
    bool checkIfTimeIsValid(string time);

    private:
    string startLoc;
    string startTime;
    int startOdo;
    string endLoc;
    string endTime;
    int endOdo;
    int amountFuelBought;
    bool isEmpty;
};  

#endif