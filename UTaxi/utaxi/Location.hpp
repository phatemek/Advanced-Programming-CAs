#ifndef __LOCATION__
#define __LOCATION__
#include <string>

class Location {
private:
    std::string name;
    double latitude;
    double longitude;
    int traffic;
public:
    Location(std::string _name, double _latitude, double _longitude, int _traffic);
    std::string get_name();
    double get_latitude();
    double get_longitude();
    int get_traffic();
};

#endif