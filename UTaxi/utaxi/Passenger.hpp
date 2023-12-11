#ifndef __PASSENGER__
#define __PASSENGER__
#include "User.hpp"

class Passenger : public User {
protected:
public:
    Passenger(std::string _username, std::string _role);
};

#endif