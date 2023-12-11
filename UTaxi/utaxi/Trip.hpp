#ifndef __TRIP__
#define __TRIP__
#include <string>
#include <vector>
#include <cmath>
#include "Location.hpp"
#include "PriceConsts.hpp"

class Trip {
protected:
    std::string passenger_name;
    std::string driver_name;
    std::string origin;
    std::string destination;
    std::string status;
    std::string is_in_hurry;
    int id;
    bool canceled;
    double price;
public:
    Trip(std::string _passenger_name, std::string _origin, std::string _destination, int _id, std::string _is_in_hurry, std::vector<Location*> locations);
    std::string get_passenger_name();
    std::string get_driver_name();
    std::string get_status();
    int get_id();
    double get_price();
    void show_info(std::string& body);
    double calculate_price(std::vector<Location*> locations);
    bool is_canceled();
    void cancel();
    void set_status(std::string _status);
    void set_driver(std::string _driver_name);
};

#endif