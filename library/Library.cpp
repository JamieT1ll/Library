/*
Name: Jamie Till
Matric number: 2505749
Module code: AC21008
*/

#include "Library.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

Library::Library() {
    users.reserve(100);
    inventory.reserve(100);
}

void Library::addBook(const Book& book) {
    inventory.push_back(book);
    booksSet.insert(book);
}

void Library::removeBook(const std::string& ISBN) {
    auto it = std::remove_if(inventory.begin(), inventory.end(),
                             [&ISBN](const Book& book) { return book.getISBN() == ISBN; });
    inventory.erase(it, inventory.end());
    booksSet.erase(Book("", "", ISBN));
}

void Library::displayAvailableBooks() const {
    for (const Book& book : inventory) {
        if (book.isAvailable()) {
            std::cout << "ISBN: " << book.getISBN() << ", Title: \"" << book.getTitle()
                      << "\", Author: \"" << book.getAuthor() << "\"" << std::endl;
        }
    }
}

void Library::borrowBook(User& user, const Book& book) {
    user.borrowBook(book);

    //Use iterators to find book within our inventory.txt file
    auto it = std::find(inventory.begin(), inventory.end(), book);

    if (it != inventory.end()) {
        //Update book availability
        it->setAvailable(false);
    } else {
        std::cerr << "Error: Book not found in the inventory." << std::endl;
    }

}

void Library::returnBook(User& user, const Book& book) {
    user.returnBook(book);
    book.setAvailable(true);  //Set book availability
    user.updateBookAvailability(book, true);  //Set user's book availability
}

void Library::displayAllUsers() const {
    for (const User& user : users) {
        std::cout << "User ID: " << user.getUserID() << ", Name: " << user.getName() << std::endl;

        // Display the borrowed books
        const std::unordered_set<Book, BookHasher>& borrowedBooks = user.getBorrowedBooksSet();
        for (const Book& borrowedBook : borrowedBooks) {
            std::cout << "  Borrowed Book: " << borrowedBook.getTitle() << std::endl;
        }
    }
}

Book* Library::findBook(const std::string& title) const {
    for (const Book& book : inventory) {
        if (book.getTitle() == title) {
            return const_cast<Book*>(&book);
        }
    }
    return nullptr;
}

void Library::addUser(const User& user) {
    users.push_back(user);
    usersSet.insert(user);
}

void Library::removeUser(const std::string& userID) {
    auto it = std::remove_if(users.begin(), users.end(),
                             [&userID](const User& user) { return user.getUserID() == userID; });
    users.erase(it, users.end());
    //Also remove from the set
    usersSet.erase(User(userID, "")); 
}

void Library::searchBooks(const std::string& searchTerm) const {
    std::cout << "Search results for \"" << searchTerm << "\":" << std::endl;

    for (const Book& book : inventory) {
        //Go through all books in inventory, and Check if the search term matches either the author's name or book title
        if (book.getAuthor().find(searchTerm) != std::string::npos ||
            book.getTitle().find(searchTerm) != std::string::npos) {
            std::cout << "ISBN: " << book.getISBN()
                      << ", Title: \"" << book.getTitle()
                      << "\", Author: \"" << book.getAuthor()
                      << "\", Available: " << (book.isAvailable() ? "Yes" : "No") << std::endl;
        }
    }
}

void Library::loadInitialData(const std::string& usersFile, const std::string& inventoryFile) {
    //Load users from users.txt
    std::ifstream usersInput(usersFile);
    std::string userID, userName;
    while (usersInput >> userID) {
        std::getline(usersInput, userName);
        //Remove spaces from name
        userName = userName.substr(userName.find_first_not_of(" \t"),
                                    userName.find_last_not_of(" \t") + 1);
        users.emplace_back(userID, userName);
    }
    usersInput.close();

    //Load the books from inventory.txt
    std::ifstream inventoryInput(inventoryFile);
    std::string ISBN, title, author, borrowedFlag;
    while (inventoryInput >> std::quoted(ISBN) >> std::quoted(title) >> std::quoted(author) >> borrowedFlag) {
        bool isBorrowed = (borrowedFlag == "1");
        inventory.emplace_back(title, author, ISBN);
        inventory.back().setAvailable(!isBorrowed);  // Set availability based on the loaded value
    }
    inventoryInput.close();
}

void Library::saveLibraryState(const std::string& usersFile, const std::string& inventoryFile) const {
    //Save users to users.txt
    std::ofstream usersOutput(usersFile);
    for (const User& user : users) {
        usersOutput << user.getUserID() << " " << user.getName() << std::endl;
    }
    usersOutput.close();

    // Save books to inventory.txt
    std::ofstream inventoryOutput(inventoryFile);
    for (const Book& book : inventory) {
        inventoryOutput << std::quoted(book.getISBN()) << " " << std::quoted(book.getTitle()) << " "
                        << std::quoted(book.getAuthor()) << " " << (book.isAvailable() ? "0" : "1") << std::endl;
    }
    inventoryOutput.close();
}

