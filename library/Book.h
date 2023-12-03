/*
Name: Jamie Till
Matric number: 2505749
Module code: AC21008
*/

#ifndef BOOK_H
#define BOOK_H

#include <string>

// Represents a book in the library system.
class Book {
public:
    // Constructors
    Book(const std::string& title, const std::string& author, const std::string& ISBN);

    // Accessor methods
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getISBN() const;
    bool isAvailable() const;
    void setAvailable(bool available);
     void setAvailable(bool available) const;

    // Comparison operator for book equality
    bool operator==(const Book& other) const;

private:
    std::string title;
    std::string author;
    std::string ISBN;
    bool available;
};

// Hash function for Book to enable usage in unordered containers
struct BookHasher {
    std::size_t operator()(const Book& book) const;
};

// Specialization of std::hash for Book
namespace std {
    template <>
    struct hash<Book> {
        size_t operator()(const Book& b) const;
    };
}

#endif // BOOK_H

