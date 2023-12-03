/*
Name: Jamie Till
Matric number: 2505749
Module code: AC21008
*/

#include "User.h"

template <class T>
inline void hash_combine(std::size_t& seed, const T& val) {
    seed ^= std::hash<T>{}(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
    size_t hash<User>::operator()(const User& user) const {
        size_t hashValue = 0;
        //Combine the hash values of userID and name
        hash_combine(hashValue, user.getUserID());
        hash_combine(hashValue, user.getName());
        return hashValue;
    }
}

//Constructors
User::User(const std::string& userID, const std::string& userName) : userID(userID), name(userName) {}

User::User(const std::string& userName) : name(userName) {
    //Generates a unique user ID based on the hash of the user's name - Unimplemented in main, but could be
    std::hash<std::string> hasher;
    userID = "ID_" + std::to_string(hasher(userName));
    borrowedBooksSet.reserve(10);
}

//Member functions related to book transactions
void User::borrowBook(const Book& book) {
    borrowedBooksSet.insert(book);
}

void User::returnBook(const Book& book) {
    borrowedBooksSet.erase(book);
}

void User::updateBookAvailability(const Book& book, bool available) {
    auto it = borrowedBooksSet.find(book);
    if (it != borrowedBooksSet.end()) {
        it->setAvailable(available);
    }
}

bool User::hasBorrowedBook(const Book& book) const {
    return borrowedBooksSet.find(book) != borrowedBooksSet.end();
}

//The Accessor methods
const std::string& User::getName() const {
    return name;
}

const std::string& User::getUserID() const {
    return userID;
}

const std::unordered_set<Book, BookHasher>& User::getBorrowedBooksSet() const {
    return borrowedBooksSet;
}

//Comparison
bool User::operator==(const User& other) const {
    return userID == other.userID && name == other.name;
}

