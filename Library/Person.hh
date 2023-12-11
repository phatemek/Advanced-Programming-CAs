#ifndef __PERSON__HH__
#define __PERSON__HH__
#include "Document.hh"

#include <vector>
#include <string>

class Person {
protected:
    std::string name;
    int max_allowed_borrows;
    int penalty;
    std::vector<Document*> borrowed_documents;
public:
    std::string get_name();
    int get_max_allowed_borrows();
    std::vector<Document*> get_borrowed_documents();
    void borrow_document(Document* document);
    void return_document(int doc);
    void set_penalty();
    int get_penalty();
};

#endif
