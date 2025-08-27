#include <stdio.h>

int main(void) {
    int age;
    char firstname[20];
    char lastname[20];
    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your first name: ");
    scanf("%19s", firstname);

    printf("Enter your last name: ");
    scanf("%19s", lastname);

    printf("Hello, You are %s %s and you are %d years old\n", firstname, lastname, age);
    
    return 0;
}