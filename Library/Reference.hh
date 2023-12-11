#ifndef __REFERENCE__HH__
#define __REFERENCE__HH__
#include "Document.hh"

class Reference : public Document {
private:
public:
    Reference(std::string _reference_title);
    virtual int calculate_penalty();
};

#endif