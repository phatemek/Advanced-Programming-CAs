#include "Document.hh"
using namespace std;

std::string Document::get_title() {
    return document_title;
}

bool Document::get_is_borrowed() {
    return is_borrowed;
}

void Document::get_borrowed() {
    is_borrowed = true;
}

string Document::get_type() {
    return type;
}

int Document::get_borrowed_days() {
    return borrowed_days;
}

bool Document::return_deadline_reached() {
    return (borrowed_days >= return_deadline);
}

bool Document::extention_count_exceeded() {
    return (extention_count >= 2);
}

void Document::extend() {
    return_deadline += initial_return_deadline;
}

void Document::add_to_borrowed_days(int days) {
    borrowed_days += days;
}

void Document::reset() {
    borrowed_days = 0;
    return_deadline = initial_return_deadline;
    is_borrowed = false;
    extention_count = 0;
}
