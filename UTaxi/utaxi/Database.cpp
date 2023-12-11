#include "Database.hpp"
#include <vector>
using namespace std;

Database::Database() {}

vector<User*> Database::get_users() {
    return users;
}

vector<Location*> Database::get_locations() {
    return locations;
}

vector<Trip*> Database::get_trips() {
    return trips;
}

void Database::add_location(Location* location) {
    locations.push_back(location);
}

void Database::add_user(User* user) {
    users.push_back(user);
}

void Database::add_trip(Trip* trip) {
    trips.push_back(trip);
}

bool trip_sorter(Trip* first_trip, Trip* second_trip) {
    return first_trip->get_price() > second_trip->get_price();
}

vector<Trip*> Database::get_sorted_trips() {
    vector<Trip*> sorted_trips = trips;
    sort(sorted_trips.begin(), sorted_trips.end(), trip_sorter);
    return sorted_trips;
}