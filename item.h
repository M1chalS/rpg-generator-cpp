/**
 * @file item.h
 * @brief Plik zawierający definicje i deklaracje związane z przedmiotami w grze RPG
 * 
 * Zawiera definicję klasy wyliczeniowej CharacterClass, struktury Item oraz 
 * funkcje do zarządzania przedmiotami w systemie gry.
 *
 * @author Michał Szajner
 * @date 2025-06-01
 */
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "types.h"

/**
 * @brief Klasa wyliczeniowa reprezentująca klasy postaci dostępne w grze
 */
enum class CharacterClass {
    WARRIOR,  /**< Wojownik - specjalizuje się w walce wręcz */
    MAGE,     /**< Mag - specjalizuje się w magii ofensywnej */
    ROGUE,    /**< Łotrzyk - specjalizuje się w skradaniu i atakach z zaskoczenia */
    CLERIC,   /**< Kleryk - specjalizuje się w leczeniu i magii wspomagającej */
    RANGER    /**< Łowca - specjalizuje się w walce dystansowej */
};

/**
 * @brief Struktura reprezentująca przedmiot w grze
 * 
 * Zawiera wszystkie informacje o przedmiocie, w tym nazwę, wagę, opis,
 * kompatybilne klasy postaci oraz bonusy do statystyk.
 */
struct Item {
    std::string name;                   /**< Nazwa przedmiotu */
    float weight;                       /**< Waga przedmiotu w jednostkach gry */
    CharacterClass* compatibleClasses;  /**< Tablica klas postaci, które mogą używać przedmiotu */
    int compatibleClassesCount;         /**< Liczba kompatybilnych klas w tablicy */
    std::string description;            /**< Opis przedmiotu */

    // Bonusy do statystyk postaci
    int strengthBonus;     /**< Bonus do siły postaci */
    int dexterityBonus;    /**< Bonus do zręczności postaci */
    int intelligenceBonus; /**< Bonus do inteligencji postaci */
    int wisdomBonus;       /**< Bonus do mądrości postaci */
    int charismaBonus;     /**< Bonus do charyzmy postaci */

    /**
     * @brief Domyślny konstruktor
     * 
     * Tworzy pusty przedmiot z zerowymi wartościami.
     */
    Item();
    
    /**
     * @brief Destruktor
     * 
     * Zwalnia pamięć zaalokowaną dla tablicy compatibleClasses.
     */
    ~Item();
    
    /**
     * @brief Konstruktor kopiujący
     * 
     * @param other Referencja do kopiowanego przedmiotu
     */
    Item(const Item& other);
    
    /**
     * @brief Operator przypisania
     * 
     * @param other Referencja do kopiowanego przedmiotu
     * @return Referencja do aktualnego przedmiotu po przypisaniu
     */
    Item& operator=(const Item& other);
};

/**
 * @brief Inicjalizuje domyślny zestaw przedmiotów
 * 
 * @param itemCount Referencja do zmiennej, która będzie zawierać liczbę zainicjalizowanych przedmiotów
 * @return Wskaźnik do tablicy zainicjalizowanych przedmiotów
 */
Item* initializeItems(int& itemCount);

/**
 * @brief Sprawdza, czy przedmiot jest kompatybilny z klasą postaci
 * 
 * @param item Referencja do przedmiotu, który ma zostać sprawdzony
 * @param playerClass Klasa postaci do sprawdzenia kompatybilności
 * @return true jeśli przedmiot jest kompatybilny, false w przeciwnym wypadku
 */
bool isItemCompatible(const Item& item, CharacterClass playerClass);

/**
 * @brief Umożliwia wybór ekwipunku dla postaci
 * 
 * @param character Referencja do struktury postaci, dla której wybierany jest ekwipunek
 */
void selectEquipment(character& character);

/**
 * @brief Stosuje lub usuwa bonusy z przedmiotu do statystyk postaci
 * 
 * @param character Referencja do struktury postaci
 * @param item Referencja do przedmiotu, którego bonusy mają zostać zastosowane
 * @param adding true jeśli bonusy mają zostać dodane, false jeśli mają zostać usunięte
 */
void applyItemBonuses(character& character, const Item& item, bool adding);

/**
 * @brief Przelicza wszystkie statystyki postaci z uwzględnieniem bonusów z przedmiotów
 * 
 * @param character Referencja do struktury postaci, dla której mają zostać przeliczone statystyki
 */
void recalculateStats(character& character);

#endif
