#include "User.hpp"
using namespace std;

User::User(string _username, string _role) {
    username = _username;
    role = _role;
    is_busy = false;
}

void User::set_busy() {
    is_busy = true;
}

void User::set_free() {
    is_busy = false;
}

std::string User::get_username() {
    return username;
}

std::string User::get_role() {
    return role;
}

bool User::get_is_busy() {
    return is_busy;
}
