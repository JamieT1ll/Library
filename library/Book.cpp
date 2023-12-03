/*
Name: Jamie Till
Matric number: 2505749
Module code: AC21008
*/


#include "Book.h"

std::size_t BookHasher::operator()(const Book& book) const {
    std::hash<std::string> hasher;
    return hasher(book.getTitle()) ^ hasher(book.getAuthor()) ^ hasher(book.getISBN());
}

namespace std {
    size_t hash<Book>::operator()(const Book& b) const {
        return 0; 
    }
}

Book::Book(const std::string& title, const std::string& author, const std::string& ISBN)
    : title(title), author(author), ISBN(ISBN), available(true) {}

const std::string& Book::getTitle() const {
    return title;
}

const std::string& Book::getAuthor() const {
    return author;
}

const std::string& Book::getISBN() const {
    return ISBN;
}

void Book::setAvailable(bool available) {
    this->available = available;
}

 //This version can be called on const Book objects
void Book::setAvailable(bool available) const {
  
}

bool Book::isAvailable() const {
    return available;
}

bool Book::operator==(const Book& other) const {
    return ISBN == other.ISBN; //Use ISBN as an unique identifier for a book
}

