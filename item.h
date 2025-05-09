#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
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
    std::vector<CharacterClass> compatibleClasses; // Klasy postaci, które mogą używać przedmiotu
    std::string description; // Opis przedmiotu

    // Bonusy do statystyk postaci
    int strengthBonus;
    int dexterityBonus;
    int intelligenceBonus;
    int wisdomBonus;
    int charismaBonus;
};

Item* initializeItems(int& itemCount);
bool isItemCompatible(const Item& item, CharacterClass playerClass);
void selectEquipment(character& character);
void applyItemBonuses(character& character, const Item& item, bool adding);
void recalculateStats(character& character);

#endif
