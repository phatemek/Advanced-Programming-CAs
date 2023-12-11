#ifndef __DOCUMENT__HH__
#define __DOCUMENT__HH__
#include <string>

class Document {
protected:
    std::string type;
    std::string document_title;
    int borrowed_days;
    int initial_return_deadline;
    int return_deadline;
    bool is_borrowed;
    int extention_count;
public:
    std::string get_title();
    bool get_is_borrowed();
    void get_borrowed();
    std::string get_type();
    int get_borrowed_days();
    bool return_deadline_reached();
    bool extention_count_exceeded();
    void extend();
    void add_to_borrowed_days(int days);
    void reset();
    virtual int calculate_penalty() = 0;
};

#endif