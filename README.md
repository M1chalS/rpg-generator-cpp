# System tworzenia postaci RPG

## Opis
Aplikacja umożliwia tworzenie i zarządzanie postaciami w grze RPG. Użytkownik może stworzyć nową postać, wybierając jej rasę, klasę, atrybuty i wyposażenie. Dane są zapisywane w plikach tekstowych, co umożliwia ich łatwe wczytywanie i modyfikację.

## Funkcje
- Tworzenie nowych postaci
- Wybór rasy (Człowiek, Elf, Krasnolud, Ork, Gnom)
- Wybór klasy (Wojownik, Mag, Łotrzy, Kleryk, Łowca)
- Przydzielanie punktów atrybutów (siła, zręczność, wytrzymałość, inteligencja, mądrość, charyzma)
- Wybór wyposażenia dla postaci
- Zarządzanie ekwipunkiem z ograniczeniem wagi
- Zapisywanie i wczytywanie postaci z pliku

## Format plików
### Format pliku items.txt
```
ITEM
name: [nazwa przedmiotu]
weight: [waga]
classes: [klasy oddzielone przecinkami]
description: [opis przedmiotu]
END_ITEM
```

### Format pliku characters.txt
```
CHARACTER
name: [imię postaci]
race: [rasa]
class: [klasa]
strength: [siła]
dexterity: [zręczność]
intelligence: [inteligencja]
wisdom: [mądrość]
charisma: [charyzma]
maxCarryWeight: [maksymalna waga ekwipunku]
currentWeight: [aktualna waga ekwipunku]
inventory: [przedmioty oddzielone przecinkami]
END_CHARACTER
```

## Jak uruchomić
Skompiluj projekt używając wybranego kompilatora C++ i uruchom plik wykonywalny. Aplikacja działa w trybie konsolowym.

*By [Michał Szajner](https://github.com/M1chalS)*