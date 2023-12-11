#ifndef __BOOK__HH__
#define __BOOK__HH__
#include "Document.hh"

class Book : public Document {
private:
public:
    Book(std::string _book_title);
    virtual int calculate_penalty();
};

#endif