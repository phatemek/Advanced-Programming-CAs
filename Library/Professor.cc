#include "Professor.hh"
using namespace std;

const int max_prof_borrows = 5;

Professor::Professor(string _prof_name) {
    name = _prof_name;
    penalty = 0;
    max_allowed_borrows = max_prof_borrows;
}