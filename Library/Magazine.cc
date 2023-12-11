#include "Magazine.hh"
#include <string>
using namespace std;

const int magazine_return_deadline = 2;
const int magazine_special_year = 1390;
const int magazine_before_special_year_penalty = 2000;
const int magazine_after_special_year_penalty = 3000;

Magazine::Magazine(string _magazine_title, int _year, int _number) {
    type = "magazine";
    document_title = _magazine_title;
    year = _year;
    number = _number;
    initial_return_deadline = magazine_return_deadline;
    return_deadline = magazine_return_deadline;
    is_borrowed = false;
    extention_count = 0;
    borrowed_days = 0;
}

int Magazine::calculate_penalty() {
    int delay = borrowed_days - return_deadline;
    if(delay <= 0)
        return 0;

    else if(year < magazine_special_year)
        return (delay * magazine_before_special_year_penalty);
        
    else
        return (delay * magazine_after_special_year_penalty);
}