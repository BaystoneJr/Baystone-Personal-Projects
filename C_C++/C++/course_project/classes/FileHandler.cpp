#include "FileHandler.h"

FileHandler::FileHandler(string name) : filePath(name) {

}

void FileHandler::openFile(fstream::openmode mode) {
    file.open(filePath, mode);
}

bool FileHandler::isFileOpen() {
    return file.is_open();
}

bool FileHandler::isFileGood() {
    return file.good();
}

void FileHandler::closeFile() {
    file.close();
}

void FileHandler::writeTripToFile(Trip trip) {

}

void FileHandler::readTripFromFile(Trip &trip) {

}

SaveFile::SaveFile(string file) : FileHandler(file) {
}

void SaveFile::writeTripToFile(Trip trip) {
    file << trip;
}

ReadFile::ReadFile(string file) : FileHandler(file) {

}

void ReadFile::readTripFromFile(Trip &trip) {
    file >> trip;
}
void ReadFile::readTripsFromFileToVector(vector<Trip> &trips) {
    vector<Trip> tempTrips;
    Trip tempTrip;

    while (FileHandler::isFileGood())
    {
        readTripFromFile(tempTrip);

        if(!tempTrip.isEmptyTrip()) {
            tempTrips.push_back(tempTrip);
        }
    }

    copy(tempTrips.begin(), tempTrips.end(), back_inserter(trips));
}
