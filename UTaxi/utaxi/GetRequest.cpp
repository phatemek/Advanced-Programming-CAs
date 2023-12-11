#include "GetRequest.hpp"
#include <iostream>
using namespace std;

GetRequest::GetRequest() {
    username = invalid_string;
    id = invalid_id;
    origin = invalid_string;
    destination = invalid_string;
    is_in_hurry = invalid_string;
    sort_by_cost = invalid_string;
}

void GetRequest::set_username(string _username) {
    username = _username;
}

void GetRequest::set_id(int _id) {
    id = _id;
}

void GetRequest::set_origin(string _origin) {
    origin = _origin;
}

void GetRequest::set_destination(string _destination) {
    destination = _destination;
}

void GetRequest::set_in_hurry(string _is_in_hurry) {
    is_in_hurry = _is_in_hurry;
}

void GetRequest::set_sort_by_cost(string _sort_by_cost) {
    sort_by_cost = _sort_by_cost;
}

void GetRequest::handle_trips_errors(Database& database) {
    check_trips_fields();
    check_username(database, "driver");
}

double GetRequest::get_cost(Database& database) {
    handle_get_cost_errors(database);
    return calculate_price(database.get_locations());
}

void GetRequest::check_trips_fields() {
    if(username == invalid_string || sort_by_cost == invalid_string) {
        throw(new Error("Trips List Bad Request"));
    }
}

void GetRequest::check_username(Database& database, string command_user) {
    bool correct_username = false;
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            if(user->get_role() != command_user) {
                throw(new Error("Permission Denied"));
            }
            correct_username = true;
            break;
        }
    }
    if(!correct_username) {
        throw(new Error("Not Found"));
    }
}

double GetRequest::calculate_price(vector<Location*> locations) {
    double origin_lat, origin_long, destination_lat, destination_long, distance, price;
    int origin_traffic, destination_traffic;
    for(Location* location : locations) {
        if(location->get_name() == origin) {
            origin_lat = location->get_latitude();
            origin_long = location->get_longitude();
            origin_traffic = location->get_traffic();
        }
        else if(location->get_name() == destination) {
            destination_lat = location->get_latitude();
            destination_long = location->get_longitude();
            destination_traffic = location->get_traffic();
        }
    }
    distance = degree_per_kilometer * sqrt(pow((destination_lat - origin_lat), 2) + pow((destination_long - origin_long), 2));
    price = distance * (origin_traffic + destination_traffic) * constant_price;
    if(is_in_hurry == "yes")
        price = price * in_hurry_factor;
    return price;
}

void GetRequest::handle_get_cost_errors(Database& database) {
    check_get_cost_fields();
    check_username(database, "passenger");
    check_cost_locations(database);
}

void GetRequest::check_get_cost_fields() {
    if(username == invalid_string || origin == invalid_string || destination == invalid_string || is_in_hurry == invalid_string) {
        throw(new Error("Trip Bad Request"));
    }
    if(is_in_hurry != "yes" && is_in_hurry != "no") {
        throw(new Error("Trip Bad Request"));
    }
}

void GetRequest::check_cost_locations(Database& database) {
    int correct_locations = 0;
    for(Location* location : database.get_locations()) {
        if(location->get_name() == origin || location->get_name() == destination) {
            correct_locations++;
        }
    }
    if(correct_locations < 2) {
        throw(new Error("Trip Not Found"));
    }
}