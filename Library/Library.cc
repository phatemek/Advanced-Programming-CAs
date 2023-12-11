#include "Library.hh"
#include <iostream>
using namespace std;

Library::Library() {}

bool Library::user_already_exists(string name) {
    for(Person* member : members) {
        if(member->get_name() == name)
            return true;
    }
    return false;
}

bool Library::field_is_empty(string field1, string field2) {
    return (field1.size() == 0 || field2.size() == 0);
}

void Library::add_student_member(string student_id, string student_name) {
    if(user_already_exists(student_name)) {
        cout << "Name already exists" << endl;
        exit(EXIT_SUCCESS);
    }

    if(field_is_empty(student_name, student_id)) {
        cout << "Empty field" << endl;
        exit(EXIT_SUCCESS);;
    }

    Student* student = new Student(student_name, student_id);
    members.push_back(student);
}

void Library::add_prof_member(string prof_name) {
    if(user_already_exists(prof_name)) {
        cout << "Name already exists" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(field_is_empty(prof_name)) {
        cout << "Empty field" << endl;
        exit(EXIT_SUCCESS);;
    }

    Professor* prof = new Professor(prof_name);
    members.push_back(prof);
}

bool Library::title_already_exists(string title) {
    for(Document* doc : documents) {
        if(doc->get_title() == title)
            return true;
    }
    return false;
}

void Library::add_book(string book_title, int copies) {
    if(title_already_exists(book_title)) {
        cout << "A document with the specified name already exists" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(field_is_empty(book_title)) {
        cout << "Empty field" << endl;
        exit(EXIT_SUCCESS);;
    }

    for(int i = 0; i < copies; i++) {
        Book* book = new Book(book_title);
        documents.push_back(book);
    }
}

bool Library::number_is_invalid(int number) {
    return (number <= 0);
}

bool Library::year_is_invalid(int year) {
    return (year <= 0);
}

void Library::add_magazine(string magazine_title, int year, int number, int copies) {
    if(title_already_exists(magazine_title)) {
        cout << "A document with the specified name already exists" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(field_is_empty(magazine_title)) {
        cout << "Empty field" << endl;
        exit(EXIT_SUCCESS);;
    }
    
    if(number_is_invalid(number)) {
        cout << "Invalid number" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(year_is_invalid(year)) {
        cout << "Invalid year" << endl;
        exit(EXIT_SUCCESS);;
    }

    for(int i = 0; i < copies; i++) {
        Magazine* magazine = new Magazine(magazine_title, year, number);
        documents.push_back(magazine);
    }
}

void Library::add_reference(string reference_title, int copies) {
    if(title_already_exists(reference_title)) {
        cout << "A document with the specified name already exists" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(field_is_empty(reference_title)) {
        cout << "Empty field" << endl;
        exit(EXIT_SUCCESS);;
    }

    for(int i = 0; i < copies; i++) {
        Reference* reference = new Reference(reference_title);
        documents.push_back(reference);
    }
}

bool Library::max_borrows_reached(string member_name) {
    for(Person* member : members) {
        if(member->get_name() == member_name) {
            return (member->get_borrowed_documents().size() == member->get_max_allowed_borrows());
        }
    }
    return false;
}

bool Library::document_is_already_borrowed(string member_name, string document_title) {
    for(Person* member : members) {
        if(member->get_name() == member_name) {
            for(Document* doc : member->get_borrowed_documents()) {
                if(doc->get_title() == document_title)
                    return true;
            }
        }
    }
    return false;
}

bool Library::document_does_not_exist(std::string document_title) {
    for(Document* doc : documents) {
        if(doc->get_title() == document_title && !(doc->get_is_borrowed()))
            return false;
    }
    return true;
}

void Library::borrow(string member_name, string document_title) {
    if(max_borrows_reached(member_name)) {
        cout << "Maximum number of allowed borrows exceeded" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(document_is_already_borrowed(member_name, document_title)) {
        cout << "You borrowed this document already" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(document_does_not_exist(document_title)) {
        cout << "This document does not exist" << endl;
        exit(EXIT_SUCCESS);;
    }

    for(Person* member: members) {
        if(member->get_name() == member_name) {
            for(Document* doc : documents) {
                if(doc->get_title() == document_title && !(doc->get_is_borrowed())) {
                    member->borrow_document(doc);
                    doc->get_borrowed();
                    return;
                }
            }
        }
    }
}

bool Library::document_is_magazine(string document_title) {
    for(Document* doc : documents) {
        if(doc->get_title() == document_title) {
            return (doc->get_type() == "magazine");
        }
    }
    return false;
}

bool Library::document_just_borrowed(string member_name, string document_title) {
    for(Person* member : members) {
        if(member->get_name() == member_name) {
            for(Document* doc : member->get_borrowed_documents()) {
                if(doc->get_title() == document_title) {
                    return (doc->get_borrowed_days() == 0);
                }
            }
        }
    }
    return false;
}

bool Library::return_deadline_already_reached(string member_name, string document_title) {
    for(Person* member : members) {
        if(member->get_name() == member_name) {
            for(Document* doc : member->get_borrowed_documents()) {
                if(doc->get_title() == document_title) {
                    return (doc->return_deadline_reached());
                }
            }
        }
    }
    return false;
}

bool Library::extention_count_exceeded(string member_name, string document_title) {
    for(Person* member : members) {
        if(member->get_name() == member_name) {
            for(Document* doc : member->get_borrowed_documents()) {
                if(doc->get_title() == document_title) {
                    return (doc->extention_count_exceeded());
                }
            }
        }
    }
    return false;
}

void Library::extend(string member_name, string document_title) {
    if(!document_is_already_borrowed(member_name, document_title)) {
        cout << "You have not borrowed this document" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(document_is_magazine(document_title)) {
        cout << "You can’t renew magazines" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(document_just_borrowed(member_name, document_title)) {
        cout << "You can’t extend and borrow a document on the same day" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(return_deadline_already_reached(member_name, document_title)) {
        cout << "You can’t renew a document after receiving a penalty" << endl;
        exit(EXIT_SUCCESS);;
    }

    if(extention_count_exceeded(member_name, document_title)) {
        cout << "You can’t renew a document more than two times" << endl;
        exit(EXIT_SUCCESS);;
    }

    for(Person* member : members) {
        if(member->get_name() == member_name) {
            for(Document* doc : member->get_borrowed_documents()) {
                if(doc->get_title() == document_title) {
                    doc->extend();
                }
            }
        }
    }
}

void Library::time_pass(int days) {
    for(Person* member : members) {
        for(Document* doc : member->get_borrowed_documents()) {
            doc->add_to_borrowed_days(days);
        }
        member->set_penalty();
    }
}

void Library::return_document(string member_name, string document_title) {
    for(Person* member : members) {
        if(member->get_name() == member_name) {
            for(int doc = 0; doc < member->get_borrowed_documents().size(); doc++) {
                if(member->get_borrowed_documents()[doc]->get_title() == document_title) {
                    member->get_borrowed_documents()[doc]->reset();
                    member->return_document(doc);
                }
            }
        }
    }
}

int Library::get_total_penalty(string member_name) {
    for(Person* member : members) {
        if(member->get_name() == member_name) {
            return member->get_penalty();
        }
    }
    return 0;
}

vector<string> Library::available_titles() {
    vector<string> available_titles;
    for(Document* doc : documents) {
        if(!doc->get_is_borrowed()) {
            available_titles.push_back(doc->get_title());
        }
    }
    return available_titles;
}
