#include "character.h"
#include <limits>

// Function to display race options and get user choice
Race selectRace() {
    int choice;
    std::cout << "Select a race:\n";
    std::cout << "1. Human\n";
    std::cout << "2. Elf\n";
    std::cout << "3. Dwarf\n";
    std::cout << "4. Orc\n";
    std::cout << "5. Gnome\n";

    while (true) {
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please try again.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    switch (choice) {
        case 1: return Race::HUMAN;
        case 2: return Race::ELF;
        case 3: return Race::DWARF;
        case 4: return Race::ORC;
        case 5: return Race::GNOME;
        default: return Race::HUMAN;
    }
}

// Function to display class options and get user choice
CharacterClass selectClass() {
    int choice;
    std::cout << "Select a class:\n";
    std::cout << "1. Warrior\n";
    std::cout << "2. Mage\n";
    std::cout << "3. Rogue\n";
    std::cout << "4. Cleric\n";
    std::cout << "5. Ranger\n";

    while (true) {
        std::cout << "Enter your choice (1-5): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please try again.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    switch (choice) {
        case 1: return CharacterClass::WARRIOR;
        case 2: return CharacterClass::MAGE;
        case 3: return CharacterClass::ROGUE;
        case 4: return CharacterClass::CLERIC;
        case 5: return CharacterClass::RANGER;
        default: return CharacterClass::WARRIOR;
    }
}

// Function to handle attribute selection
Attributes selectAttributes() {
    Attributes attrs = {5, 5, 5, 5, 5, 5}; // Default values
    int pointsRemaining = 10; // Points to distribute
    int choice;

    std::cout << "You have " << pointsRemaining << " points to distribute among attributes.\n";
    std::cout << "Current attributes:\n";
    std::cout << "1. Strength: " << attrs.strength << "\n";
    std::cout << "2. Dexterity: " << attrs.dexterity << "\n";
    std::cout << "3. Constitution: " << attrs.constitution << "\n";
    std::cout << "4. Intelligence: " << attrs.intelligence << "\n";
    std::cout << "5. Wisdom: " << attrs.wisdom << "\n";
    std::cout << "6. Charisma: " << attrs.charisma << "\n";

    while (pointsRemaining > 0) {
        std::cout << "Points remaining: " << pointsRemaining << "\n";
        std::cout << "Select attribute to increase (1-6) or 0 to finish: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 0 || choice > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        if (choice == 0) {
            break;
        }

        int pointsToAdd;
        std::cout << "How many points to add (1-" << pointsRemaining << "): ";
        std::cin >> pointsToAdd;

        if (std::cin.fail() || pointsToAdd < 1 || pointsToAdd > pointsRemaining) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid number of points. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1: attrs.strength += pointsToAdd; break;
            case 2: attrs.dexterity += pointsToAdd; break;
            case 3: attrs.constitution += pointsToAdd; break;
            case 4: attrs.intelligence += pointsToAdd; break;
            case 5: attrs.wisdom += pointsToAdd; break;
            case 6: attrs.charisma += pointsToAdd; break;
            default: break;
        }

        pointsRemaining -= pointsToAdd;

        // Display updated attributes
        std::cout << "Updated attributes:\n";
        std::cout << "1. Strength: " << attrs.strength << "\n";
        std::cout << "2. Dexterity: " << attrs.dexterity << "\n";
        std::cout << "3. Constitution: " << attrs.constitution << "\n";
        std::cout << "4. Intelligence: " << attrs.intelligence << "\n";
        std::cout << "5. Wisdom: " << attrs.wisdom << "\n";
        std::cout << "6. Charisma: " << attrs.charisma << "\n";
    }

    return attrs;
}

// Function to get character name
std::string getCharacterName() {
    std::string name;
    std::cout << "Enter character name: ";
    std::getline(std::cin, name);
    return name;
}

// Display character inventory
void displayInventory(const character& character) {
    std::cout << "\n===== Equipment =====\n";

    if (character.inventory.empty()) {
        std::cout << "No items in inventory.\n";
    } else {
        std::cout << "Items:\n";
        for (const auto& item : character.inventory) {
            std::cout << "- " << item.name << " (" << item.weight << " lbs)\n";
        }
        std::cout << "Total weight: " << character.currentWeight << "/"
                  << character.maxCarryWeight << " lbs\n";
    }
}

// Function to display character info
void displayCharacter(const character& character) {
    std::cout << "\n===== Character Sheet =====\n";
    std::cout << "Name: " << character.name << "\n";

    std::cout << "Race: ";
    switch (character.race) {
        case Race::HUMAN: std::cout << "Human"; break;
        case Race::ELF: std::cout << "Elf"; break;
        case Race::DWARF: std::cout << "Dwarf"; break;
        case Race::ORC: std::cout << "Orc"; break;
        case Race::GNOME: std::cout << "Gnome"; break;
    }
    std::cout << "\n";

    std::cout << "Class: ";
    switch (character.characterClass) {
        case CharacterClass::WARRIOR: std::cout << "Warrior"; break;
        case CharacterClass::MAGE: std::cout << "Mage"; break;
        case CharacterClass::ROGUE: std::cout << "Rogue"; break;
        case CharacterClass::CLERIC: std::cout << "Cleric"; break;
        case CharacterClass::RANGER: std::cout << "Ranger"; break;
    }
    std::cout << "\n";

    std::cout << "Attributes:\n";
    std::cout << "  Strength: " << character.attributes.strength << "\n";
    std::cout << "  Dexterity: " << character.attributes.dexterity << "\n";
    std::cout << "  Constitution: " << character.attributes.constitution << "\n";
    std::cout << "  Intelligence: " << character.attributes.intelligence << "\n";
    std::cout << "  Wisdom: " << character.attributes.wisdom << "\n";
    std::cout << "  Charisma: " << character.attributes.charisma << "\n";

    std::cout << "==========================\n";

    displayInventory(character);

    std::cout << "==========================\n";
}