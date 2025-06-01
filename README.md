# System tworzenia postaci RPG

## Opis
Aplikacja umożliwia tworzenie i zarządzanie postaciami w grze RPG. Użytkownik może stworzyć nową postać, wybierając jej rasę, klasę, atrybuty i wyposażenie. Dane są zapisywane w plikach tekstowych, co umożliwia ich łatwe wczytywanie i modyfikację.

Oto instrukcja obsługi aplikacji do tworzenia postaci RPG:

## Instrukcja obsługi

1. **Uruchomienie programu**
    - Skompiluj projekt za pomocą wybranego kompilatora C++.
    - Uruchom plik wykonywalny w terminalu/wierszu poleceń.

2. **Menu główne**
    - Po uruchomieniu zobaczysz menu:
        - Wciśnij `1`, aby utworzyć nową postać.
        - Wciśnij `2`, aby wczytać istniejące postacie.
        - Wciśnij `3`, aby zakończyć działanie programu.

3. **Tworzenie nowej postaci**
    - Podaj imię postaci.
    - Wybierz rasę (człowiek, elf, krasnolud, ork, gnom).
    - Wybierz klasę (wojownik, mag, łotrzyk, kleryk, łowca).
    - Rozdziel 10 punktów pomiędzy atrybuty: siła, zręczność, inteligencja, mądrość, charyzma.
    - Wybierz wyposażenie z dostępnych przedmiotów (zależnie od klasy i limitu wagi).
    - Po zakończeniu postać zostanie zapisana do pliku.

4. **Wczytywanie i edycja postaci**
    - Wybierz postać z listy.
    - Możesz przeglądać jej statystyki i ekwipunek.
    - W menu postaci wybierz:
        - `1` – zarządzanie ekwipunkiem (dodawanie/usuwanie przedmiotów, z zachowaniem limitu wagi).
        - `2` – powrót do wyboru postaci.

5. **Format plików**
    - Przedmioty i postacie są zapisywane w plikach tekstowych w folderze `data` (`items.txt`, `characters.txt`).
    - Możesz edytować te pliki ręcznie, zachowując odpowiedni format (opisany w pliku `README.md`).

6. **Zakończenie pracy**
    - W każdej chwili możesz zakończyć program wybierając opcję wyjścia z menu głównego.

**Uwaga:** Wszystkie operacje wykonuj zgodnie z komunikatami wyświetlanymi przez program w konsoli.

## Funkcje
- Tworzenie nowych postaci
- Wybór rasy (Człowiek, Elf, Krasnolud, Ork, Gnom)
- Wybór klasy (Wojownik, Mag, Łotrzy, Kleryk, Łowca)
- Przydzielanie punktów atrybutów (siła, zręczność, wytrzymałość, inteligencja, mądrość, charyzma)
- Wybór wyposażenia dla postaci
- Zarządzanie ekwipunkiem z ograniczeniem wagi
- Zapisywanie i wczytywanie postaci z pliku
- Edytowanie ekwipunku istniejących postaci

## Format plików
### Format pliku items.txt
```
ITEM
name: [nazwa przedmiotu]
weight: [waga]
classes: [klasy oddzielone przecinkami]
description: [opis przedmiotu]
strengthBonus: [bonus do siły]
dexterityBonus: [bonus do zręczności]
intelligenceBonus: [bonus do inteligencji]
wisdomBonus: [bonus do mądrości]
charismaBonus: [bonus do charyzmy]
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