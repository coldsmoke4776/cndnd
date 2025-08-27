#include <stdio.h>
#include "bestiary.h"

struct Monster bestiary[] = {
    {"Goblin", 10, 12, 3, 6, 0},
    {"Orc", 15, 13, 5 ,8, 1},
    {"Bandit", 11, 12, 1, 6, 0},
    {"Basilisk", 52, 15, 10, 12, 2},
    {"Gelatinous Cube", 63, 6, 8, 6, 2},
    {"Gnoll Warrior", 27, 15, 4, 6, 2},
    {"Sahaugin Warrior", 22, 12, 3, 6, 1},
    {"Kobold", 5, 12, 4, 4, 2},
    {"Skeleton", 13, 13, 4, 6, 2},
    {"Zombie", 22, 8, 3, 6, 1},
    {"Giant Rat", 10, 10, 2, 4, 0},
    {"Ogre", 59, 11, 6, 10, 4},             
    {"Troll", 84, 15, 7, 6, 4},             
    {"Werewolf", 58, 11, 4, 8, 2},          
    {"Wyvern", 110, 13, 7, 6, 4},           
    {"Young Red Dragon", 178, 18, 10, 10, 6} // Boss-level threat
};

const int NUM_MONSTERS = sizeof(bestiary)/sizeof(bestiary[0]);
