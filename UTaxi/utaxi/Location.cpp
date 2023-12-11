#include "Location.hpp"
using namespace std;

Location::Location(string _name, double _latitude, double _longitude, int _traffic) {
    name = _name;
    latitude = _latitude;
    longitude = _longitude;
    traffic = _traffic;
}

std::string Location::get_name() {
    return name;
}

double Location::get_latitude() {
    return latitude;
}

double Location::get_longitude() {
    return longitude;
}

int Location::get_traffic() {
    return traffic;
}