#include "PostRequest.hpp"
#include <string>
using namespace std;

PostRequest::PostRequest() {
    username = invalid_string;
    role = invalid_string;
    origin = invalid_string;
    destination = invalid_string;
    is_in_hurry = invalid_string;
    id = invalid_id;
}

void PostRequest::set_username(std::string _username) {
    username = _username;
}

void PostRequest::set_role(std::string _role) {
    role = _role;
}

void PostRequest::set_origin(std::string _origin) {
    origin = _origin;
}

void PostRequest::set_destination(std::string _destination) {
    destination = _destination;
}

void PostRequest::set_in_hurry(std::string _is_in_hurry) {
    is_in_hurry = _is_in_hurry;
}

void PostRequest::set_id(int _id) {
    id = _id;
}

int PostRequest::get_id() {
    return id;
}

void PostRequest::signup(Database& database) {
    handle_signup_errors(database);
    if(role == "driver") {
        database.add_user(new Driver(username, role));
    }
    else {
        database.add_user(new Passenger(username, role));
    }
}

void PostRequest::make_trip(Database& database) {
    handle_make_trip_errors(database);
    id = database.get_trips().size() + 1;
    database.add_trip(new Trip(username, origin, destination, id, is_in_hurry, database.get_locations()));
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            user->set_busy();
            break;
        }
    }
}

void PostRequest::accept_trip(Database& database) {
    handle_accept_trip_errors(database);
    for(Trip* trip : database.get_trips()) {
        if(trip->get_id() == id) {
            trip->set_driver(username);
            trip->set_status("traveling");
            break;
        }
    }
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            user->set_busy();
            break;
        }
    }
}

void PostRequest::finish_trip(Database& database) {
    handle_finish_errors(database);
    string passenger_name;
    for(Trip* trip : database.get_trips()) {
        if(trip->get_id() == id) {
            trip->set_status("finished");
            passenger_name = trip->get_passenger_name();
            break;
        }
    }
    for(User* user : database.get_users()) {
        if(user->get_username() == username || user->get_username() == passenger_name) {
            user->set_free();
        }
    }
}

void PostRequest::handle_signup_errors(Database& database) {
    check_signup_fields();
    check_signup_user(database);
}

void PostRequest::check_signup_fields() {
    if(username == invalid_string || role == invalid_string) {
        throw(new Error("Signup Bad Request"));
    }
}

void PostRequest::check_signup_user(Database& database) {
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            throw(new Error("Signup Bad Request"));
        }
    }
    if(!(role == "passenger" || role == "driver")) {
        throw(new Error("Signup Bad Request"));
    }
}

void PostRequest::handle_make_trip_errors(Database& database) {
    check_make_trip_fields();
    check_locations(database);
    check_make_trip_user(database);
}

void PostRequest::check_make_trip_fields() {
    if(username == invalid_string || origin == invalid_string || destination == invalid_string || is_in_hurry == invalid_string) {
        throw(new Error("Trip Bad Request"));
    }
    if(is_in_hurry != "yes" && is_in_hurry != "no") {
        throw(new Error("Trip Bad Request"));
    }
}

void PostRequest::check_locations(Database& database) {
    int correct_locations = 0;
    for(Location* location : database.get_locations()) {
        if(location->get_name() == origin || location->get_name() == destination) {
            correct_locations++;
        }
    }
    if(correct_locations < trip_location_count) {
        throw(new Error("Trip Not Found"));
    }
}

void PostRequest::check_make_trip_user(Database& database) {
    bool correct_username = false;
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            if(user->get_role() == "driver") {
                throw(new Error("Permission Denied"));
            }
            if(user->get_is_busy()) {
                throw(new Error("Trip Bad Request"));
            }
            correct_username = true;
            break;
        }
    }
    if(!correct_username) {
        throw(new Error("Trip Not Found"));
    }
}

void PostRequest::handle_accept_trip_errors(Database& database) {
    check_accept_trip_fields();
    check_accept_trip_user(database);
    check_accept_trip_id(database);
}

void PostRequest::check_accept_trip_fields() {
    if(username == invalid_string || id == invalid_id) {
        throw(new Error("Trips List Bad Request"));
    }
}

void PostRequest::check_accept_trip_user(Database& database) {
    bool correct_username = false;
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            correct_username = true;
            if(user->get_role() == "passenger") {
                throw(new Error("Trips List Permission Denied"));
            }
            if(user->get_is_busy()) {
                throw(new Error("Trips List Bad Request"));
            }
        }
    }
    if(!correct_username) {
        throw(new Error("Trips List Not Found "));
    }
}

void PostRequest::check_accept_trip_id(Database& database) {
    bool correct_id = false;
    for(Trip* trip : database.get_trips()) {
        if(trip->get_id() == id && !trip->is_canceled()) {
            if(trip->get_status() != "waiting") {
                throw(new Error("Trips List Permission Denied"));
            }
            correct_id = true;
            break;
        }
    }
    if(!correct_id) {
        throw(new Error("Trips List Not Found"));
    }
}

void PostRequest::handle_finish_errors(Database& database) {
    check_finish_fields();
    check_finish_user(database);
    check_finish_id(database);
}

void PostRequest::check_finish_fields() {
    if(username == invalid_string || id == invalid_id) {
        throw(new Error("Trips List Bad Request"));
    }
}

void PostRequest::check_finish_user(Database& database) {
    bool correct_username = false;
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            if(user->get_role() == "passenger") {
                throw(new Error("Trips List Permission Denied"));
            }
            correct_username = true;
            break;
        }
    }
    if(!correct_username) {
        throw(new Error("Trips List Not Found "));
    }
}

void PostRequest::check_finish_id(Database& database) {
    bool correct_id = false;
    for(Trip* trip : database.get_trips()) {
        if(trip->get_id() == id && !trip->is_canceled()) {
            if(trip->get_driver_name() != username) {
                throw(new Error("Trips List Permission Denied"));
            }
            if(trip->get_status() != "traveling") {
                throw(new Error("Trips List Permission Denied"));
            }
            correct_id = true;
            break;
        }
    }
    if(!correct_id) {
        throw(new Error("Trips List Not Found"));
    }
}