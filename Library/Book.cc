#include "Book.hh"
#include <string>
using namespace std;

const int book_return_deadline = 10;
const int book_7_day_delay_penalty = 2000;
const int book_21_delay_penalty = 3000;
const int book_more_delay_penalty = 5000;

Book::Book(string _book_title) {
    type = "book";
    document_title = _book_title;
    initial_return_deadline = book_return_deadline;
    return_deadline = book_return_deadline;
    is_borrowed = false;
    extention_count = 0;
    borrowed_days = 0;
}

int Book::calculate_penalty() {
    int delay = borrowed_days - return_deadline;
    if(delay <= 0) 
        return 0;

    else if(delay <= 7)
        return (delay * book_7_day_delay_penalty);
    
    else if(delay <= 21)
        return (7 * book_7_day_delay_penalty + (delay - 7) * book_21_delay_penalty);

    else
        return (7 * book_7_day_delay_penalty + 14 * book_21_delay_penalty + (delay - 21) * book_more_delay_penalty);
}