#ifndef __DATABASE__
#define __DATABASE__
#include <vector>
#include "User.hpp"
#include "Location.hpp"
#include "Trip.hpp"
#include <algorithm>

class Database {
private:
    std::vector<User*> users;
    std::vector<Location*> locations;
    std::vector<Trip*> trips;
public:
    Database();
    std::vector<User*> get_users();
    std::vector<Location*> get_locations();
    std::vector<Trip*> get_trips();
    void add_location(Location* location);
    void add_user(User* user);
    void add_trip(Trip* trip);
    std::vector<Trip*> get_sorted_trips();
};

#endif