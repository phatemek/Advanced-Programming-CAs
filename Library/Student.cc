#include "Student.hh"
#include <string>
using namespace std;

const int max_student_borrows = 2;

Student::Student(string _student_name, string _student_id) {
    student_id = _student_id;
    name = _student_name;
    penalty = 0;
    max_allowed_borrows = max_student_borrows;
}