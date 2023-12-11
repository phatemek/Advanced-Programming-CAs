#ifndef __UTAXI__
#define __UTAXI__
#include "Database.hpp"
#include "Error.hpp"
#include "IOHandler.hpp"
#include "CLRequest.hpp"
#include "PostRequest.hpp"
#include "GetRequest.hpp"
#include "DeleteRequest.hpp"

const int request_type_index = 0;
const int request_command_index = 1;
const int sort_by_cost_index = 5;

class UTaxi {
private:
    Database& database;
    IOHandler iohandler;
public:
    UTaxi(std::string _filename, Database& _database);
    void run();
};

#endif