/**
 * @mainpage
 * @par Rpg Generator
 * Aplikacja umożliwia tworzenie i zarządzanie postaciami w grze RPG. Użytkownik może stworzyć nową postać, wybierając jej rasę, klasę, atrybuty i wyposażenie. Dane są zapisywane w plikach tekstowych, co umożliwia ich łatwe wczytywanie i modyfikację.
 * @author Michał Szajner
 * @date 2025-06-01
 */

/**
 * @file main.cpp
 * @brief Główny plik programu generatora postaci RPG
 * 
 * Zawiera funkcję main oraz funkcje obsługujące główne menu programu.
 * Plik odpowiada za inicjalizację i kontrolę przepływu programu.
 *
 * @author Michał Szajner
 * @date 2025-06-01
 */
#include <iostream>
#include "character.h"
#include <limits>

/**
 * @brief Obsługuje główne menu programu i interakcję z użytkownikiem
 * 
 * Funkcja wyświetla menu główne i obsługuje wybory użytkownika w pętli,
 * umożliwiając tworzenie nowych postaci, wczytywanie istniejących
 * lub zakończenie programu.
 */
void start() {
    while (true) {
        std::cout << std::endl;
        std::cout << "Press 1 to create a new character\n";
        std::cout << "Press 2 to load an existing characters\n";
        std::cout << "Press 3 to exit\n";

        int choice;
        std::cin >> choice;
        
        // Walidacja wprowadzonych danych
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                // Tworzenie nowej postaci
                createCharacter();
                break;
            case 2: {
                // Wczytywanie istniejących postaci
                int characterCount = 0;
                character* characters = loadCharacters("data/characters.txt", characterCount);

                if (characters != nullptr && characterCount > 0) {
                    selectCharacter(characters, characterCount);
                } else {
                    std::cout << "No characters found or error loading characters.\n";
                }

                // Zawsze zwalniaj pamięć, nawet jeśli nie znaleziono postaci
                if (characters != nullptr) {
                    freeCharactersArray(characters, characterCount);
                }
                break;
            }
            case 3:
                // Wyjście z programu
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

/**
 * @brief Funkcja główna programu
 * 
 * Inicjalizuje program, wyświetla tytuł aplikacji i uruchamia
 * główne menu poprzez wywołanie funkcji start().
 * 
 * @return Kod zakończenia programu (0 oznacza sukces)
 */
int main() {
    std::cout << "RPG Character Generator\n";
    std::cout << "======================\n";

    start();

    return 0;
}
