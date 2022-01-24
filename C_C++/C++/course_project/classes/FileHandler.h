#ifndef PROJECT_FILEHANDLER_INCLUDED
#define PROJECT_FILEHANDLER_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "Trip.h"

using namespace std;

/**
 * @brief FileHandler class is used for all of the operations that require access to files
 * 
 */

class FileHandler {
    public:
    FileHandler(string name);
    virtual void openFile(fstream::openmode mode);
    virtual bool isFileOpen();
    virtual bool isFileGood();
    virtual void closeFile();
    virtual void writeTripToFile(Trip trip);
    virtual void readTripFromFile(Trip &trip);
    virtual ~FileHandler() {};
    protected:
    string filePath;
    fstream file;
};


class ReadFile : public FileHandler {
    public:
    ReadFile(string file);
    void readTripFromFile(Trip &trip) override;
    void readTripsFromFileToVector(vector<Trip> &trips);
};

class SaveFile : public FileHandler {
    public:
    SaveFile(string file);
    void writeTripToFile(Trip trip) override;

};

#endif