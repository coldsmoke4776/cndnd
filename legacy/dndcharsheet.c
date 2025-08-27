#include <stdio.h>
#include <math.h>
#include "dicegoblin.h"
#include "bestiary.h"

struct Character{
    char name[20]; char class[20]; char alignment[20]; int strength; int dexterity; int constitution; int intelligence; int wisdom; int charisma; int hp;
};

int ability_mod(int score){
    return (int)floor((score-10)/2.0);
}

void print_welcome(void) {
    printf("Welcome to C&D&D!\n\n");  // does something, but returns nothing
}

void combat(struct Character *hero, struct Monster *enemy) {
    printf("=== An Encounter Begins! === \n");
    printf("\n");
    printf("An angry %s appears! (HP: %d, AC: %d, Att.Bon: %d, Dmg.Die: D%d, Dmg.Bon: %d)\n", enemy-> name, enemy->hp, enemy->armorclass, enemy->attackbonus, enemy->damagedie, enemy->damagebonus);
    printf("\n");
    printf("Swords in hand, spells at the ready, the party is ready to fight! \n");
    printf("\n");

    while (hero->hp >0 && enemy->hp >0) {
        //Hero attacks
        printf("=== %s's Turn === \n\n", hero->name);
        int hero_attackroll = roll_dice(20) + ability_mod(hero->strength);

        if (hero_attackroll >= enemy->armorclass) {
            int damage = roll_dice(6) + ability_mod(hero->strength);
            enemy->hp -= damage;
            printf("%s hits the %s for %d damage! (Ememy HP is now: %d) \n\n", hero->name, enemy->name, damage, enemy->hp);
        } else {
            printf("%s misses the %s! \n\n", hero->name, enemy->name);
        }

        // Enemy is defeated
        if (enemy->hp <=0) {
            printf("%s has been defeated! \n\n", enemy->name);
            break;
        }

        //Enemy attacks
        printf("=== %s's turn === \n\n", enemy->name);
        int enemy_attackroll = roll_dice(20) + enemy->damagebonus; 
        //NOTE: We are using 10 + the hero's DEX modifier to determine if the hero is hit in lieu of hero AC currently
        if (enemy_attackroll >= 10 + ability_mod(hero->dexterity)) {
            int damage = roll_dice(enemy->damagedie) + enemy->damagebonus;
            hero->hp -= damage;
            printf("%s hits %s for %d damage! (%s's HP is now: %d) \n\n", enemy->name, hero->name, damage, hero->name, hero->hp);
        } else {
            printf("%s misses their attack on %s! \n\n", enemy->name, hero->name);
        }

        //Hero is defeated
        if (hero->hp <=0) {
            printf("%s has been defeated! \n\n", hero->name);
            break;  
        }
    }
}

int main(void) {
    struct Character party[4]; // this is the array to hold the 4 character party members
    int initiativeroll[4];
    
    for (int i=0; i <4; i++) {
        printf("\n === Creating Character %d ===\n ", i+1);
        printf("Enter the name of the character (make it fun): ");
        scanf("%19s", party[i].name);
        printf("What is %s's alignment? ", party[i].name);
        scanf(" %19[^\n]", party[i].alignment);
        printf("What class is %s?\n", party[i].name);
        scanf(" %19[^\n]", party[i].class);
        printf("What is %s's strength?\n ", party[i].name);
        scanf("%d", &party[i].strength);
        printf("What is %s's dexterity?\n ", party[i].name);
        scanf("%d", &party[i].dexterity);
        printf("What is %s's constitution?\n ", party[i].name);
        scanf("%d", &party[i].constitution);
        printf("What is %s's intelligence?\n ", party[i].name);
        scanf("%d", &party[i].intelligence);
        printf("What is %s's wisdom?\n ", party[i].name);
        scanf("%d", &party[i].wisdom);
        printf("What is %s's charisma?\n ", party[i].name);
        scanf("%d", &party[i].charisma);
        printf("What is %s's hp?\n ", party[i].name);
        scanf("%d", &party[i].hp);
        printf("Your character is %s, a %s %s with a STR of %d, DEX of %d, CON of %d, INT of %d, WIS of %d, CHA of %d, and %d HP.\n", party[i].name, party[i].alignment, party[i].class, party[i].strength, party[i].dexterity, party[i].constitution, party[i].intelligence, party[i].wisdom, party[i].charisma, party[i].hp);
    }

    // Display Party Summary
    printf("\n=== Party Summary ===\n");
    for (int i=0; i<4; i++) {
        printf("%d. %s - %s %s (HP: %d) \n", i+1, party[i].name, party[i].alignment, party[i].class, party[i].hp);
        printf("STR: %2d (%+d), DEX: %2d (%+d), CON: %2d (%+d)\n", party[i].strength, ability_mod(party[i].strength), party[i].dexterity, ability_mod(party[i].dexterity), party[i].constitution, ability_mod(party[i].constitution));
        printf("INT: %2d (%+d), WIS: %2d (%+d), CHA: %2d (%+d)\n", party[i].intelligence, ability_mod(party[i].intelligence), party[i].wisdom, ability_mod(party[i].wisdom), party[i].charisma, ability_mod(party[i].charisma));
        printf("-----------------------------------\n");
        printf("\n\n");
    }

    // Initialize the RNG to ensure we get different results every time we play
    init_rng();

    // Roll for initiative!
    printf("=== Rolling for Initiative === \n");
    for (int i=0; i<4; i++) {
        int d20 = roll_dice(20);
        int dex_modifier = ability_mod(party[i].dexterity);
        initiativeroll[i] = d20 + dex_modifier;
        
        printf("%s rolls a %d and adds %d for a total of %d\n", party[i].name, d20, dex_modifier, initiativeroll[i]);
        printf("-----------------------------------\n");
    }

    // Sort Characters by initiative roll and determine turn order
    for (int i=0; i<4; i++) {
        for (int j=0; j<4 - i-1; j++) {
            if (initiativeroll[j] < initiativeroll[j+1]) {
                // Swap the initative values
                int tempInitiative = initiativeroll[j];
                initiativeroll[j] = initiativeroll[j+1];
                initiativeroll[j+1] = tempInitiative;
                
                // Swap the character names
                struct Character tempCharacterName = party[j];
                party[j] = party[j+1];

                party[j+1] = tempCharacterName;
            }
        }
    }
        // Display the sorted turn order
        printf("\n\n");
        printf("=== Combat Turn Order === \n");
            for (int i=0; i<4; i++) {
                printf("%d. %s (Initiative: %d) \n", i+1, party[i].name, initiativeroll[i]);
            }
        printf("\n\n");

        // Pick a random monster from the bestiary to fight
        int index = roll_dice(NUM_MONSTERS) -1;
        struct Monster *enemy = &bestiary[index];

        // Just for testing purposes, we're only going to have the first character fight the monster
        combat(&party[0], enemy);

        return 0;
    }


