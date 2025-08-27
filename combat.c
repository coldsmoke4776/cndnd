#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "character.h"
#include "combat.h"
#include "dicegoblin.h"

// Initiative tracker to keep track of turn order
struct Initiative {
    char name[20];
    int initiative;
    int is_hero; // 1 is hero, 0 is enemy
    struct Character *hero;
    struct Monster *enemy;
};

// Helper function to check if any character in the party is still alive
int party_alive(struct Character party[], int count) {
    for (int i = 0; i < count; i++) {
        if (party[i].hp > 0) return 1; // Checks if any character in the party is still alive
    } 
    return 0; // Party is all dead - TPK!
};

// Helper function to pick a random living hero for the enemy to attack
struct Character* random_living_hero(struct Character party[], int count) {
    struct Character *alive[count]; // Array to store pointers to living heroes
    int alive_count = 0;
    for (int i =0; i < count; i++) {
        if (party[i].hp > 0) {
            alive[alive_count++] = &party[i]; // Adds the living hero to the alive_count array
        }
    }
    if (alive_count == 0) return NULL; // No living heroes - return NULL
    int pick = rand() % alive_count; // Picks a random living hero
    return alive[pick]; // Returns the randomly selected living hero
};

void get_attack_stats(struct Character *c, int *damagedie, int *damagebonus){
    //Compares the string at "class" to "Fighter" to ascertain if character is a Fighter
    if (strcmp(c->class, "Fighter") == 0) { 
        *damagedie = 8; // Fighter's default damage die is a d8
        *damagebonus = ability_mod(c->strength); // Fighter's damage bonus is based off their STR modifier
    }
    else if (strcmp(c->class, "Rogue") == 0) {
        *damagedie = 6; // Rogue's default damage die is a d6
        *damagebonus = ability_mod(c->dexterity); // Rogue's damage bonus is based off their DEX modifier
    }
    else if (strcmp(c->class, "Wizard") == 0) {
        *damagedie = 4; // Wizard's default damage die is a d4
        *damagebonus = ability_mod(c->intelligence); // Wizard's damage bonus is based off their INT modifier
    }
    else if (strcmp(c->class, "Cleric") == 0) {
        *damagedie = 8; // Cleric's default damage die is a d8
        *damagebonus = ability_mod(c->wisdom); // Cleric's damage bonus is based off their WIS modifier
    }
    else if (strcmp(c->class, "Paladin") == 0) {
        *damagedie = 10; // Paladin's default damage die is a d10
        *damagebonus = ability_mod(c->strength); // Paladin's damage bonus is based off their STR modifier
    }
    else if (strcmp(c->class, "Barbarian") == 0) {
        *damagedie = 12; // Barbarian's default damage die is a d12
        *damagebonus = ability_mod(c->strength); // Barbarian's damage bonus is based off their STR modifier
    }
    else if (strcmp(c->class, "Monk") == 0) {
        *damagedie = 8; // Monk's default damage die is a d8
        *damagebonus = ability_mod(c->dexterity); // Monk's damage bonus is based off their DEX modifier
    }
    else if (strcmp(c->class, "Druid") == 0) {
        *damagedie = 8; // Druid's default damage die is a d8
    }
    else if (strcmp(c->class, "Bard") == 0) {
        *damagedie = 8; // Bard's default damage die is a d8
        *damagebonus = ability_mod(c->charisma); // Bard's damage bonus is based off their CHA modifier
    }
    else if (strcmp(c->class, "Ranger") == 0) {
        *damagedie = 10; // Ranger's default damage die is a d10
        *damagebonus = ability_mod(c->wisdom); // Ranger's damage bonus is based off their WIS modifier
    }
    else if (strcmp(c->class, "Sorcerer") == 0) {
        *damagedie = 6; // Sorcerer's default damage die is a d6
        *damagebonus = ability_mod(c->constitution); // Sorcerer's damage bonus is based off their CON modifier
    }
    else if (strcmp(c->class, "Warlock") == 0) {
        *damagedie = 8; // Warlock's default damage die is a d8
        *damagebonus = ability_mod(c->wisdom); // Warlock's damage bonus is based off their WIS modifier
    }
    else {
        *damagedie = 6; // Default to d6 for other classes
        *damagebonus = ability_mod(c->strength); // Default damage bonus is based off STR modifier
    }
}


void combat(struct Character party[], int count, struct Monster *enemy) {
    printf("=== An Encounter Begins! === \n");
    printf("\n");
    sleep(2);
    printf("An angry %s appears! (HP: %d, AC: %d, Att.Bon: %d, Dmg.Die: D%d, Dmg.Bon: %d)\n", enemy-> name, enemy->hp, enemy->armorclass, enemy->attackbonus, enemy->damagedie, enemy->damagebonus);
    printf("\n");
    sleep(2);
    printf("Swords in hand, spells at the ready, the party is ready to fight! \n");
    printf("\n\n");
    sleep(2);


    while (enemy->hp >0) {
        // Step 1: Choose a random living hero for the enemy to attack
        struct Character *hero = random_living_hero(party, count);
        if (!hero) {
            printf("All our intrepid heroes have fallen! The party has been defeated...\n\n");
            break;
        }

        // Step 2: Hero attacks the enemy
        printf("=== %s's Turn === \n", hero->name);
        int hero_attackroll = roll_dice(20) + ability_mod(hero->strength);

        if (hero_attackroll >= enemy->armorclass) {
            int damagedie, damagebonus;
            get_attack_stats(hero, &damagedie, &damagebonus);
            int damage = roll_dice(damagedie) + damagebonus; // Updated combat logic to use hero's specific damage die for D&D 5E accuracy
            enemy->hp -= damage;
            printf("%s hits the %s for %d damage! (Ememy HP is now: %d) \n\n", hero->name, enemy->name, damage, enemy->hp);
        } else {
            printf("%s misses the %s! \n\n", hero->name, enemy->name);
        }

        printf("--------------------------------\n");;
        sleep(2);


        // Step 3: Check if the enemy is defeated
        if (enemy->hp <=0) {
        printf("%s whispers: \"Omae wa mou shindeiru...\"\n", hero->name);
        printf("%s says back: NANI?!?\n", enemy->name);
        printf("%s has been defeated! \n\n", enemy->name);
        break;
        }

        // Step 4: Enemy attacks the hero
        //Enemy attacks
        printf("=== %s's turn === \n", enemy->name);
        int enemy_attackroll = roll_dice(20) + enemy->attackbonus; 
        //NOTE: We have now updated the engine to include hero AC, so we can remove the original 10+DEX modifier we had for testing
        if (enemy_attackroll >= hero->ac) {
            int damage = roll_dice(enemy->damagedie) + enemy->attackbonus;
            hero->hp -= damage;
            printf("%s hits %s for %d damage! (%s's HP is now: %d) \n\n", enemy->name, hero->name, damage, hero->name, hero->hp);
        } else {
            printf("%s misses their attack on %s! \n\n", enemy->name, hero->name);
        }

        printf("--------------------------------\n");;
        sleep(2);

        //Hero is defeated
        if (hero->hp <=0) {
            printf("%s has been defeated! \n\n", hero->name);
                // Loop will continue, but get_random_living_hero() will skip this hero next time  
        }
    }
}