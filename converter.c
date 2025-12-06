#include <stdio.h>
int main() {
    printf("Converter\n");
    printf("Type 1 to convert Celsius to Fahrenheit\n");
    printf("Type 2 to convert Fahrenheit to Celsius\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        float celsius;
        printf("Enter temperature in Celsius: ");
        scanf("%f", &celsius);
        float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
        printf("Temperature in Fahrenheit: %.2f\n", fahrenheit);
    } else if (choice == 2) {
        float fahrenheit;
        printf("Enter temperature in Fahrenheit: ");
        scanf("%f", &fahrenheit);
        float celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
        printf("Temperature in Celsius: %.2f\n", celsius);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}