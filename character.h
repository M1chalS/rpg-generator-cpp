#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <vector>
#include "item.h"

// Define character races
enum class Race {
    HUMAN,
    ELF,
    DWARF,
    ORC,
    GNOME
};

// Character attributes
struct Attributes {
    int strength;
    int dexterity;
    int intelligence;
    int wisdom;
    int charisma;
};

// Character structure
struct character {
    std::string name;
    Race race;
    CharacterClass characterClass;
    Attributes baseAttributes;  // Bazowe statystyki bez bonusów
    Attributes attributes;      // Statystyki z uwzględnieniem bonusów z przedmiotów
    std::vector<Item> inventory;
    float maxCarryWeight;
    float currentWeight;
};

Race selectRace();
CharacterClass selectClass();
Attributes selectAttributes();
std::string getCharacterName();
void displayCharacter(const character& character);
void displayInventory(const character& character);
void saveCharacter(const character& character, const std::string& filename);
std::vector<character> loadCharacters(const std::string& filename);
void createCharacter();
void selectCharacter(const std::vector<character> &characters);

#endif