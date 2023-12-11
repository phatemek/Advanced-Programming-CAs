#include "Reference.hh"
#include <string>
using namespace std;

const int reference_return_deadline = 5;
const int reference_3_day_delay_penalty = 5000;
const int reference_more_delay_penalty = 7000;

Reference::Reference(string _reference_title) {
    type = "reference";
    document_title = _reference_title;
    initial_return_deadline = reference_return_deadline;
    return_deadline = reference_return_deadline;
    is_borrowed = false;
    extention_count = 0;
    borrowed_days = 0;
}

int Reference::calculate_penalty() {
    int delay = borrowed_days - return_deadline;
    if(delay <= 0)
        return 0;

    else if(delay <= 3)
        return (delay * reference_3_day_delay_penalty);

    else
        return (3 * reference_3_day_delay_penalty + (delay - 3) * reference_more_delay_penalty);
}