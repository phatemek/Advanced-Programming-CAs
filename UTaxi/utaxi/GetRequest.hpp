#ifndef __GetRequest__
#define __GetRequest__
#include "CLRequest.hpp"

class GetRequest : public CLRequest {
protected:
    std::string username;
    int id;
    std::string origin;
    std::string destination;
    std::string is_in_hurry;
    std::string sort_by_cost;
public:
    GetRequest();
    void set_username(std::string _username);
    void set_id(int _id);
    void set_origin(std::string _origin);
    void set_destination(std::string _destination);
    void set_in_hurry(std::string _is_in_hurry);
    void set_sort_by_cost(std::string _sort_by_cost);
    double get_cost(Database& database);
    void handle_trips_errors(Database& database);
    void check_trips_fields();
    void check_username(Database& database, std::string command_user);
    double calculate_price(std::vector<Location*> locations);
    void handle_get_cost_errors(Database& database);
    void check_get_cost_fields();
    void check_cost_usernames(Database& database, IOHandler& iohandler);
    void check_cost_locations(Database& database);
};

#endif