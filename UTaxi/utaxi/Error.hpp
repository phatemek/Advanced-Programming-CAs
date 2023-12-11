#ifndef __ERRORS__
#define __ERRORS__
#include <string>

class Error {
private:
    std::string message;
public:
    Error(std::string _message);
    std::string get_message();
};

#endif