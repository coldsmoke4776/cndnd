#ifndef CHARACTER_H
#define CHARACTER_H

struct Character {
    char name[20]; 
    char class[20]; 
    char alignment[20]; 
    int strength; 
    int dexterity; 
    int constitution; 
    int intelligence; 
    int wisdom; 
    int charisma; 
    int ac; // new field for character armor class for more advanced combat mechanics
    int hp;
    int damagedie; //new field for damage die (6 = d6, 8 = d8, etc)
    int damagebonus; //new field for a flat damage bonus to attacks, usually from STR or DEX depending on the weapon
};

struct Character *create_character(
    const char *name, const char *class, const char *alignment,
    int hp, int strength, int dexterity, int constitution, int intelligence,int wisdom,int charisma, int ac, int damagedie, int damagebonus);


int ability_mod(int score);
void print_character(struct Character *c);
void print_party(struct Character party[], int count);
void free_character(struct Character *c);
void save_party(struct Character party[], int count, const char *filename);
int load_party(struct Character party[], int max_count, const char *filename);


#endif