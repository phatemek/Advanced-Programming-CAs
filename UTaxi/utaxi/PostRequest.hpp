#ifndef __POSTREQUEST__
#define __POSTREQUEST__
#include "CLRequest.hpp"

const int trip_location_count = 2;

class PostRequest : public CLRequest {
protected:
    std::string username;
    std::string role;
    std::string origin;
    std::string destination;
    std::string is_in_hurry;
    int id;
public:
    PostRequest();
    void set_username(std::string _username);
    void set_role(std::string _role);
    void set_origin(std::string _origin);
    void set_destination(std::string _destination);
    void set_in_hurry(std::string _is_in_hurry);
    void set_id(int _id);
    int get_id();
    void signup(Database& database);
    void make_trip(Database& database);
    void accept_trip(Database& database);
    void finish_trip(Database& database);
    void handle_signup_errors(Database& database);
    void check_signup_fields();
    void check_signup_user(Database& database);
    void handle_make_trip_errors(Database& database);
    void check_make_trip_fields();
    void check_locations(Database& database);
    void check_make_trip_user(Database& database);
    void handle_accept_trip_errors(Database& database);
    void check_accept_trip_fields();
    void check_accept_trip_user(Database& database);
    void check_accept_trip_id(Database& database);
    void handle_finish_errors(Database& database);
    void check_finish_fields();
    void check_finish_user(Database& database);
    void check_finish_id(Database& database);
};

#endif
