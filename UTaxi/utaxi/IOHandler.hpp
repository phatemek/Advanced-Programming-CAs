#ifndef __IOHANDLER__
#define __IOHANDLER__
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Database.hpp"
#include "Error.hpp"

const char FILE_DELIMITER = ',';
const char REQUEST_DELIMITER = ' ';

class IOHandler {
private:
    std::string filename;
public:
    IOHandler(std::string _filename);
    void read_location(Database& database);
};

#endif