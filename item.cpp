/**
 * @file item.cpp
 * @brief Implementacja funkcji i metod związanych z przedmiotami w grze RPG
 * 
 * Plik zawiera implementację metod klasy Item oraz funkcje pomocnicze
 * do zarządzania przedmiotami, w tym inicjalizację, wybór ekwipunku i 
 * obliczanie wpływu przedmiotów na statystyki postaci.
 *
 * @author Michał Szajner
 * @date 2025-06-01
 */
#include "item.h"
#include "character.h"
#include <fstream>
#include <sstream>
#include <limits>

/**
 * @brief Podstawowa wartość udźwigu dla każdej postaci
 * 
 * Określa bazową ilość ciężaru, jaką każda postać może nieść
 * niezależnie od swoich atrybutów.
 */
const int BASE_CARRY_WEIGHT = 5.0f;

/**
 * @brief Konstruktor domyślny dla klasy Item
 * 
 * Tworzy nowy przedmiot z wartościami domyślnymi.
 */
Item::Item() : name(""), weight(1.0f), compatibleClasses(nullptr), compatibleClassesCount(0),
               description(""), strengthBonus(0), dexterityBonus(0), intelligenceBonus(0),
               wisdomBonus(0), charismaBonus(0) {}

/**
 * @brief Destruktor klasy Item
 * 
 * Zwalnia pamięć zaalokowaną dla tablicy kompatybilnych klas.
 */
Item::~Item() {
    delete[] compatibleClasses;
}

/**
 * @brief Konstruktor kopiujący dla klasy Item
 * 
 * @param other Referencja do kopiowanego przedmiotu
 */
Item::Item(const Item& other) : name(other.name), weight(other.weight),
                               compatibleClassesCount(other.compatibleClassesCount),
                               description(other.description), strengthBonus(other.strengthBonus),
                               dexterityBonus(other.dexterityBonus),
                               intelligenceBonus(other.intelligenceBonus),
                               wisdomBonus(other.wisdomBonus), charismaBonus(other.charismaBonus) {
    if (other.compatibleClassesCount > 0) {
        compatibleClasses = new CharacterClass[other.compatibleClassesCount];
        for (int i = 0; i < other.compatibleClassesCount; i++) {
            compatibleClasses[i] = other.compatibleClasses[i];
        }
    } else {
        compatibleClasses = nullptr;
    }
}

/**
 * @brief Operator przypisania dla klasy Item
 * 
 * @param other Referencja do przedmiotu, z którego kopiujemy dane
 * @return Referencja do aktualnego przedmiotu po przypisaniu
 */
Item& Item::operator=(const Item& other) {
    if (this != &other) {
        delete[] compatibleClasses;

        name = other.name;
        weight = other.weight;
        compatibleClassesCount = other.compatibleClassesCount;
        description = other.description;
        strengthBonus = other.strengthBonus;
        dexterityBonus = other.dexterityBonus;
        intelligenceBonus = other.intelligenceBonus;
        wisdomBonus = other.wisdomBonus;
        charismaBonus = other.charismaBonus;

        if (other.compatibleClassesCount > 0) {
            compatibleClasses = new CharacterClass[other.compatibleClassesCount];
            for (int i = 0; i < other.compatibleClassesCount; i++) {
                compatibleClasses[i] = other.compatibleClasses[i];
            }
        } else {
            compatibleClasses = nullptr;
        }
    }
    return *this;
}

/**
 * @brief Sprawdza, czy przedmiot jest kompatybilny z daną klasą postaci
 * 
 * @param item Referencja do przedmiotu, który jest sprawdzany
 * @param playerClass Klasa postaci do sprawdzenia kompatybilności
 * @return true jeśli przedmiot jest kompatybilny z klasą, false w przeciwnym przypadku
 */
bool isItemCompatible(const Item& item, CharacterClass playerClass) {
    for (int i = 0; i < item.compatibleClassesCount; i++) {
        if (item.compatibleClasses[i] == playerClass) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Inicjalizuje tablicę przedmiotów z pliku
 * 
 * Funkcja wczytuje dane przedmiotów z pliku "data/items.txt" i tworzy
 * na ich podstawie tablicę obiektów Item.
 * 
 * @param itemCount Referencja do zmiennej, która będzie przechowywać liczbę wczytanych przedmiotów
 * @return Wskaźnik do tablicy wczytanych przedmiotów lub nullptr w przypadku błędu
 */
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
    CharacterClass* compatibleClasses = nullptr;
    int compatibleClassesCount = 0;
    bool inItem = false;
    int currentItemIndex = 0;

    // Domyślne wartości bonusów
    int strengthBonus = 0;
    int dexterityBonus = 0;
    int intelligenceBonus = 0;
    int wisdomBonus = 0;
    int charismaBonus = 0;

    while (std::getline(file, line)) {
        // Usunięcie whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        if (!line.empty()) {
            line.erase(line.find_last_not_of(" \t") + 1);
        }

        if (line.empty()) continue;

        if (line == "ITEM") {
            // Początek nowego przedmiotu
            inItem = true;
            name = "";
            description = "";
            weight = 1.0f;
            delete[] compatibleClasses;
            compatibleClasses = nullptr;
            compatibleClassesCount = 0;

            // Reset bonusów
            strengthBonus = 0;
            dexterityBonus = 0;
            intelligenceBonus = 0;
            wisdomBonus = 0;
            charismaBonus = 0;
        } else if (line == "END_ITEM") {
            // Zmodyfikuj fragment, gdzie tworzone są nowe przedmioty
            if (!name.empty()) {
                Item newItem;
                newItem.name = name;
                newItem.weight = weight;
                newItem.compatibleClasses = compatibleClasses;  // Teraz już zgodne typy
                newItem.compatibleClassesCount = compatibleClassesCount;
                newItem.description = description;
                newItem.strengthBonus = strengthBonus;
                newItem.dexterityBonus = dexterityBonus;
                newItem.intelligenceBonus = intelligenceBonus;
                newItem.wisdomBonus = wisdomBonus;
                newItem.charismaBonus = charismaBonus;

                availableItems[currentItemIndex] = newItem;
                currentItemIndex++;

                // Ustawienie na nullptr, żeby nie zwolnić tej pamięci w destruktorze
                compatibleClasses = nullptr;
                compatibleClassesCount = 0;
            }
            inItem = false;
        } else if (inItem) {
            // Przetwarzanie właściwości przedmiotu
            size_t colonPos = line.find(":");
            if (colonPos != std::string::npos) {
                std::string key = line.substr(0, colonPos);
                std::string value = line.substr(colonPos + 1);

                // Usunięcie whitespace
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
                    std::istringstream classStream(value);
                    std::string classStr;

                    // Najpierw zliczamy liczbę klas
                    int classCount = 0;
                    std::string tempStr = value;
                    std::istringstream countStream(tempStr);
                    std::string tempClass;
                    while (std::getline(countStream, tempClass, ',')) {
                        classCount++;
                    }

                    // Alokujemy tablicę o odpowiednim rozmiarze
                    CharacterClass* tempClasses = new CharacterClass[classCount];
                    int currentClass = 0;

                    // Wypełniamy tablicę
                    while (std::getline(classStream, classStr, ',')) {
                        // Usunięcie whitespace
                        classStr.erase(0, classStr.find_first_not_of(" \t"));
                        classStr.erase(classStr.find_last_not_of(" \t") + 1);

                        if (classStr == "WARRIOR") tempClasses[currentClass++] = CharacterClass::WARRIOR;
                        else if (classStr == "MAGE") tempClasses[currentClass++] = CharacterClass::MAGE;
                        else if (classStr == "ROGUE") tempClasses[currentClass++] = CharacterClass::ROGUE;
                        else if (classStr == "CLERIC") tempClasses[currentClass++] = CharacterClass::CLERIC;
                        else if (classStr == "RANGER") tempClasses[currentClass++] = CharacterClass::RANGER;
                    }

                    // Przypisujemy tablicę do obiektu
                    compatibleClasses = tempClasses;
                    compatibleClassesCount = currentClass;
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

/**
 * @brief Stosuje lub usuwa bonusy z przedmiotu do statystyk postaci
 * 
 * @param character Referencja do struktury postaci
 * @param item Referencja do przedmiotu, którego bonusy mają zostać zastosowane/usunięte
 * @param adding true jeśli bonusy mają zostać dodane, false jeśli usunięte
 */
void applyItemBonuses(character& character, const Item& item, bool adding) {
    int multiplier = adding ? 1 : -1;

    character.attributes.strength += item.strengthBonus * multiplier;
    character.attributes.dexterity += item.dexterityBonus * multiplier;
    character.attributes.intelligence += item.intelligenceBonus * multiplier;
    character.attributes.wisdom += item.wisdomBonus * multiplier;
    character.attributes.charisma += item.charismaBonus * multiplier;
}

/**
 * @brief Przelicza wszystkie statystyki postaci na podstawie atrybutów bazowych i bonusów z przedmiotów
 * 
 * @param character Referencja do struktury postaci, której statystyki mają zostać przeliczone
 */
void recalculateStats(character& character) {
    // Resetowanie atrybutów
    character.attributes = character.baseAttributes;

    // Zastosowanie bonusów z przedmiotów
    for (int i = 0; i < character.inventorySize; i++) {
        applyItemBonuses(character, character.inventory[i], true);
    }
}

/**
 * @brief Funkcja umożliwiająca wybór ekwipunku dla postaci
 * 
 * Wyświetla listę dostępnych przedmiotów kompatybilnych z klasą postaci
 * i pozwala użytkownikowi dodać je do ekwipunku postaci w interaktywny sposób.
 * 
 * @param character Referencja do struktury postaci, dla której wybierany jest ekwipunek
 */
void selectEquipment(character& character) {
    int itemCount = 0;
    Item* availableItems = initializeItems(itemCount);

    // Tworzymy dynamiczną tablicę na zgodne przedmioty
    int compatibleItemsCount = 0;
    Item* compatibleItems = nullptr;

    // Ustawianie maksymalnej wagi
    character.maxCarryWeight = BASE_CARRY_WEIGHT + (character.attributes.strength * 2.0f);
    character.currentWeight = 0.0f;

    // Inicjalizacja ekwipunku
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

        // Wyświetlanie listy przedmiotów z ich statystykami
        for (int i = 0; i < compatibleItemsCount; i++) {
            const Item& item = compatibleItems[i];
            std::cout << i + 1 << ". " << item.name
                      << " (Weight: " << item.weight << " kg) - " << item.description << "\n";

            // Sprawdzenie, czy przedmiot ma bonusy
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

        // Wyświetlanie aktualnych statystyk z bonusami
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

        // Sprawdzenie, czy przedmiot może być dodany (nie przekracza maksymalnej wagi)
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
