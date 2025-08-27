#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "character.h"

int main(void) {
    printf("=== HEAP ALLOCATION TEST ===\n\n");

    // Step 1: Create a character on the heap
    struct Character *hero = create_character(
        "Alice", "Wizard", "CG",   // name, class, alignment
        8, 14, 12, 18, 13, 10,     // STR, DEX, CON, INT, WIS, CHA
        25, 12                     // HP, AC
    );

    // Step 2: Print character info
    print_character(hero);

    // Step 3: Free the character when done
    free_character(hero);

    printf("\n=== MEMORY FREED, PROGRAM COMPLETE ===\n");

    return 0;
}
