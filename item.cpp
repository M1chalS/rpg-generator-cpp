#include "item.h"
#include "character.h"
#include <fstream>
#include <sstream>
#include <limits>

const int BASE_CARRY_WEIGHT = 5.0f;

// Initialize available items
Item* initializeItems(int& itemCount) {
    itemCount = 0;
    Item* availableItems = nullptr;
    std::ifstream file("./data/items.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open items.txt" << std::endl;
        return availableItems;
    }

    // Najpierw policz liczbę przedmiotów
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        if (line.find("ITEM") != std::string::npos) {
            count++;
        }
    }

    // Zresetuj pozycję w pliku
    file.clear();
    file.seekg(0, std::ios::beg);

    // Alokuj pamięć na tablicę przedmiotów
    availableItems = new Item[count];

    std::string name, description;
    float weight = 1.0f;
    std::vector<CharacterClass> compatibleClasses;
    bool inItem = false;
    int currentItemIndex = 0;

    // Domyślne wartości bonusów
    int strengthBonus = 0;
    int dexterityBonus = 0;
    int intelligenceBonus = 0;
    int wisdomBonus = 0;
    int charismaBonus = 0;

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

            // Reset bonusy
            strengthBonus = 0;
            dexterityBonus = 0;
            intelligenceBonus = 0;
            wisdomBonus = 0;
            charismaBonus = 0;
        } else if (line == "END_ITEM") {
            if (!name.empty()) {
                Item newItem = {
                    name,
                    weight,
                    compatibleClasses,
                    description,
                    strengthBonus,
                    dexterityBonus,
                    intelligenceBonus,
                    wisdomBonus,
                    charismaBonus
                };
                availableItems[currentItemIndex] = newItem;
                currentItemIndex++;
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
                } else if (key == "strengthBonus") {
                    try {
                        strengthBonus = std::stoi(value);
                    } catch (...) {
                        std::cerr << "Invalid strength bonus value: " << value << std::endl;
                    }
                } else if (key == "dexterityBonus") {
                    try {
                        dexterityBonus = std::stoi(value);
                    } catch (...) {
                        std::cerr << "Invalid dexterity bonus value: " << value << std::endl;
                    }
                } else if (key == "intelligenceBonus") {
                    try {
                        intelligenceBonus = std::stoi(value);
                    } catch (...) {
                        std::cerr << "Invalid intelligence bonus value: " << value << std::endl;
                    }
                } else if (key == "wisdomBonus") {
                    try {
                        wisdomBonus = std::stoi(value);
                    } catch (...) {
                        std::cerr << "Invalid wisdom bonus value: " << value << std::endl;
                    }
                } else if (key == "charismaBonus") {
                    try {
                        charismaBonus = std::stoi(value);
                    } catch (...) {
                        std::cerr << "Invalid charisma bonus value: " << value << std::endl;
                    }
                }
            }
        }
    }

    itemCount = currentItemIndex;
    return availableItems;
}

// Apply or remove bonuses from an item to character stats
void applyItemBonuses(character& character, const Item& item, bool adding) {
    int multiplier = adding ? 1 : -1;

    character.attributes.strength += item.strengthBonus * multiplier;
    character.attributes.dexterity += item.dexterityBonus * multiplier;
    character.attributes.intelligence += item.intelligenceBonus * multiplier;
    character.attributes.wisdom += item.wisdomBonus * multiplier;
    character.attributes.charisma += item.charismaBonus * multiplier;
}

// Recalculate all stats based on base attributes and item bonuses
void recalculateStats(character& character) {
    // Reset to base attributes
    character.attributes = character.baseAttributes;

    // Apply all item bonuses
    for (int i = 0; i < character.inventorySize; i++) {
        applyItemBonuses(character, character.inventory[i], true);
    }
}

// Check if item is compatible with character class
bool isItemCompatible(const Item& item, CharacterClass playerClass) {
    for (size_t i = 0; i < item.compatibleClasses.size(); i++) {
        if (item.compatibleClasses[i] == playerClass) {
            return true;
        }
    }
    return false;
}

// Select equipment for character
void selectEquipment(character& character) {
    int itemCount = 0;
    Item* availableItems = initializeItems(itemCount);

    // Tworzymy dynamiczną tablicę na zgodne przedmioty
    int compatibleItemsCount = 0;
    Item* compatibleItems = nullptr;

    // Set max carry weight based on strength
    character.maxCarryWeight = BASE_CARRY_WEIGHT + (character.attributes.strength * 2.0f);
    character.currentWeight = 0.0f;

    // Inicjalizacja inwentarza
    character.inventory = nullptr;
    character.inventorySize = 0;

    // Zapisz bazowe atrybuty przed dodaniem bonusów z przedmiotów
    character.baseAttributes = character.attributes;

    // Najpierw zliczamy zgodne przedmioty
    for (int i = 0; i < itemCount; i++) {
        if (isItemCompatible(availableItems[i], character.characterClass)) {
            compatibleItemsCount++;
        }
    }

    // Alokuj pamięć na tablicę zgodnych przedmiotów
    compatibleItems = new Item[compatibleItemsCount];

    // Wypełnij tablicę zgodnych przedmiotów
    int currentIndex = 0;
    for (int i = 0; i < itemCount; i++) {
        if (isItemCompatible(availableItems[i], character.characterClass)) {
            compatibleItems[currentIndex] = availableItems[i];
            currentIndex++;
        }
    }

    std::cout << "\nSelect equipment for your character\n";
    std::cout << "Maximum carry weight: " << character.maxCarryWeight << " kg\n";

    bool selecting = true;
    while (selecting) {
        std::cout << "\nAvailable items for your class:\n";

        // Display available items with their stat bonuses
        for (int i = 0; i < compatibleItemsCount; i++) {
            const Item& item = compatibleItems[i];
            std::cout << i + 1 << ". " << item.name
                      << " (Weight: " << item.weight << " kg) - " << item.description << "\n";

            // Display stat bonuses if they exist
            bool hasBonuses = item.strengthBonus || item.dexterityBonus ||
                              item.intelligenceBonus || item.wisdomBonus ||
                              item.charismaBonus;

            if (hasBonuses) {
                std::cout << "   Bonuses: ";
                if (item.strengthBonus) std::cout << "STR+" << item.strengthBonus << " ";
                if (item.dexterityBonus) std::cout << "DEX+" << item.dexterityBonus << " ";
                if (item.intelligenceBonus) std::cout << "INT+" << item.intelligenceBonus << " ";
                if (item.wisdomBonus) std::cout << "WIS+" << item.wisdomBonus << " ";
                if (item.charismaBonus) std::cout << "CHA+" << item.charismaBonus << " ";
                std::cout << "\n";
            }
        }

        std::cout << "0. Finish selecting items\n";
        std::cout << "Current weight: " << character.currentWeight << "/"
                  << character.maxCarryWeight << " kg\n";

        // Display current stats with applied bonuses
        std::cout << "Current stats with bonuses:\n";
        std::cout << "  Strength: " << character.attributes.strength << "\n";
        std::cout << "  Dexterity: " << character.attributes.dexterity << "\n";
        std::cout << "  Intelligence: " << character.attributes.intelligence << "\n";
        std::cout << "  Wisdom: " << character.attributes.wisdom << "\n";
        std::cout << "  Charisma: " << character.attributes.charisma << "\n";

        int choice;
        std::cout << "Select an item to add (0-" << compatibleItemsCount << "): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 0 || choice > compatibleItemsCount) {
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

        // Tworzenie nowej tablicy o jedną pozycję większej
        Item* newInventory = new Item[character.inventorySize + 1];

        // Kopiowanie istniejących przedmiotów
        for (int i = 0; i < character.inventorySize; i++) {
            newInventory[i] = character.inventory[i];
        }

        // Dodanie nowego przedmiotu
        newInventory[character.inventorySize] = compatibleItems[choice - 1];

        // Zwolnienie starej tablicy
        if (character.inventory != nullptr) {
            delete[] character.inventory;
        }

        // Przypisanie nowej tablicy
        character.inventory = newInventory;
        character.inventorySize++;

        // Aktualizacja wagi i bonusów
        character.currentWeight += compatibleItems[choice - 1].weight;
        applyItemBonuses(character, compatibleItems[choice - 1], true);

        std::cout << "Added " << compatibleItems[choice - 1].name << " to your inventory.\n";
    }

    // Zwolnienie pamięci
    delete[] availableItems;
    delete[] compatibleItems;
}