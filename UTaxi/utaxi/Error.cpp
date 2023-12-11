#include "Error.hpp"
#include <iostream>
using namespace std;

Error::Error(string _message) {
    message = _message;
}

string Error::get_message() {
    return message;
}