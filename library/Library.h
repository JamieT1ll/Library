/*
Name: Jamie Till
Matric number: 2505749
Module code: AC21008
*/

#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <unordered_set>
#include <vector>

// Represents a simple library system with books and users.
class Library {
public:
    Library();  // Constructor

    // Basic operations on books and users
    void addBook(const Book& book);
    void removeBook(const std::string& ISBN);
    void displayAvailableBooks() const;
    void displayAllUsers() const;
    Book* findBook(const std::string& title) const;
    void addUser(const User& user);
    void removeUser(const std::string& userID);
    void searchBooks(const std::string& searchTerm) const;

    // File operations
    void loadInitialData(const std::string& usersFile, const std::string& inventoryFile);
    void saveLibraryState(const std::string& usersFile, const std::string& inventoryFile) const;

    // Accessor for the library's book inventory
    const std::vector<Book>& getInventory() const {
        return inventory;
    }

    // Book borrowing and return
    void borrowBook(User& user, const Book& book);
    void returnBook(User& user, const Book& book);

private:
    // Data structures for users, books, and borrowed books
    std::vector<User> users;
    std::vector<Book> inventory;
    std::unordered_set<User> usersSet;
    std::unordered_set<Book> booksSet;
    std::unordered_set<Book, BookHasher> borrowedBooksSet;
};

#endif // LIBRARY_H

