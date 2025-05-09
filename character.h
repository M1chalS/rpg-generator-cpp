#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include "item.h"

// Rasy w typie wyliczeniowym
enum class Race {
    HUMAN,
    ELF,
    DWARF,
    ORC,
    GNOME
};

// Struktura atrybutów postaci
struct Attributes {
    int strength; // Siła
    int dexterity; // Zręczność
    int intelligence; // Inteligencja
    int wisdom; // Mądrość
    int charisma; // Charyzma
};

// Struktura postaci
struct character {
    std::string name; // Imię postaci
    Race race; // Rasa postaci
    CharacterClass characterClass; // Klasa postaci
    Attributes baseAttributes; // Bazowe statystyki bez bonusów
    Attributes attributes; // Statystyki z uwzględnieniem bonusów z przedmiotów
    Item* inventory; // Dynamiczna tablica przedmiotów
    int inventorySize; // Rozmiar tablicy inventory jako osobna zmienna po zmianie z std::vector
    float maxCarryWeight; // Maksymalna waga, jaką postać może nosić
    float currentWeight; // Aktualna waga przedmiotów w inwentarzu
};

Race selectRace();
CharacterClass selectClass();
Attributes selectAttributes();
std::string getCharacterName();
void displayCharacter(const character& character);
void displayInventory(const character& character);
void saveCharacter(const character& character, const std::string& filename = "data/characters.txt");
character* loadCharacters(const std::string& filename, int& characterCount);
void createCharacter();
void selectCharacter(const character* characters, int characterCount);
void addItemToInventory(character& character, const Item& item);
void removeItemFromInventory(character& character, int itemIndex);
void manageInventory(character& character);
void freeCharacterMemory(character& character);
void freeCharactersArray(character* characters, int characterCount);

#endif