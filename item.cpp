//
// Created by Michał Szajner on 22/03/2025.
//

#include "item.h"
#include "character.h"
#include <fstream>
#include <sstream>

const int BASE_CARRY_WEIGHT = 20.0f;

// Initialize available items
std::vector<Item> initializeItems() {
    std::vector<Item> availableItems;
    std::ifstream file("./data/items.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open items.txt" << std::endl;
        return availableItems;
    }

    std::string line;
    std::string name, description;
    float weight = 1.0f;
    std::vector<CharacterClass> compatibleClasses;
    bool inItem = false;

    while (std::getline(file, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        if (!line.empty()) {
            line.erase(line.find_last_not_of(" \t") + 1);
        }

        if (line.empty()) continue;

        if (line == "ITEM") {
            // Start of a new item
            inItem = true;
            name = "";
            description = "";
            weight = 1.0f;
            compatibleClasses.clear();
        } else if (line == "END_ITEM") {
            if (!name.empty()) {
                availableItems.push_back({name, weight, compatibleClasses, description});
            }
            inItem = false;
        } else if (inItem) {
            // Parse item properties
            size_t colonPos = line.find(":");
            if (colonPos != std::string::npos) {
                std::string key = line.substr(0, colonPos);
                std::string value = line.substr(colonPos + 1);

                // Trim whitespace
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                if (key == "name") {
                    name = value;
                } else if (key == "weight") {
                    try {
                        weight = std::stof(value);
                    } catch (...) {
                        std::cerr << "Invalid weight value: " << value << std::endl;
                    }
                } else if (key == "classes") {
                    // Parse comma-separated classes
                    std::istringstream classStream(value);
                    std::string classStr;
                    while (std::getline(classStream, classStr, ',')) {
                        // Trim whitespace
                        classStr.erase(0, classStr.find_first_not_of(" \t"));
                        classStr.erase(classStr.find_last_not_of(" \t") + 1);

                        if (classStr == "WARRIOR") compatibleClasses.push_back(CharacterClass::WARRIOR);
                        else if (classStr == "MAGE") compatibleClasses.push_back(CharacterClass::MAGE);
                        else if (classStr == "ROGUE") compatibleClasses.push_back(CharacterClass::ROGUE);
                        else if (classStr == "CLERIC") compatibleClasses.push_back(CharacterClass::CLERIC);
                        else if (classStr == "RANGER") compatibleClasses.push_back(CharacterClass::RANGER);
                    }
                } else if (key == "description") {
                    description = value;
                }
            }
        }
    }

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