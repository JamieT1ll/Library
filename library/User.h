/*
Name: Jamie Till
Matric number: 2505749
Module code: AC21008
*/

#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_set>
#include "Book.h"  // Include the necessary header for Book

// Declaration of hash_combine function
template <class T>
inline void hash_combine(std::size_t& seed, const T& val);

// Represents a user in the library system.
class User {
public:
    // Constructors
    User(const std::string& userID, const std::string& userName);
    User(const std::string& userName);

    // Member functions related to book transactions
    void borrowBook(const Book& book);
    void returnBook(const Book& book);
    void updateBookAvailability(const Book& book, bool available);
    bool hasBorrowedBook(const Book& book) const;

    // Accessor methods
    const std::string& getName() const;
    const std::string& getUserID() const;
    const std::unordered_set<Book, BookHasher>& getBorrowedBooksSet() const;

    // Comparison operator for user equality
    bool operator==(const User& other) const;

private:
    std::string userID;
    std::string name;
    std::unordered_set<Book, BookHasher> borrowedBooksSet;
};

// Specialization of std::hash for User to enable usage in unordered containers
namespace std {
    template <>
    struct hash<User> {
        size_t operator()(const User& user) const;
    };
}

#endif  // USER_H

