#ifndef __STUDENT__HH__
#define __STUDENT__HH__
#include "Person.hh"

class Student : public Person {
protected:
    std::string student_id;
public:
    Student(std::string _student_name, std::string _student_id);
};

#endif