#ifndef DICEGOBLIN_H
#define DICEGOBLIN_H

// Seeding the RNG to ensure we get different results every time we play
void init_rng(void);


// Rolling a single die (d6, d8, d10, d12, d20 etc.)
int roll_dice(int sides);

// Rolling dice with advantage
int roll_dice_w_advantage(int sides);

// Rolling dice with disadvantage
int roll_dice_w_disadvantage(int sides);

#endif

