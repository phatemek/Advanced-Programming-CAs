#include "UTaxi.hpp"
#include <string>
#include <iostream>
using namespace std;

UTaxi::UTaxi(string _filename, Database& _database) : database(_database), iohandler(_filename) {}

void UTaxi::run() {
    iohandler.read_location(database);
}
