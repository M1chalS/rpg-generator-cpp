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
    std::string name;
    float weight;
    std::vector<CharacterClass> compatibleClasses;
    std::string description;
};

std::vector<Item> initializeItems();
bool isItemCompatible(const Item& item, CharacterClass playerClass);
void selectEquipment(character& character);

#endif