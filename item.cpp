//
// Created by Michał Szajner on 22/03/2025.
//

#include "item.h"
#include "character.h"

const int BASE_CARRY_WEIGHT = 20.0f;

// Initialize available items
std::vector<Item> initializeItems() {
    std::vector<Item> availableItems;

    // Warrior items
    availableItems.push_back({"Steel Sword", 5.0f, {CharacterClass::WARRIOR, CharacterClass::RANGER}, "A sturdy steel blade"});
    availableItems.push_back({"Shield", 4.0f, {CharacterClass::WARRIOR, CharacterClass::CLERIC}, "A defensive shield"});
    availableItems.push_back({"Plate Armor", 15.0f, {CharacterClass::WARRIOR}, "Heavy protective armor"});

    // Mage items
    availableItems.push_back({"Spellbook", 2.0f, {CharacterClass::MAGE}, "A book of arcane spells"});
    availableItems.push_back({"Staff", 3.0f, {CharacterClass::MAGE, CharacterClass::CLERIC}, "A magical staff"});
    availableItems.push_back({"Robe", 2.0f, {CharacterClass::MAGE}, "Enchanted robes"});

    // Rogue items
    availableItems.push_back({"Dagger", 1.0f, {CharacterClass::ROGUE, CharacterClass::RANGER}, "A sharp dagger"});
    availableItems.push_back({"Lockpick Set", 0.5f, {CharacterClass::ROGUE}, "Tools for opening locks"});
    availableItems.push_back({"Leather Armor", 7.0f, {CharacterClass::ROGUE, CharacterClass::RANGER}, "Light flexible armor"});

    // Cleric items
    availableItems.push_back({"Holy Symbol", 0.5f, {CharacterClass::CLERIC}, "A religious icon"});
    availableItems.push_back({"Mace", 4.0f, {CharacterClass::CLERIC, CharacterClass::WARRIOR}, "A blunt weapon"});

    // Ranger items
    availableItems.push_back({"Bow", 2.0f, {CharacterClass::RANGER}, "A wooden longbow"});
    availableItems.push_back({"Quiver", 1.0f, {CharacterClass::RANGER}, "Holds 20 arrows"});

    // Universal items
    availableItems.push_back({"Potion", 0.5f, {CharacterClass::WARRIOR, CharacterClass::MAGE, CharacterClass::ROGUE, CharacterClass::CLERIC, CharacterClass::RANGER}, "Healing potion"});
    availableItems.push_back({"Backpack", 1.0f, {CharacterClass::WARRIOR, CharacterClass::MAGE, CharacterClass::ROGUE, CharacterClass::CLERIC, CharacterClass::RANGER}, "Increases carrying capacity"});

    return availableItems;
}

// Check if item is compatible with character class
bool isItemCompatible(const Item& item, CharacterClass playerClass) {
    for (const auto& compatibleClass : item.compatibleClasses) {
        if (compatibleClass == playerClass) {
            return true;
        }
    }
    return false;
}

// Select equipment for character
void selectEquipment(character& character) {
    std::vector<Item> availableItems = initializeItems();
    std::vector<Item> compatibleItems;

    // Set max carry weight based on strength
    character.maxCarryWeight = BASE_CARRY_WEIGHT + (character.attributes.strength * 2.0f);
    character.currentWeight = 0.0f;

    // Filter items based on character class
    for (const auto& item : availableItems) {
        if (isItemCompatible(item, character.characterClass)) {
            compatibleItems.push_back(item);
        }
    }

    std::cout << "\nSelect equipment for your character\n";
    std::cout << "Maximum carry weight: " << character.maxCarryWeight << " lbs\n";

    bool selecting = true;
    while (selecting) {
        std::cout << "\nAvailable items for your class:\n";

        // Display available items
        for (size_t i = 0; i < compatibleItems.size(); i++) {
            std::cout << i + 1 << ". " << compatibleItems[i].name
                      << " (Weight: " << compatibleItems[i].weight
                      << " lbs) - " << compatibleItems[i].description << "\n";
        }

        std::cout << "0. Finish selecting items\n";
        std::cout << "Current weight: " << character.currentWeight << "/"
                  << character.maxCarryWeight << " lbs\n";

        int choice;
        std::cout << "Select an item to add (0-" << compatibleItems.size() << "): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 0 || choice > static_cast<int>(compatibleItems.size())) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        if (choice == 0) {
            selecting = false;
            continue;
        }

        // Check if adding this item would exceed weight limit
        if (character.currentWeight + compatibleItems[choice - 1].weight > character.maxCarryWeight) {
            std::cout << "Cannot add this item. It would exceed your maximum carry weight.\n";
            continue;
        }

        // Add item to inventory
        character.inventory.push_back(compatibleItems[choice - 1]);
        character.currentWeight += compatibleItems[choice - 1].weight;

        std::cout << "Added " << compatibleItems[choice - 1].name << " to your inventory.\n";
    }
}