#ifndef __DRIVER__
#define __DRIVER__
#include "User.hpp"

class Driver : public User {
protected:
public:
    Driver(std::string _username, std::string _role);
};

#endif
