#include "Trip.hpp"
using namespace std;

Trip::Trip(string _passenger_name, string _origin, string _destination, int _id, string _is_in_hurry, vector<Location*> locations) {
    passenger_name = _passenger_name;
    origin = _origin;
    destination = _destination;
    id = _id;
    is_in_hurry = _is_in_hurry;
    status = "waiting";
    canceled = false;
    price = calculate_price(locations);
}

string Trip::get_passenger_name() {
    return passenger_name;
}

string Trip::get_driver_name() {
    return driver_name;
}

string Trip::get_status() {
    return status;
}

int Trip::get_id() {
    return id;
}

double Trip::get_price() {
    return price;
}

void Trip::show_info(std::string& body) {
    body += "<td> " + to_string(id) + " </td>";
    body += "<td> " + passenger_name + " </td>";
    body += "<td> " + origin + " </td>";
    body += "<td> " + destination + " </td>";
    body += "<td> " + status + " </td>";
    body += "<td> " + to_string(price) + " </td>";
}

bool Trip::is_canceled() {
    return canceled;
}

void Trip::cancel() {
    canceled = true;
}

void Trip::set_status(std::string _status) {
    status = _status;
}

void Trip::set_driver(std::string _driver_name) {
    driver_name = _driver_name;
}

double Trip::calculate_price(vector<Location*> locations) {
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