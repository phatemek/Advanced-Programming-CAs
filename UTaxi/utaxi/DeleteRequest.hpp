#ifndef __DELETEREQUEST__
#define __DELETEREQUEST__
#include "CLRequest.hpp"

class DeleteRequest : public CLRequest {
protected:
    std::string username;
    int id;
public:
    DeleteRequest();
    void set_username(std::string _username);
    void set_id(int _id);
    void delete_trip(Database& database);
    void handle_errors(Database& database);
    void check_fields(Database& database);
    void check_username(Database& database);
    void check_id(Database& database);
    void check_trip(Database& database);
};

#endif