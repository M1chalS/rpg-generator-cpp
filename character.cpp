#include "character.h"

#include <fstream>
#include <limits>
#include <sstream>

const int POINTS_TO_DISTRIBUTE = 10;

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
    Attributes attrs = {5, 5, 5, 5, 5}; // Default values
    int pointsRemaining = POINTS_TO_DISTRIBUTE; // Points to distribute
    int choice;

    std::cout << "You have " << pointsRemaining << " points to distribute among attributes.\n";
    std::cout << "Current attributes:\n";
    std::cout << "1. Strength: " << attrs.strength << "\n";
    std::cout << "2. Dexterity: " << attrs.dexterity << "\n";
    std::cout << "3. Intelligence: " << attrs.intelligence << "\n";
    std::cout << "4. Wisdom: " << attrs.wisdom << "\n";
    std::cout << "5. Charisma: " << attrs.charisma << "\n";

    while (pointsRemaining > 0) {
        std::cout << "Points remaining: " << pointsRemaining << "\n";
        std::cout << "Select attribute to increase (1-5) or 0 to finish: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 0 || choice > 5) {
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
            case 1: attrs.strength += pointsToAdd;
                break;
            case 2: attrs.dexterity += pointsToAdd;
                break;
            case 3: attrs.intelligence += pointsToAdd;
                break;
            case 4: attrs.wisdom += pointsToAdd;
                break;
            case 5: attrs.charisma += pointsToAdd;
                break;
            default: break;
        }

        pointsRemaining -= pointsToAdd;

        // Display updated attributes
        std::cout << "Updated attributes:\n";
        std::cout << "1. Strength: " << attrs.strength << "\n";
        std::cout << "2. Dexterity: " << attrs.dexterity << "\n";
        std::cout << "3. Intelligence: " << attrs.intelligence << "\n";
        std::cout << "4. Wisdom: " << attrs.wisdom << "\n";
        std::cout << "5. Charisma: " << attrs.charisma << "\n";
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
void displayInventory(const character &character) {
    std::cout << "\n===== Equipment =====\n";

    if (character.inventory.empty()) {
        std::cout << "No items in inventory.\n";
    } else {
        std::cout << "Items:\n";
        for (size_t i = 0; i < character.inventory.size(); i++) {
            std::cout << "- " << character.inventory[i].name << " (" << character.inventory[i].weight << " kg)\n";
        }
        std::cout << "Total weight: " << character.currentWeight << "/"
                << character.maxCarryWeight << " kg\n";
    }
}

// Function to display character info
void displayCharacter(const character &character) {
    std::cout << "\n===== Character Sheet =====\n";
    std::cout << "Name: " << character.name << "\n";

    std::cout << "Race: ";
    switch (character.race) {
        case Race::HUMAN: std::cout << "Human";
            break;
        case Race::ELF: std::cout << "Elf";
            break;
        case Race::DWARF: std::cout << "Dwarf";
            break;
        case Race::ORC: std::cout << "Orc";
            break;
        case Race::GNOME: std::cout << "Gnome";
            break;
    }
    std::cout << "\n";

    std::cout << "Class: ";
    switch (character.characterClass) {
        case CharacterClass::WARRIOR: std::cout << "Warrior";
            break;
        case CharacterClass::MAGE: std::cout << "Mage";
            break;
        case CharacterClass::ROGUE: std::cout << "Rogue";
            break;
        case CharacterClass::CLERIC: std::cout << "Cleric";
            break;
        case CharacterClass::RANGER: std::cout << "Ranger";
            break;
    }
    std::cout << "\n";

    std::cout << "Attributes (base + item bonuses):\n";
    std::cout << "  Strength: " << character.baseAttributes.strength;
    if (character.attributes.strength != character.baseAttributes.strength)
        std::cout << " (+" << (character.attributes.strength - character.baseAttributes.strength) << ")";
    std::cout << "\n";

    std::cout << "  Dexterity: " << character.baseAttributes.dexterity;
    if (character.attributes.dexterity != character.baseAttributes.dexterity)
        std::cout << " (+" << (character.attributes.dexterity - character.baseAttributes.dexterity) << ")";
    std::cout << "\n";

    std::cout << "  Intelligence: " << character.baseAttributes.intelligence;
    if (character.attributes.intelligence != character.baseAttributes.intelligence)
        std::cout << " (+" << (character.attributes.intelligence - character.baseAttributes.intelligence) << ")";
    std::cout << "\n";

    std::cout << "  Wisdom: " << character.baseAttributes.wisdom;
    if (character.attributes.wisdom != character.baseAttributes.wisdom)
        std::cout << " (+" << (character.attributes.wisdom - character.baseAttributes.wisdom) << ")";
    std::cout << "\n";

    std::cout << "  Charisma: " << character.baseAttributes.charisma;
    if (character.attributes.charisma != character.baseAttributes.charisma)
        std::cout << " (+" << (character.attributes.charisma - character.baseAttributes.charisma) << ")";
    std::cout << "\n";

    std::cout << "==========================\n";

    displayInventory(character);

    std::cout << "==========================\n";
}

std::vector<character> loadCharacters(const std::string &filename = "data/characters.txt") {
    std::vector<character> characters;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open characters.txt" << std::endl;
        return characters;
    }

    std::string line;
    bool inCharacter = false;
    character currentChar;

    // Initialize default values
    std::string name;
    Race race = Race::HUMAN;
    CharacterClass charClass = CharacterClass::WARRIOR;
    int strength = 5, dexterity = 5, intelligence = 5, wisdom = 5, charisma = 5;
    float maxCarryWeight = 0.0f, currentWeight = 0.0f;
    std::vector<Item> inventory;

    while (std::getline(file, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        if (!line.empty()) {
            line.erase(line.find_last_not_of(" \t") + 1);
        }

        if (line.empty()) continue;

        if (line == "CHARACTER") {
            inCharacter = true;
            // Reset values
            name = "";
            race = Race::HUMAN;
            charClass = CharacterClass::WARRIOR;
            strength = 5;
            dexterity = 5;
            intelligence = 5;
            wisdom = 5;
            charisma = 5;
            maxCarryWeight = 0.0f;
            currentWeight = 0.0f;
            inventory.clear();
        } else if (line == "END_CHARACTER") {
            if (!name.empty()) {
                // Create attributes struct
                Attributes attrs = {
                    strength, dexterity,
                    intelligence, wisdom, charisma
                };

                // Create character and add to vector
                currentChar.name = name;
                currentChar.race = race;
                currentChar.characterClass = charClass;
                currentChar.baseAttributes = attrs;  // Ustaw bazowe atrybuty
                currentChar.attributes = attrs;      // Początkowo takie same jak bazowe
                currentChar.maxCarryWeight = maxCarryWeight;
                currentChar.currentWeight = currentWeight;
                currentChar.inventory = inventory;

                // Przelicz statystyki uwzględniając bonusy z przedmiotów
                recalculateStats(currentChar);

                characters.push_back(currentChar);
            }
            inCharacter = false;
        } else if (inCharacter) {
            if (size_t colonPos = line.find(':'); colonPos != std::string::npos) {
                std::string key = line.substr(0, colonPos);
                std::string value = line.substr(colonPos + 1);

                // Trim whitespace
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                if (key == "name") {
                    name = value;
                } else if (key == "race") {
                    if (value == "HUMAN") race = Race::HUMAN;
                    else if (value == "ELF") race = Race::ELF;
                    else if (value == "DWARF") race = Race::DWARF;
                    else if (value == "GNOME") race = Race::GNOME;
                    else if (value == "ORC") race = Race::ORC;
                } else if (key == "class") {
                    if (value == "WARRIOR") charClass = CharacterClass::WARRIOR;
                    else if (value == "MAGE") charClass = CharacterClass::MAGE;
                    else if (value == "ROGUE") charClass = CharacterClass::ROGUE;
                    else if (value == "CLERIC") charClass = CharacterClass::CLERIC;
                    else if (value == "RANGER") charClass = CharacterClass::RANGER;
                } else if (key == "strength") {
                    strength = std::stoi(value);
                } else if (key == "dexterity") {
                    dexterity = std::stoi(value);
                } else if (key == "intelligence") {
                    intelligence = std::stoi(value);
                } else if (key == "wisdom") {
                    wisdom = std::stoi(value);
                } else if (key == "charisma") {
                    charisma = std::stoi(value);
                } else if (key == "maxCarryWeight") {
                    maxCarryWeight = std::stof(value);
                } else if (key == "currentWeight") {
                    currentWeight = std::stof(value);
                } else if (key == "inventory") {
                    // Parse comma-separated inventory items
                    std::istringstream itemStream(value);
                    std::string itemName;

                    // Get all available items first
                    std::vector<Item> availableItems = initializeItems();

                    while (std::getline(itemStream, itemName, ',')) {
                        // Trim whitespace
                        itemName.erase(0, itemName.find_first_not_of(" \t"));
                        itemName.erase(itemName.find_last_not_of(" \t") + 1);

                        // Find matching item from available items
                        for (size_t i = 0; i < availableItems.size(); i++) {
                            if (availableItems[i].name == itemName) {
                                inventory.push_back(availableItems[i]);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return characters;
}

void saveCharacter(const character &character, const std::string &filename = "data/characters.txt") {
    // Open the file for appending
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing" << std::endl;
        return;
    }

    // Start character block
    file << "CHARACTER\n";
    file << "name: " << character.name << "\n";

    // Save race
    file << "race: ";
    switch (character.race) {
        case Race::HUMAN: file << "HUMAN";
            break;
        case Race::ELF: file << "ELF";
            break;
        case Race::DWARF: file << "DWARF";
            break;
        case Race::ORC: file << "ORC";
            break;
        case Race::GNOME: file << "GNOME";
            break;
    }
    file << "\n";

    // Save class
    file << "class: ";
    switch (character.characterClass) {
        case CharacterClass::WARRIOR: file << "WARRIOR";
            break;
        case CharacterClass::MAGE: file << "MAGE";
            break;
        case CharacterClass::ROGUE: file << "ROGUE";
            break;
        case CharacterClass::CLERIC: file << "CLERIC";
            break;
        case CharacterClass::RANGER: file << "RANGER";
            break;
    }
    file << "\n";

    // Save attributes - zapisujemy tylko bazowe atrybuty
    file << "strength: " << character.baseAttributes.strength << "\n";
    file << "dexterity: " << character.baseAttributes.dexterity << "\n";
    file << "intelligence: " << character.baseAttributes.intelligence << "\n";
    file << "wisdom: " << character.baseAttributes.wisdom << "\n";
    file << "charisma: " << character.baseAttributes.charisma << "\n";

    // Save weights
    file << "maxCarryWeight: " << character.maxCarryWeight << "\n";
    file << "currentWeight: " << character.currentWeight << "\n";

    // Save inventory
    file << "inventory: ";
    bool first = true;
    for (const auto &item: character.inventory) {
        if (!first) {
            file << ",";
        }
        file << item.name;
        first = false;
    }
    file << "\n";

    // End character block
    file << "END_CHARACTER\n\n";

    file.close();
    std::cout << "Character saved to " << filename << std::endl;
}

void createCharacter() {
    character character;

    character.name = getCharacterName();

    character.race = selectRace();

    character.characterClass = selectClass();

    character.attributes = selectAttributes();

    selectEquipment(character);

    saveCharacter(character);

    displayCharacter(character);
}

void selectCharacter(const std::vector<character> &characters) {
    std::cout << "Select a character:\n";
    for (size_t i = 0; i < characters.size(); ++i) {
        std::cout << i + 1 << ". " << characters[i].name << "\n";
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(characters.size())) {
        std::cout << "Invalid choice. Please try again.\n";
        selectCharacter(characters);
    } else {
        displayCharacter(characters[choice - 1]);
    }
}
