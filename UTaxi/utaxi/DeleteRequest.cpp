#include "DeleteRequest.hpp"
using namespace std;

DeleteRequest::DeleteRequest() {
    username = invalid_string;
    id = invalid_id;
}

void DeleteRequest::set_username(std::string _username) {
    username = _username;
}

void DeleteRequest::set_id(int _id) {
    id = _id;
}

void DeleteRequest::delete_trip(Database& database) {
    handle_errors(database);
    for(Trip* trip : database.get_trips()) {
        if(trip->get_id() == id) {
            trip->cancel();
            break;
        }
    }
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            user->set_free();
            break;
        }
    }
}

void DeleteRequest::handle_errors(Database& database) {
    check_fields(database);
    check_username(database);
    check_id(database);
    check_trip(database);
}

void DeleteRequest::check_fields(Database& database) {
    if(username == invalid_string || id == invalid_id) {
        throw(new Error("Delete Bad Request"));
    }
}

void DeleteRequest::check_username(Database& database) {
    bool correct_username = false;
    for(User* user : database.get_users()) {
        if(user->get_username() == username) {
            if(user->get_role() == "driver") {
                throw(new Error("Delete Permission Denied"));
            }
            correct_username = true;
            break;
        }
    }
    if(!correct_username) {
        throw(new Error("Delete Not Found"));
    }
}

void DeleteRequest::check_id(Database& database) {
    bool correct_id = false;
    for(Trip* trip : database.get_trips()) {
        if(trip->get_id() == id && !trip->is_canceled()) {
            correct_id = true;
            break;
        }
    }
    if(!correct_id) {
        throw(new Error("Delete Not Found"));
    }
}

void DeleteRequest::check_trip(Database& database) {
    for(Trip* trip : database.get_trips()) {
        if(trip->get_id() == id) {
            if(trip->is_canceled()) {
                throw(new Error("Delete Not Found"));
            }
            if(trip->get_passenger_name() != username) {
                throw(new Error("Delete Permission Denied"));
            }
            if(trip->get_status() != "waiting") {
                throw(new Error("Delelte Bad Request"));
            }
        }
    }
}