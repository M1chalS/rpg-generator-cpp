#include <iostream>

#include "character.h"

void start() {
    std::cout << std::endl;
    std::cout << "Press 1 to create a new character\n";
    std::cout << "Press 2 to load an existing characters\n";
    std::cout << "Press 3 to exit\n";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (choice) {
        case 1:
            createCharacter();
            start();
            break;
        case 2:
            selectCharacter(loadCharacters("data/characters.txt"));
            start();
            break;
        case 3:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            start();
            break;
    }
}

int main() {
    std::cout << "RPG Character Generator\n";
    std::cout << "======================\n";

    start();

    return 0;
}
