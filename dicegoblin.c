#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dicegoblin.h"

void init_rng(void) {
    srand((unsigned int)time(NULL));
}

int roll_dice(int sides) {
    return rand() % sides +1;
}

int roll_dice_w_advantage(int sides){
    int firstroll = roll_dice(sides);
    int secondroll = roll_dice(sides);
    return firstroll > secondroll ? firstroll : secondroll;
}

int roll_dice_w_disadvantage(int sides){
    int firstroll = roll_dice(sides);
    int secondroll = roll_dice(sides);
    return firstroll < secondroll ? firstroll : secondroll;
}
