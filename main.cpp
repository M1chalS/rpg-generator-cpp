#include <iostream>

#include "character.h"

int main() {
    std::cout << "RPG Character Generator\n";
    std::cout << "======================\n\n";

    character character;

    character.name = getCharacterName();

    character.race = selectRace();

    character.characterClass = selectClass();

    character.attributes = selectAttributes();

    selectEquipment(character);

    displayCharacter(character);

    return 0;
}
