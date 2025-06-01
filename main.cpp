#include <iostream>

#include "character.h"
#include <limits>

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
        case 2: {
            int characterCount = 0;
            character* characters = loadCharacters("data/characters.txt", characterCount);
            if (characters != nullptr && characterCount > 0) {
                selectCharacter(characters, characterCount);
                freeCharactersArray(characters, characterCount);
            } else {
                std::cout << "No characters found or error loading characters.\n";
            }
            start();
            break;
        }
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
