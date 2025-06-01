#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "types.h"

enum class CharacterClass {
    WARRIOR,
    MAGE,
    ROGUE,
    CLERIC,
    RANGER
};

struct Item {
    std::string name; // Nazwa przedmiotu
    float weight; // Waga przedmiotu
    CharacterClass* compatibleClasses; // Klasy postaci, które mogą używać przedmiotu
    int compatibleClassesCount; // Liczba kompatybilnych klas
    std::string description; // Opis przedmiotu

    // Bonusy do statystyk postaci
    int strengthBonus;
    int dexterityBonus;
    int intelligenceBonus;
    int wisdomBonus;
    int charismaBonus;

    // Konstruktor i destruktor
    Item();
    ~Item();
    Item(const Item& other); // Konstruktor kopiujący
    Item& operator=(const Item& other); // Operator przypisania
};

Item* initializeItems(int& itemCount);
bool isItemCompatible(const Item& item, CharacterClass playerClass);
void selectEquipment(character& character);
void applyItemBonuses(character& character, const Item& item, bool adding);
void recalculateStats(character& character);

#endif