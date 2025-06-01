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

#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "item.h"

/**
 * @brief Typ wyliczeniowy reprezentujący rasy postaci dostępne w grze
 */
enum class Race {
    HUMAN,    /**< Człowiek */
    ELF,      /**< Elf */
    DWARF,    /**< Krasnolud */
    ORC,      /**< Ork */
    GNOME     /**< Gnom */
};

/**
 * @brief Struktura przechowująca atrybuty postaci
 * 
 * Zawiera podstawowe cechy postaci, które wpływają na jej umiejętności i możliwości.
 */
struct Attributes {
    int strength;      /**< Siła - wpływa na udźwig i obrażenia w walce wręcz */
    int dexterity;     /**< Zręczność - wpływa na szybkość i precyzję */
    int intelligence;  /**< Inteligencja - wpływa na zdolności magiczne */
    int wisdom;        /**< Mądrość - wpływa na percepcję i odporność mentalną */
    int charisma;      /**< Charyzma - wpływa na interakcje społeczne */
};

/**
 * @brief Struktura reprezentująca postać gracza
 * 
 * Zawiera wszystkie informacje o postaci, w tym jej atrybuty,
 * wyposażenie oraz podstawowe cechy jak rasa i klasa.
 */
struct character {
    std::string name;             /**< Imię postaci */
    Race race;                    /**< Rasa postaci */
    CharacterClass characterClass; /**< Klasa postaci */
    Attributes baseAttributes;    /**< Bazowe statystyki bez bonusów */
    Attributes attributes;        /**< Statystyki z uwzględnieniem bonusów z przedmiotów */
    Item* inventory;              /**< Dynamiczna tablica przedmiotów */
    int inventorySize;            /**< Rozmiar tablicy inventory */
    float maxCarryWeight;         /**< Maksymalna waga, jaką postać może nosić */
    float currentWeight;          /**< Aktualna waga przedmiotów w inwentarzu */
};

/**
 * @brief Funkcja pozwalająca użytkownikowi na wybór rasy postaci
 * @return Wybrana przez użytkownika rasa postaci
 */
Race selectRace();

/**
 * @brief Funkcja pozwalająca użytkownikowi na wybór klasy postaci
 * @return Wybrana przez użytkownika klasa postaci
 */
CharacterClass selectClass();

/**
 * @brief Funkcja pozwalająca użytkownikowi na przydzielenie punktów atrybutów
 * @return Struktura z wybranymi wartościami atrybutów
 */
Attributes selectAttributes();

/**
 * @brief Pobiera od użytkownika imię dla postaci
 * @return Ciąg znaków zawierający imię postaci
 */
std::string getCharacterName();

/**
 * @brief Wyświetla informacje o postaci
 * @param character Referencja do struktury postaci, której informacje mają zostać wyświetlone
 */
void displayCharacter(const character& character);

/**
 * @brief Wyświetla zawartość inwentarza postaci
 * @param character Referencja do struktury postaci, której inwentarz ma zostać wyświetlony
 */
void displayInventory(const character& character);

/**
 * @brief Zapisuje informacje o postaci do pliku
 * @param character Referencja do struktury postaci, która ma zostać zapisana
 * @param filename Ścieżka do pliku, w którym mają zostać zapisane dane (domyślnie "data/characters.txt")
 */
void saveCharacter(const character& character, const std::string& filename = "data/characters.txt");

/**
 * @brief Wczytuje postacie z pliku
 * @param filename Ścieżka do pliku, z którego mają zostać wczytane dane
 * @param characterCount Referencja do zmiennej, która będzie przechowywać liczbę wczytanych postaci
 * @return Wskaźnik do tablicy wczytanych postaci
 */
character* loadCharacters(const std::string& filename, int& characterCount);

/**
 * @brief Tworzy nową postać na podstawie danych wprowadzonych przez użytkownika
 */
void createCharacter();

/**
 * @brief Pozwala użytkownikowi wybrać postać z dostępnej listy
 * @param characters Wskaźnik do tablicy postaci
 * @param characterCount Liczba postaci w tablicy
 */
void selectCharacter(const character* characters, int characterCount);

/**
 * @brief Dodaje przedmiot do inwentarza postaci
 * @param character Referencja do struktury postaci
 * @param item Przedmiot, który ma zostać dodany do inwentarza
 */
void addItemToInventory(character& character, const Item& item);

/**
 * @brief Usuwa przedmiot z inwentarza postaci
 * @param character Referencja do struktury postaci
 * @param itemIndex Indeks przedmiotu, który ma zostać usunięty
 */
void removeItemFromInventory(character& character, int itemIndex);

/**
 * @brief Pozwala na zarządzanie inwentarzem postaci (dodawanie/usuwanie przedmiotów)
 * @param character Referencja do struktury postaci
 */
void manageInventory(character& character);

/**
 * @brief Zwalnia pamięć zaalokowaną dla inwentarza postaci
 * @param character Referencja do struktury postaci
 */
void freeCharacterMemory(character& character);

/**
 * @brief Zwalnia pamięć zaalokowaną dla tablicy postaci
 * @param characters Wskaźnik do tablicy postaci
 * @param characterCount Liczba postaci w tablicy
 */
void freeCharactersArray(character* characters, int characterCount);

#endif
