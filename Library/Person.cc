#include "Person.hh"
#include <vector>
using namespace std;

string Person::get_name() {
    return name;
}

int Person::get_max_allowed_borrows() {
    return max_allowed_borrows;
}

std::vector<Document*> Person::get_borrowed_documents() {
    return borrowed_documents;
}

void Person::borrow_document(Document* document) {
    borrowed_documents.push_back(document);
}

void Person::return_document(int doc) {
    borrowed_documents.erase(borrowed_documents.begin() + doc);
}

void Person::set_penalty() {
    penalty = 0;
    for(Document* doc : borrowed_documents) {
        penalty += doc->calculate_penalty();
    }
}

int Person::get_penalty() {
    return penalty;
}