#ifndef BESTIARY_H
#define BESTIARY_H
#include "bestiary.h"

struct Monster {
    char name[20];
    int hp;
    int armorclass; // Target to hit
    int attackbonus;
    int damagedie; // Dice monster rolls to hit
    int damagebonus; // Bonus to monster damage
};

extern struct Monster bestiary[ ];
extern const int NUM_MONSTERS;



#endif