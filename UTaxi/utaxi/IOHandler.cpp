#include "IOHandler.hpp"
using namespace std;

IOHandler::IOHandler(std::string _filename) {
    filename = _filename;
}

void IOHandler::read_location(Database& database) {
    ifstream file(filename);
    string line;
    getline(file, line);
    while(file >> line) {
        string location_name;
        double latitude, longitude;
        int traffic;
        size_t index;
        index = line.find(FILE_DELIMITER);
        location_name = line.substr(0, index);
        line = line.substr(index + 1);
        index = line.find(FILE_DELIMITER);
        latitude = stod(line.substr(0, index));
        line = line.substr(index + 1);
        index = line.find(FILE_DELIMITER);
        longitude = stod(line.substr(0, index));
        line = line.substr(index + 1);
        traffic = stoi(line);
        database.add_location(new Location(location_name, latitude, longitude, traffic));
    }
}
