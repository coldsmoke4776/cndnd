#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "character.h"
#include "bestiary.h"
#include "combat.h"
#include "dicegoblin.h"

int main(void) {
    init_rng(); // This initializes the RNG, seeded to ensure we get a different sequence each game.

    // This is the part array, which is an array of 4 characters, preprogrammed for now to
    // save on data entry during testing and development.
    struct Character party[4] = {
        {"Tav", "Fighter", "NE", 18, 14, 16, 12, 13, 10, 15, 40, 8, 4},
        {"Gale", "Wizard", "NG", 10, 12, 14, 18, 16, 18, 14, 30, 4, 0},
        {"Jaheira", "Ranger", "LG", 16, 16, 16, 14, 18, 14, 16, 40, 10, 3},
        {"Shadowheart", "Cleric", "CE", 16, 18, 14, 12, 18, 16, 16, 30, 8, 3}
    };

    // Save the party to a file called party.txt to allow for loading later
    save_party(party, 4, "party.txt");

    //For testing purposes, clear it from memory
    //struct Character new_party[4];
    //int loaded_count = load_party(new_party, 4, "party.txt");
    // print_party(new_party, loaded_count);

    sleep(2);
    print_party(party, 4);
    struct Monster enemy = bestiary[rand() % NUM_MONSTERS];
    sleep(2);
    combat(&party[0], 4, &enemy);

    return 0;
}