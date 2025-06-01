/**
 * @file types.h
 * @brief Plik zawierający deklaracje wyprzedzające typów używanych w systemie RPG
 *
 * Ten plik zawiera deklaracje wyprzedzające dla klas wyliczeniowych oraz struktur,
 * które są używane w różnych częściach systemu generatora postaci RPG.
 * Umożliwia to unikanie cyklicznych zależności między plikami nagłówkowymi.
 *
 * @author Michał Szajner
 * @date 2025-06-01
 */
#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Klasa wyliczeniowa reprezentująca klasy postaci
 * 
 * Szczegółowa definicja znajduje się w odpowiednim pliku nagłówkowym.
 */
enum class CharacterClass;

/**
 * @brief Klasa wyliczeniowa reprezentująca rasy postaci
 * 
 * Szczegółowa definicja znajduje się w odpowiednim pliku nagłówkowym.
 */
enum class Race;

/**
 * @brief Struktura przechowująca atrybuty postaci
 * 
 * Szczegółowa definicja znajduje się w odpowiednim pliku nagłówkowym.
 */
struct Attributes;

/**
 * @brief Struktura reprezentująca postać gracza
 * 
 * Szczegółowa definicja znajduje się w odpowiednim pliku nagłówkowym.
 */
struct character;

/**
 * @brief Struktura reprezentująca przedmiot w grze
 * 
 * Szczegółowa definicja znajduje się w odpowiednim pliku nagłówkowym.
 */
struct Item;

#endif
