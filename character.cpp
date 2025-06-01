#include "character.h"

#include <fstream>
#include <sstream>

const int POINTS_TO_DISTRIBUTE = 10;

// Funkcja wyboru rasy postaci
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

// Funkcja wyboru klasy postaci
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

// Funkcja do wyboru atrybutów
Attributes selectAttributes() {
    Attributes attrs = {5, 5, 5, 5, 5}; // Domyślne wartości
    int pointsRemaining = POINTS_TO_DISTRIBUTE; // Punkty do rozdysponowania
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

        // Wyświetl zaktualizowane atrybuty
        std::cout << "Updated attributes:\n";
        std::cout << "1. Strength: " << attrs.strength << "\n";
        std::cout << "2. Dexterity: " << attrs.dexterity << "\n";
        std::cout << "3. Intelligence: " << attrs.intelligence << "\n";
        std::cout << "4. Wisdom: " << attrs.wisdom << "\n";
        std::cout << "5. Charisma: " << attrs.charisma << "\n";
    }

    return attrs;
}

// Getter do nazwy postaci
std::string getCharacterName() {
    std::string name;
    std::cout << "Enter character name: ";
    std::getline(std::cin, name);
    return name;
}

// Funkcja dodawania przedmiotu do ekwipunku postaci
void addItemToInventory(character& character, const Item& item) {
    // Tworzenie nowej tablicy o jeden większej
    Item* newInventory = new Item[character.inventorySize + 1];

    // Kopiowanie istniejących przedmiotów
    for (int i = 0; i < character.inventorySize; i++) {
        newInventory[i] = character.inventory[i];
    }

    // Dodawanie nowego przedmiotu
    newInventory[character.inventorySize] = item;

    // Usuwanie starej tablicy
    if (character.inventorySize > 0) {
        delete[] character.inventory;
    }

    // Aktualizowanie wskaźnika i rozmiaru
    character.inventory = newInventory;
    character.inventorySize++;

    // Aktualizacja wagi
    character.currentWeight += item.weight;
}

// Funkcja zwalniająca pamięć używaną przez ekwipunek postaci
void freeCharacterMemory(character& character) {
    if (character.inventorySize > 0) {
        delete[] character.inventory;
        character.inventory = nullptr;
        character.inventorySize = 0;
    }
}

// Funkcja zwalniająca pamięć używaną przez tablicę postaci
void freeCharactersArray(character* characters, int characterCount) {
    if (characters != nullptr) {
        for (int i = 0; i < characterCount; i++) {
            freeCharacterMemory(characters[i]);
        }
        delete[] characters;
    }
}

// Funkcja wyświetlająca ekwipunek postaci
void displayInventory(const character &character) {
    std::cout << "\n===== Equipment =====\n";

    if (character.inventorySize == 0) {
        std::cout << "No items in inventory.\n";
    } else {
        std::cout << "Items:\n";
        for (int i = 0; i < character.inventorySize; i++) {
            std::cout << "- " << character.inventory[i].name << " (" << character.inventory[i].weight << " kg)\n";
        }
        std::cout << "Total weight: " << character.currentWeight << "/"
                << character.maxCarryWeight << " kg\n";
    }
}

// Funkcja wyświetlająca statystyki postaci
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

// Funkcja wczytująca postacie z pliku
character* loadCharacters(const std::string &filename, int& characterCount) {
    characterCount = 0;
    character* characters = nullptr;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open characters.txt" << std::endl;
        return nullptr;
    }

    // Najpierw zliczamy liczbę postaci w pliku
    std::string line;
    int characterCounter = 0;
    while (std::getline(file, line)) {
        if (line == "CHARACTER") {
            characterCounter++;
        }
    }

    // Resetujemy pozycję w pliku
    file.clear();
    file.seekg(0);

    // Alokujemy tablicę postaci
    characters = new character[characterCounter];

    bool inCharacter = false;
    character currentChar;
    int currentCharIndex = -1;

    // Inicjalizacja zmiennych
    std::string name;
    Race race = Race::HUMAN;
    CharacterClass charClass = CharacterClass::WARRIOR;
    int strength = 5, dexterity = 5, intelligence = 5, wisdom = 5, charisma = 5;
    float maxCarryWeight = 0.0f, currentWeight = 0.0f;

    // Tymczasowa tablica przedmiotów
    Item* tempInventory = nullptr;
    int inventorySize = 0;

    while (std::getline(file, line)) {
        // Usunięcie whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        if (!line.empty()) {
            line.erase(line.find_last_not_of(" \t") + 1);
        }

        if (line.empty()) continue;

        if (line == "CHARACTER") {
            inCharacter = true;
            currentCharIndex++;

            // Resetowanie wartości
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

            // Resetowanie ekwipunku
            if (tempInventory != nullptr) {
                delete[] tempInventory;
                tempInventory = nullptr;
            }
            inventorySize = 0;

        } else if (line == "END_CHARACTER") {
            if (!name.empty() && currentCharIndex >= 0) {
                Attributes attrs = {
                    strength, dexterity,
                    intelligence, wisdom, charisma
                };

                // Zapisz dane do bieżącej postaci
                characters[currentCharIndex].name = name;
                characters[currentCharIndex].race = race;
                characters[currentCharIndex].characterClass = charClass;
                characters[currentCharIndex].baseAttributes = attrs;
                characters[currentCharIndex].attributes = attrs;
                characters[currentCharIndex].maxCarryWeight = maxCarryWeight;
                characters[currentCharIndex].currentWeight = currentWeight;

                // Alokacja i kopiowanie ekwipunku
                characters[currentCharIndex].inventorySize = inventorySize;
                if (inventorySize > 0) {
                    characters[currentCharIndex].inventory = new Item[inventorySize];
                    for (int i = 0; i < inventorySize; i++) {
                        characters[currentCharIndex].inventory[i] = tempInventory[i];
                    }
                } else {
                    characters[currentCharIndex].inventory = nullptr;
                }

                // Przelicz statystyki
                recalculateStats(characters[currentCharIndex]);

                characterCount++;
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
                    // Parsowanie przedmiotów
                    std::istringstream itemStream(value);
                    std::string itemName;
                    std::vector<std::string> itemNames;

                    // Zbierz nazwy przedmiotów
                    while (std::getline(itemStream, itemName, ',')) {
                        itemName.erase(0, itemName.find_first_not_of(" \t"));
                        itemName.erase(itemName.find_last_not_of(" \t") + 1);
                        if (!itemName.empty()) {
                            itemNames.push_back(itemName);
                        }
                    }

                    // Pobierz dostępne przedmioty
                    int itemCount = 0;
                    Item* availableItems = initializeItems(itemCount);

                    // Utwórz tymczasową tablicę na przedmioty
                    if (tempInventory != nullptr) {
                        delete[] tempInventory;
                    }
                    inventorySize = itemNames.size();
                    tempInventory = new Item[inventorySize];

                    // Dodaj znalezione przedmioty do tymczasowej tablicy
                    int foundItems = 0;
                    for (const auto& name : itemNames) {
                        for (int i = 0; i < itemCount; i++) {
                            if (availableItems[i].name == name && foundItems < inventorySize) {
                                tempInventory[foundItems++] = availableItems[i];
                                break;
                            }
                        }
                    }

                    // Zwolnij pamięć zaalokowaną przez availableItems
                    delete[] availableItems;
                }
            }
        }
    }

    // Zwolnij pamięć tymczasową
    if (tempInventory != nullptr) {
        delete[] tempInventory;
    }

    file.close();
    return characters;
}

// Funkcja do zapisywania postaci do pliku
void saveCharacter(const character &character, const std::string &filename) {
    // Otwórz plik do zapisu
    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing" << std::endl;
        return;
    }

    // Rozpoczęcie bloku postaci
    file << "CHARACTER\n";
    // Zapisanie nazwy postaci
    file << "name: " << character.name << "\n";

    // Zapisanie rasy
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

    // Zapisanie klasy
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

    // Zapisanie atrybutów - tylko bazowe atrybuty
    file << "strength: " << character.baseAttributes.strength << "\n";
    file << "dexterity: " << character.baseAttributes.dexterity << "\n";
    file << "intelligence: " << character.baseAttributes.intelligence << "\n";
    file << "wisdom: " << character.baseAttributes.wisdom << "\n";
    file << "charisma: " << character.baseAttributes.charisma << "\n";

    // Zapisanie wagi
    file << "maxCarryWeight: " << character.maxCarryWeight << "\n";
    file << "currentWeight: " << character.currentWeight << "\n";

    // Zapisanie ekwipunku
    file << "inventory: ";
    bool first = true;
    for (int i = 0; i < character.inventorySize; i++) {
        if (!first) {
            file << ",";
        }
        file << character.inventory[i].name;
        first = false;
    }
    file << "\n";

    // Zamknięcie bloku postaci
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

// Funkcja do usuwania przedmiotu z ekwipunku
void removeItemFromInventory(character& character, int itemIndex) {
    if (itemIndex < 0 || itemIndex >= character.inventorySize) {
        std::cout << "Invalid item index.\n";
        return;
    }

    // Pobierz przedmiot do usunięcia, aby można było zaktualizować wagę
    Item itemToRemove = character.inventory[itemIndex];

    // Utwórz nową tablicę o jedną pozycję mniejszą
    Item* newInventory = nullptr;
    if (character.inventorySize > 1) {
        newInventory = new Item[character.inventorySize - 1];

        // Kopiuj przedmioty przed usuwanym indeksem
        for (int i = 0; i < itemIndex; i++) {
            newInventory[i] = character.inventory[i];
        }

        // Kopiuj przedmioty po usuwanym indeksie
        for (int i = itemIndex + 1; i < character.inventorySize; i++) {
            newInventory[i - 1] = character.inventory[i];
        }
    }

    // Usuń bonusy przedmiotu z atrybutów postaci
    applyItemBonuses(character, itemToRemove, false);

    // Zmniejsz obecną wagę
    character.currentWeight -= itemToRemove.weight;

    // Zwolnij starą tablicę
    delete[] character.inventory;

    // Zaktualizuj wskaźnik i rozmiar tablicy
    character.inventory = newInventory;
    character.inventorySize--;

    std::cout << "Item " << itemToRemove.name << " removed from inventory.\n";
}

// Funkcja do zarządzania ekwipunkiem postaci
void manageInventory(character& characterProp) {
    bool managing = true;

    while (managing) {
        std::cout << "\n===== Inventory Management =====\n";
        displayInventory(characterProp);

        std::cout << "\nOptions:\n";
        std::cout << "1. Add items\n";
        std::cout << "2. Remove item\n";
        std::cout << "3. Return to character view\n";

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                // Pobierz dostępne przedmioty
                int itemCount = 0;
                Item* availableItems = initializeItems(itemCount);

                // Filtruj przedmioty kompatybilne z klasą postaci
                int compatibleItemsCount = 0;
                Item* compatibleItems = nullptr;

                // Najpierw zliczamy zgodne przedmioty
                for (int i = 0; i < itemCount; i++) {
                    if (isItemCompatible(availableItems[i], characterProp.characterClass)) {
                        compatibleItemsCount++;
                    }
                }

                if (compatibleItemsCount == 0) {
                    std::cout << "No compatible items found for your class.\n";
                    delete[] availableItems;
                    break;
                }

                // Alokuj pamięć dla zgodnych przedmiotów
                compatibleItems = new Item[compatibleItemsCount];

                // Wypełnij tablicę zgodnych przedmiotów
                int currentIndex = 0;
                for (int i = 0; i < itemCount; i++) {
                    if (isItemCompatible(availableItems[i], characterProp.characterClass)) {
                        compatibleItems[currentIndex] = availableItems[i];
                        currentIndex++;
                    }
                }

                // Wyświetl dostępne przedmioty
                std::cout << "\nAvailable items for your class:\n";
                for (int i = 0; i < compatibleItemsCount; i++) {
                    const Item& item = compatibleItems[i];
                    std::cout << i + 1 << ". " << item.name
                              << " (Weight: " << item.weight << " kg) - " << item.description << "\n";

                    // Wyświetl bonusy statystyk, jeśli istnieją
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

                std::cout << "0. Cancel\n";
                std::cout << "Current weight: " << characterProp.currentWeight << "/"
                          << characterProp.maxCarryWeight << " kg\n";

                int itemChoice;
                std::cout << "Select an item to add (0-" << compatibleItemsCount << "): ";
                std::cin >> itemChoice;

                if (std::cin.fail() || itemChoice < 0 || itemChoice > compatibleItemsCount) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid choice. Please try again.\n";
                } else if (itemChoice != 0) {
                    // Sprawdź czy dodanie tego przedmiotu nie przekroczy limitu wagi
                    if (characterProp.currentWeight + compatibleItems[itemChoice - 1].weight > characterProp.maxCarryWeight) {
                        std::cout << "Cannot add this item. It would exceed your maximum carry weight.\n";
                    } else {
                        // Dodaj przedmiot do ekwipunku
                        addItemToInventory(characterProp, compatibleItems[itemChoice - 1]);
                        applyItemBonuses(characterProp, compatibleItems[itemChoice - 1], true);
                        std::cout << "Added " << compatibleItems[itemChoice - 1].name << " to your inventory.\n";

                        // Zapisz postać po zmianach
                        // Tworzymy tymczasowy plik do zapisu
                        character* allCharacters;
                        int charCount;
                        allCharacters = loadCharacters("data/characters.txt", charCount);

                        // Usuwamy plik i tworzymy nowy
                        std::remove("data/characters.txt");

                        // Zapisujemy wszystkie postacie z powrotem, z zaktualizowanymi danymi
                        for (int i = 0; i < charCount; i++) {
                            if (allCharacters[i].name == characterProp.name) {
                                // Zapisz zaktualizowaną postać
                                saveCharacter(characterProp);
                            } else {
                                // Zapisz oryginalną postać
                                saveCharacter(allCharacters[i]);
                            }
                        }

                        // Zwolnij pamięć
                        freeCharactersArray(allCharacters, charCount);
                    }
                }

                // Zwolnij pamięć
                delete[] availableItems;
                delete[] compatibleItems;
                break;
            }
            case 2: {
                if (characterProp.inventorySize == 0) {
                    std::cout << "No items in inventory to remove.\n";
                    break;
                }

                // Wyświetl przedmioty z indeksami
                std::cout << "\nSelect item to remove:\n";
                for (int i = 0; i < characterProp.inventorySize; i++) {
                    std::cout << i + 1 << ". " << characterProp.inventory[i].name
                              << " (" << characterProp.inventory[i].weight << " kg)\n";
                }
                std::cout << "0. Cancel\n";

                int itemIndex;
                std::cout << "Enter item number to remove (0 to cancel): ";
                std::cin >> itemIndex;

                if (std::cin.fail() || itemIndex < 0 || itemIndex > characterProp.inventorySize) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid choice. Please try again.\n";
                } else if (itemIndex != 0) {
                    // Usuń przedmiot
                    removeItemFromInventory(characterProp, itemIndex - 1);

                    // Zapisz postać po zmianach
                    // Tworzymy tymczasowy plik do zapisu
                    character* allCharacters;
                    int charCount;
                    allCharacters = loadCharacters("data/characters.txt", charCount);

                    // Usuwamy plik i tworzymy nowy
                    std::remove("data/characters.txt");

                    // Zapisujemy wszystkie postacie z powrotem, z zaktualizowanymi danymi
                    for (int i = 0; i < charCount; i++) {
                        if (allCharacters[i].name == characterProp.name) {
                            // Zapisz zaktualizowaną postać
                            saveCharacter(characterProp);
                        } else {
                            // Zapisz oryginalną postać
                            saveCharacter(allCharacters[i]);
                        }
                    }

                    // Zwolnij pamięć
                    freeCharactersArray(allCharacters, charCount);
                }
                break;
            }
            case 3:
                managing = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void selectCharacter(const character* characters, int characterCount) {
    std::cout << "Select a character:\n";
    for (int i = 0; i < characterCount; ++i) {
        std::cout << i + 1 << ". " << characters[i].name << "\n";
    }
    std::cout << "0. Return to main menu\n";

    int choice;
    std::cin >> choice;

    if (choice == 0) {
        return;
    }

    if (choice < 1 || choice > characterCount) {
        std::cout << "Invalid choice. Please try again.\n";
        selectCharacter(characters, characterCount);
        return;
    }

    // Tworzymy kopię postaci, aby móc ją modyfikować
    character selectedChar = characters[choice - 1];

    bool viewingCharacter = true;
    while (viewingCharacter) {
        // Wyświetl szczegóły postaci
        displayCharacter(selectedChar);

        std::cout << "\nOptions:\n";
        std::cout << "1. Manage inventory\n";
        std::cout << "2. Return to character selection\n";

        int option;
        std::cout << "Enter your choice: ";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (option) {
            case 1:
                manageInventory(selectedChar);
                break;
            case 2:
                viewingCharacter = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    // Zwolnij pamięć zaalokowaną dla ekwipunku kopii postaci
    freeCharacterMemory(selectedChar);

    // Wróć do wyboru postaci
    selectCharacter(characters, characterCount);
}