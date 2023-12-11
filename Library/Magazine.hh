#ifndef __MAGAZINE__HH__
#define __MAGAZINE__HH__
#include "Document.hh"

class Magazine : public Document {
private:
    int year;
    int number;
public:
    Magazine(std::string _magazine_title, int _year, int _number);
    virtual int calculate_penalty();
};

#endif