#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

int ability_mod(int score){
    return (int)floor((score-10)/2.0);
}

struct Character *create_character(
    const char *name, const char *class, const char *alignment,
    int hp, int strength, int dexterity, int constitution,
    int intelligence, int wisdom, int charisma, int ac, int damagedie, int damagebonus){
        // Step 1. Allocate enough memory for one character
        struct Character *new_character = malloc(sizeof(struct Character));
        if(!new_character) {
            fprintf(stderr, "Error: Failed to allocate memory for character. \n");
            exit(1); // This indicates a hard crash, and is a good way to handle errors.
        }

        // Step 2. Copy the strings into the allocated memory
        strncpy(new_character->name, name, sizeof(new_character->name)-1);
        new_character->name[sizeof(new_character->name)-1] = '\0'; // This ensures the string is null-terminated.
        
        strncpy(new_character->alignment, alignment, sizeof(new_character->alignment)-1);
        new_character->alignment[sizeof(new_character->alignment)-1] = '\0'; // Even if the input string was too long,
        // this gurantees that the struct string won't overflow or stay unterminated.

        strncpy(new_character->class, class, sizeof(new_character->class)-1);
        new_character->class[sizeof(new_character->class)-1] = '\0';

        // Step 3. Now, we copy the numeric values into the struct (thankfully simpler!)
        new_character->hp = hp;
        new_character->strength = strength;
        new_character->dexterity = dexterity;
        new_character->constitution = constitution;
        new_character->intelligence = intelligence;
        new_character->wisdom = wisdom;
        new_character->charisma = charisma;
        new_character->ac = ac;
        new_character->damagedie = damagedie;
        new_character->damagebonus = damagebonus;

        // Step 4. Return the pointer to the new_character
        return new_character;
}


void print_character(struct Character *c){
    printf("%s - %s %s (HP: %d, AC: %d)\n", c-> name, c->alignment, c->class, c->hp, c->ac);
    printf("STR: %d (Mod: %d), DEX: %d (Mod: %d), CON: %d (Mod: %d)\n", c->strength, ability_mod(c->strength), c->dexterity, ability_mod(c->dexterity), c->constitution, ability_mod(c->constitution));
    printf("INT: %d (Mod: %d), WIS: %d (Mod: %d), CHA: %d (Mod: %d)\n", c->intelligence, ability_mod(c->intelligence), c->wisdom, ability_mod(c->wisdom), c->charisma, ability_mod(c->charisma));
    printf("--------------------------------\n\n");
}
void print_party(struct Character party[], int count) {
    printf("=== PARTY SUMMARY - Our intrepid adventurers === \n\n");
    for (int i=0; i<count; i++) {
        printf ("%d. ", i+1);
        print_character(&party[i]);
    }
    printf("--------------------------------\n\n");
}

void free_character(struct Character *c) {
    if (c) {   // defensive check in case we pass NULL
        free(c);
    }
}

// Calculates the damage die and bonus for the character's attacks based on their class
// NOTE: This is a new function that mostly accounts for the classic D&D class set and does not account for all classes or subclasses.
// Feel free to expand this function to account for more classes and subclasses as needed.


void save_party(struct Character party[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Failed to open file for writing: %s\n", filename);
        return;
    }

    for (int i=0; i<count; i++) {
        fprintf(file, "%s, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d\n",
        party[i].name, 
        party[i].alignment, 
        party[i].class, 
        party[i].hp, 
        party[i].strength, 
        party[i].dexterity, 
        party[i].constitution, 
        party[i].intelligence, 
        party[i].wisdom, 
        party[i].charisma, 
        party[i].ac);
    }

    fclose(file);
    printf("Party has been saved to %s\n", filename);

}

int load_party(struct Character party[], int max_count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file) {
        fprintf(stderr, "Error: Failed to open file for reading: %s\n", filename);
        return 0;
    }

    int i = 0;
    while (i<max_count && fscanf(file, "%19s %19s %19s %d %d %d %d %d %d %d %d",
    party[i].name,
    party[i].alignment, 
    party[i].class, 
    &party[i].hp, 
    &party[i].strength, 
    &party[i].dexterity, 
    &party[i].constitution, 
    &party[i].intelligence, 
    &party[i].wisdom, 
    &party[i].charisma, 
    &party[i].ac) == 11) {
        i++;
    }

    fclose(file);
    printf("Party has been loaded from %s\n", filename);
    return i;
}