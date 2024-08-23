/*
C is a general-purpose low-level language well-known for its speed and versatility
Mastering C is crucial for having a solid foundation in data structures and algorithms
*/

// Header file libraries at the top
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Function declarations
void printDataTypes();
void conditionals();
void loops();


// Technically you can write all C code in one line but it's bad style!
int main() {
    printf("Hello world!\n"); // Hello world!
    printDataTypes();
    Sleep(3000);
    conditionals();
    Sleep(3000);
    loops();
    return 0;
}

// Function definitions
void printDataTypes() {
    printf("**Basic datatypes in C**\n");
    bool yes = true, no = false;            // 1 byte
    char myChar = 'A';                      // 1 byte
    int a = 72;                             // 2 or 4 byte (usually 4)
    float b = 6.66, c = -2.0, d = 3.14;     // 4 byte
    double e = 520.52052052052;             // 8 byte
    /*
    ### Qualifiers ###
    signed: Indicates that the data type can hold both positive and negative values.
        Example: signed int num = -100;
    unsigned: Indicates that the data type can hold only non-negative values.
        Example: unsigned int num = 100;
    short: Reduces the size of the data type.
        Example: short int num = 32767;
    long: Increases the size of the data type.
        Example: long int num = 1000000;
    const: Indicates that the value of the variable cannot be changed.
        Example: const int MAX = 100;
    volatile: Indicates that the variable can be changed unexpectedly (e.g., by hardware).
        Example: volatile int timer;
    restrict: Used in pointer declarations to indicate that the pointer is the only way to access the object it points to.
        Example: int *restrict ptr;
    */

    // %[flags][width][.precision][length]specifier
    printf ("Characters: %c %c \n", 'a', 65);
    printf ("Decimals: %d %ld\n", 1977, 650000L);
    printf ("Preceding with blanks: %10d \n", 1977);
    printf ("Preceding with zeros: %010d \n", 1977);
    printf ("Some different radices of 500: %d %x %o %#x %#o \n", 500, 500, 500, 500, 500);
    printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    printf ("Width trick: %*d \n", 5, 10);
    printf ("Size type: %zu\n", (size_t)8);
    printf ("%s \n", "This is a string!");
}


void conditionals() {
    printf("\nRunning conditionals...\n");
    int age;
    printf("(Prompt)Please enter your age: ");
    scanf("%d", &age);
    getchar(); // Consume newline character left in the buffer
    const int DRINK_AGE = 21;
    if (age >= DRINK_AGE) {
        printf("You can drink alcohol!\n");
    } else if (age >= 0 && age < DRINK_AGE) {
        printf("You cannot purchase this wine!\n");
    } else {
        printf("Please enter a valid age!\n");
    }

    char grade;
    printf("(Prompt)Please report your letter grade (A, B, etc.): ");
    scanf("%c", &grade);
    getchar(); // Consume newline character left in the buffer
    switch (grade)
    {
    case 'A':
        printf("Excellent!\n");
        break;
    case 'B':
        printf("Good!\n");
        break;
    case 'C':
        printf("Mediocre.\n");
        break;
    case 'D':
        printf("Passing.\n");
        break;
    default:
        printf("You failed!\n");
        break;
    }
}

void loops() {
    printf("\nRunning loops...\n");
    Sleep(1000);
    for (int i = 0; i < 6; i++) {
        if (i == 4) {
            printf("Number reaches 4! Break!\n");
            Sleep(1000);
            break;
        }
        if (i == 2) {
            printf("Use continue at 2, skip to the next iteration\n");
            continue;
        }
        printf("i = %d\n", i);
        Sleep(1000);
    }

    int n = 10;
    printf("Counting down!\n");
    Sleep(500);
    while (n > 0) {
        printf("Time left: %d\n", n);
        n--;
        Sleep(1000);
    }
    printf("BOOM!\n");
    Sleep(1000);
    do {
        printf("This line will run at least once no matter what!\n");
    } while (n > 0);
}
