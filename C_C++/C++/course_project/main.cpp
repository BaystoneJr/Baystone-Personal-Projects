#include <iostream>
#include "classes\Trip.h"
#include "classes\Menus.h"
#include "classes\FileHandler.h"
#include <memory>
#include <iterator>
#include <algorithm>
#define DATABASE_NAME "tripdata.txt"

using namespace std;

bool checkDBFileAndPopulateVector(vector<Trip> &trips);

const string MenuTexts[] = {"Welcome to TripDairy, softaware to track your driving. \nPlease select the function you want to use by writing corresponding number below", "\t1. Initialize Database\n\t2. Save a trip data to file\n\t3. Read trip data from file\n\t4. Add new trip\n\t5. Remove trip\n\t6. Print report\n\t7. Calculate average fuel consumption\n\t8. Exit the program", "Trip database uninitiated, initiate database by selecting option 1 from main menu.", "To read the file in to TripDairy, the data must be formatted the following way in to the otherwise the data will be rejected.\n(start location)\n(star time)\n(odometer at start)\n(end time)\n(end time)\n(odometer at the end)\n(amount of fuel bought, enter 0 here if none was)\n"};

int main()
{
    MenuContainer mc;
    MenuWindow mw(1);
    int userChoice = 0;
    bool dbFileCheck;
    shared_ptr<FileHandler> fileptr;
    shared_ptr<Trip> tripptr;
    vector<Trip> savedTrips;

    dbFileCheck = checkDBFileAndPopulateVector(savedTrips);

    mc.Attach(&mw);
    mw.setSubject(&mc);
    mc.addString(MenuTexts[0]);

    if (!dbFileCheck)
    {
        mc.addString(MenuTexts[2]);
    }

    do
    {
        mc.addString(MenuTexts[1]);

        userChoice = mc.askInputInt("Enter corresponding number: ", 1, 8);

        if (!dbFileCheck && ((userChoice > 1) && (userChoice < 8)))
        {
            mc.addString(MenuTexts[2]);
            mc.askInputString("Press enter to return to main menu....");
        }
        else
        {
            switch (userChoice)
            {
            case 1:
                mc.addString("Initializing database...");

                fileptr = make_shared<SaveFile>(DATABASE_NAME);

                fileptr->openFile(fstream::out);
                if (fileptr->isFileOpen())
                {
                    mc.addString("Database initialized successefully");
                    dbFileCheck = true;
                }
                else
                {
                    mc.addString("Database initialition unsuccesseful");
                }
                fileptr->closeFile();

                checkDBFileAndPopulateVector(savedTrips);
                mc.askInputString("Press enter to return to menu....");

                break;
            case 2:
            {
                int index = 0;
                int chosenTrip = 0;
                string nameForFileSave;
                mc.addString("Select from the trips below the one you want to save: ");
                for_each(savedTrips.begin(), savedTrips.end(), [&index](Trip &trip)
                         { 
                            cout << index + 1 << ". " << trip.getTripHeader();
                            index++; });
                chosenTrip = mc.askInputInt("Enter the trips number: ", 1, savedTrips.size());
                nameForFileSave = mc.askInputString("Next, enter the file path and name (if name is entered only, file is to the root of the program): ");
                fileptr = make_shared<SaveFile>(nameForFileSave);

                fileptr->openFile(fstream::out);

                if (!fileptr->isFileOpen())
                {
                    mc.addString("Unable to open file to specified location, try again later");
                }
                else
                {
                    fileptr->writeTripToFile(savedTrips.at(chosenTrip - 1));
                    mc.addString("The trip is now saved to the file");
                }

                fileptr->closeFile();

                mc.askInputString("Press enter to return to the menu.....");
                break;
            }
            case 3:
            {
                string fileLoc;

                mc.addString(MenuTexts[3]);

                fileLoc = mc.askInputString("Enter file location: ");

                fileptr = make_shared<ReadFile>(fileLoc);
                tripptr = make_shared<Trip>();

                fileptr->openFile(fstream::in);

                if (!fileptr->isFileOpen())
                {
                    mc.addString("Unable to open the file where the data is, try again later");
                }
                else
                {
                    fileptr->readTripFromFile(*tripptr);

                    if (tripptr->isEmptyTrip())
                    {
                        mc.addString("File read failed, incorrect format");
                    }
                    else
                    {
                        mc.addString("File read successeful");

                        fileptr->closeFile();

                        savedTrips.push_back(*tripptr);

                        fileptr = make_shared<SaveFile>(DATABASE_NAME);

                        fileptr->openFile(fstream::out);

                        if (fileptr->isFileOpen())
                        {
                            for (auto trip : savedTrips)
                            {
                                fileptr->writeTripToFile(trip);
                            }
                            savedTrips.clear();
                        }
                        else
                        {
                            mc.addString("Unable to open file, try again later");
                        }

                        fileptr->closeFile();

                        checkDBFileAndPopulateVector(savedTrips);
                    }
                }

                mc.askInputString("Press enter to return to the menu(input might not register the first time).....");
                break;
            }

            case 4:
                tripptr = make_shared<Trip>();

                fileptr = make_shared<SaveFile>(DATABASE_NAME);

                fileptr->openFile(fstream::app);

                tripptr->askTripFromUser();

                fileptr->writeTripToFile(*tripptr);

                fileptr->closeFile();

                checkDBFileAndPopulateVector(savedTrips);

                mc.askInputString("New trip created, press enter to return to menu....");
                break;
            case 5:
            {
                int index = 0;
                int chosenTrip = 0;
                mc.addString("Select from the trips below the one you want to remove: ");
                for_each(savedTrips.begin(), savedTrips.end(), [&index](Trip &trip)
                         { 
                            cout << index + 1 << ". " << trip.getTripHeader();
                            index++; });
                chosenTrip = mc.askInputInt("Enter the trips number: ", 1, savedTrips.size());

                mc.addString("Deleting the selected trip...");

                chosenTrip = chosenTrip - 1;

                savedTrips.erase(savedTrips.begin() + chosenTrip);

                fileptr = make_shared<SaveFile>(DATABASE_NAME);

                fileptr->openFile(fstream::trunc);

                fileptr->closeFile();

                fileptr->openFile(fstream::out);

                if (fileptr->isFileOpen())
                {
                    for (auto trip : savedTrips)
                    {
                        fileptr->writeTripToFile(trip);
                    }
                    savedTrips.clear();
                }
                else
                {
                    mc.addString("Unable to open file, try again later");
                    mc.askInputString("Press enter to return to menu...");
                }

                fileptr->closeFile();

                cout << "Trip deleted..." << endl;

                checkDBFileAndPopulateVector(savedTrips);

                mc.askInputString("Press enter to return to the menu...");

                break;
            }
            case 6:
            {
                int minValue; 
                int maxValue;

                mc.addString("To see reports, enter the min and max values for trip distance.\nIf you want to see all trips, enter 0 on both.");

                minValue = mc.askInputInt("Enter minimum distance: ", 0, INT_MAX);
                maxValue = mc.askInputInt("Enter maximum distance: ", 0, INT_MAX);

                if (minValue == 0 && maxValue == 0)
                {

                    for (auto trip : savedTrips)
                    {
                        mc.addString(trip.tripReportString());
                    }
                }
                else
                {
                    for (auto trip : savedTrips)
                    {
                        if ((trip.getDistanceDriven() >= minValue) && (trip.getDistanceDriven() <= maxValue))
                        {
                            mc.addString(trip.tripReportString());
                        }
                    }
                }

                mc.askInputString("Trip report printed, press enter to return to menu....");
                break;
            }

            case 7:

            {
                double average = 0.0;

                if (savedTrips.size() == 0)
                {
                    mc.addString("Not enough trips to calculate average");
                    mc.askInputString("Press enter to return to main menu....");
                }
                else
                {

                    for (auto trip : savedTrips)
                    {
                        average = average + trip.getFuelConsumption();
                    }

                    average = average / savedTrips.size();

                    stringstream sout;

                    sout << "Average fuel consumption: " << average;

                    mc.addString(sout.str());

                    mc.askInputString("Press enter to return to the menu...");
                }

                break;
            }
            }
        }

    } while (userChoice != 8);

    return 0;
}

bool checkDBFileAndPopulateVector(vector<Trip> &trips)
{
    bool fileCheck;

    ReadFile file(DATABASE_NAME);

    file.openFile(fstream::in);

    if (!file.isFileOpen())
    {
        fileCheck = false;
    }
    else
    {
        file.readTripsFromFileToVector(trips);
        fileCheck = true;
    }

    return fileCheck;
}