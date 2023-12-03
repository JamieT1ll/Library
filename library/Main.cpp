/*
Name: Jamie Till
Matric number: 2505749
Module code: AC21008
*/

#include "Library.h"
#include <iostream>

int main() {
    // Create a library instance
    Library library;

    // Scenario 1: Load the sample data files into the system
    library.loadInitialData("users.txt", "inventory.txt");

    // Scenario 2: Add the book "Jingo" by Terry Pratchett to the library
    Book jingoBook("Jingo", "Terry Pratchett", "978-0061059062");
    library.addBook(jingoBook);

    // Scenario 3: Create a user profile for a user called Craig
    User craigUser("106","Craig");

    // Scenario 4: Have Craig borrow "Jingo"
    library.borrowBook(craigUser, jingoBook);

    // Display updated user information
    std::cout << "Updated User Information:" << std::endl;
    library.displayAllUsers();
    std::cout << std::endl;

    // Display updated available books
    std::cout << "Updated Available Books:" << std::endl;
    library.displayAvailableBooks();
    std::cout << std::endl;

    // Scenario 5: Have Craig return "Jingo"
    library.returnBook(craigUser, jingoBook);

    // Display updated user information
    std::cout << "Updated User Information:" << std::endl;
    library.displayAllUsers();
    std::cout << std::endl;

    // Display updated available books
    std::cout << "Updated Available Books:" << std::endl;
    library.displayAvailableBooks();
    std::cout << std::endl;

    // Scenario 6: Search for "Jingo" in the library
    Book* foundBook = library.findBook("Jingo");
    if (foundBook) {
        std::cout << "Book found: " << foundBook->getTitle() << std::endl;
    } else {
        std::cout << "Book not found." << std::endl;
    }

    // Scenario 7: Have Craig borrow "Jingo" again
    library.borrowBook(craigUser, jingoBook);

    // Display updated user information
    std::cout << "Updated User Information:" << std::endl;
    library.displayAllUsers();
    std::cout << std::endl;

    // Display updated available books
    std::cout << "Updated Available Books:" << std::endl;
    library.displayAvailableBooks();
    std::cout << std::endl;

    // Scenario 8: Export the current data
    library.saveLibraryState("users.txt", "inventory.txt");

    return 0;
}

