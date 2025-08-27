#include <stdio.h>
#include <math.h>

int ability_mod(int score){
    return (int)floor((score-10)/2.0);
}

int main(void) {
    // Quick test of ability_mod function
    int test_scores[] = {8, 9, 10, 11, 12, 18};
    int n = sizeof(test_scores) / sizeof(test_scores[0]);

    printf("=== Ability Modifier Test ===\n");
    for (int i = 0; i < n; i++) {
        int score = test_scores[i];
        int mod = ability_mod(score);
        printf("Score %2d -> Modifier %+d\n", score, mod);
    }

    return 0;
}