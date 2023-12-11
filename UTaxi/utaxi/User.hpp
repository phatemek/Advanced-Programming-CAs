#ifndef __USER__
#define __USER__
#include <string>

class User{
protected:
    std::string username;
    std::string role;
    bool is_busy;
public:
    User(std::string _username, std::string _role);
    void set_busy();
    void set_free();
    std::string get_username();
    std::string get_role();
    bool get_is_busy();
};

#endif