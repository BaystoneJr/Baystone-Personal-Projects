#include "Trip.h"

Trip::Trip(string initStartLoc, string initStartTime, int initStartOdo, string initEndLoc, string initEndTime, int initEndOdo, int fuel) : startLoc(initStartLoc), startTime(initStartTime), startOdo(initStartOdo),
                                                                                                                                           endLoc(initEndLoc), endTime(initEndTime), endOdo(initEndOdo),
                                                                                                                                           amountFuelBought(fuel)
{
    isEmpty = false;
}
Trip::Trip()
{
    startLoc = "";
    startTime = -1;
    startOdo = -1;
    endLoc = "";
    endTime = -1;
    endOdo = -1;
    amountFuelBought = -1;
    isEmpty = true;
}
void Trip::printTripReport()
{
    cout << "Start location: " << startLoc << endl;
    cout << "Start time: " << startTime << endl;
    cout << "Start odometer: " << startOdo << endl;
    cout << "End location: " << endLoc << endl;
    cout << "End time: " << endTime << endl;
    cout << "End odometer: " << endOdo << endl;
    cout << "Amount of fuel bought on trip: " << endl;
}
void Trip::askTripFromUser()
{
    string stringInput;
    int intInput;
    auto cinClearLambda = [](string str)
    {
        cin.sync();
        str.clear();
    };

    auto odometerValidity = [](int odometerStart, int odometerEnd)
    {
        return ((odometerStart >= 0) && (odometerEnd >= 0)) && (odometerEnd >= odometerStart);
    };

    auto timeCheckLambda = [](string timeInput)
    {
        bool inputCorrect;

        if ((timeInput.length() == 5) && (timeInput.compare(2, 1, ":") == 0))
        {
            string inputHours = timeInput.substr(0, 2);
            string inputMinutes = timeInput.substr(3, 2);

            int hours;
            int minutes;

            try
            {
                hours = stoi(inputHours);
                minutes = stoi(inputMinutes);

                if ((0 <= hours && hours < 24) && (0 <= minutes && minutes < 60))
                {
                    inputCorrect = true;
                }
                else
                {
                    inputCorrect = false;
                }
            }
            catch (const std::invalid_argument &e)
            {
                inputCorrect = false;
            }
        }
        else
        {
            inputCorrect = false;
        }

        return inputCorrect;
    };

    cout << "Enter details of a trip below: " << endl;

    cout << "Enter start location by writing the name of the location: ";

    cinClearLambda(stringInput);

    getline(cin, stringInput);

    startLoc = stringInput;

    cout << "Next, enter start location in the format (hh:mm): ";

    cinClearLambda(stringInput);

    getline(cin, stringInput);

    while (!timeCheckLambda(stringInput))
    {
        cout << "Incorrect input, correct format is (hh:mm), try again: ";
        cinClearLambda(stringInput);
        getline(cin, stringInput);
    }

    startTime = stringInput;

    cout << "Next, enter the odometer number at the start of the trip: ";

    cin >> intInput;

    while (cin.fail() || !odometerValidity(0, intInput))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input, please input correct integer value: ";

        cin >> intInput;
    }

    startOdo = intInput;

    cout << "Next, enter the end location: ";

    cinClearLambda(stringInput);

    getline(cin, stringInput);

    endLoc = stringInput;

    cout << "Next, enter time at the end of the trip: ";

    cinClearLambda(stringInput);

    getline(cin, stringInput);

    while (!timeCheckLambda(stringInput))
    {
        cout << "Incorrect input, correct format is (hh:mm), try again: ";
        cinClearLambda(stringInput);
        getline(cin, stringInput);
    }

    endTime = stringInput;

    cout << "Next, enter the number on the odometer at the end of the trip (the number must be bigger than at the start or same size): ";

    intInput = 0;

    cin >> intInput;

    while (cin.fail() || !odometerValidity(startOdo, intInput))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Invalid input, please input correct integer value: ";

        cin >> intInput;
    }

    endOdo = intInput;

    cout << "Finally, enter the amount of fuel bought during the trip, if any was bought (round up to nearest integer): ";

    intInput = 0;

    cin >> intInput;

    while (cin.fail() || intInput < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid value, try again: ";
        cin >> intInput;
    }

    amountFuelBought = intInput;

    isEmpty = false;
}
string Trip::tripReportString()
{
    ostringstream sout;

    sout << "Start location: " << startLoc << endl;
    sout << "Start time: " << startTime << endl;
    sout << "Odometer at the start: " << startOdo << endl;
    sout << "End location: " << endLoc << endl;
    sout << "End time: " << endTime << endl;
    sout << "Odometer at the end: " << endOdo << endl;
    sout << "Amount of fuel bought during the trip: " << amountFuelBought << endl;

    return sout.str();
}
bool Trip::isEmptyTrip()
{
    return isEmpty;
}
bool Trip::checkIfTimeIsValid(string time)
{
    bool correctTime;

    if ((time.length() == 5) && (time.compare(2, 1, ":") == 0))
    {
        string inputHours = time.substr(0, 2);
        string inputMinutes = time.substr(3, 2);

        int hours;
        int minutes;

        try
        {
            hours = stoi(inputHours);
            minutes = stoi(inputMinutes);

            if ((0 <= hours && hours < 24) && (0 <= minutes && minutes < 60))
            {
                correctTime = true;
            }
            else
            {
                correctTime = false;
            }
        }
        catch (const std::invalid_argument &e)
        {
            correctTime = false;
        }
    } else {
        correctTime = false;
    }
    return correctTime;
}
ostream &operator<<(ostream &out, const Trip &trip)
{
    out << trip.startLoc << endl;
    out << trip.startTime << endl;
    out << trip.startOdo << endl;
    out << trip.endLoc << endl;
    out << trip.endTime << endl;
    out << trip.endOdo << endl;
    out << trip.amountFuelBought << endl;

    return out;
}
istream &operator>>(istream &in, Trip &trip)
{
    int tempinputInt;
    string tempinputString;

    getline(in, trip.startLoc);
    if (trip.startLoc.empty())
    {
        trip.isEmpty = true;
    }
    else
    {

        in >> tempinputString;

        if(trip.checkIfTimeIsValid(tempinputString)) {
            trip.startTime = tempinputString;

            in >> tempinputInt;

            if(tempinputInt < 1) {
                trip.isEmpty = true;
            } else {
                trip.startOdo = tempinputInt;

                in.ignore();
                tempinputString.clear();
                getline(in, tempinputString);

                if(tempinputString.empty()) {
                    trip.isEmpty = true;
                } else {
                    trip.endLoc = tempinputString;

                    tempinputString.clear();

                    in >> tempinputString;

                    if(trip.checkIfTimeIsValid(tempinputString)) {
                        trip.endTime = tempinputString;

                        in >> tempinputInt;

                        if(tempinputInt < 1 || (trip.startOdo > tempinputInt)) {
                            trip.isEmpty = true;
                        } else {
                            trip.endOdo = tempinputInt;

                            in >> tempinputInt;

                            if(tempinputInt < 0) {
                                trip.isEmpty = true;
                            } else {
                                trip.amountFuelBought = tempinputInt;

                                trip.isEmpty = false;
                            }
                        }
                    }
                }
            }
        }  else {
            trip.isEmpty = true;
        }
    }

    return in;
}
string Trip::getTripTime()
{
    int tripHours = getTripHours();
    int tripMinutes = getTripMinutes();

    stringstream sout;

    sout << setfill('0') << setw(2) <<  tripHours;
    sout << ":";
    sout << setfill('0') << setw(2) << tripMinutes;

    return sout.str();  
}
int Trip::getTripHours()
{
    string startHour = startTime.substr(0, 2);
    string endHour = endTime.substr(0, 2);
    int startHours, endHours, tripHours;

    try
    {
        startHours = stoi(startHour);
        endHours = stoi(endHour);

        if(startHours > endHours) {
            tripHours = startHours - endHours;
        } else {
            tripHours = endHours - startHours;
        }
    }
    catch (const std::invalid_argument &e)
    {
        tripHours = -1;
    }

    return tripHours;
}
int Trip::getTripMinutes()
{
    int startMinutes, endMinutes, tripMinutes;

    string startMinute = startTime.substr(3, 2);
    string endMinute = endTime.substr(3, 2);
    try
    {
        startMinutes = stoi(startMinute);
        endMinutes = stoi(endMinute);

        if (startMinutes > endMinutes)
        {
            tripMinutes = startMinutes - endMinutes;
        }
        else
        {
            tripMinutes = endMinutes - startMinutes;
        }
    }
    catch (const std::invalid_argument &e)
    {
        tripMinutes = -1;
    }

    return tripMinutes;
}

string Trip::getTripHeader()
{
    stringstream headerstream;

    headerstream << "Start location: " << startLoc << ", ";
    headerstream << "end location: " << endLoc << ", ";
    headerstream << "trip time: " << getTripTime() << endl;

    return headerstream.str();
}
int Trip::getDistanceDriven() {
    return endOdo - startOdo;
}

double Trip::getFuelConsumption() {
    double consumption;
    int distance = getDistanceDriven();

    consumption = distance * 1.0 / amountFuelBought * 1.0;

    return consumption;
}
