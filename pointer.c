#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void pointers();

int main() {
    pointers();
    return 0;
}

void pointers() {
    int n = 702;                        // alloc a int on stack
    int arr[] = {1,2,3,4,5};            // create an int arr on stack
    char word[3];                       // declare a char arr on stack
    word[0] = 'A';
    word[1] = 'B';
    word[2] = 'C';
    /* Alternatively
    char word[] = "ABC";
    char word[] = {'A', 'B', 'C', '\0'}; NOTE: '\0' is a nul character
    */


    int* n_p = &n;                      // n_p is a 8 byte pointer pointing to the addr (memory location) of n
    printf("Addr of n is: %p\n", n_p);  // Print the value of n_p which is a memory location in Hex
    printf("Val of n is: %d\n", *n_p);  // Print the value of dereferenced n_p

    int* arr_p = &(arr[0]); 
    printf("Addr of first int of arr is: %p\n", arr_p);

    char* word_p = &(word[0]);
    printf("Addr of first char of word is: %p\n", word_p);
    // Note a dereferencing trick: *(p + n) == p[n]

    int length = sizeof(arr)/sizeof(*arr); // calc the correct length of any array on stack via total size divided by the size of first elem
    int* p = arr; // arr is already a pointer pointing to the addr of the first int on the stack segment if C memory
    for (int i = 0; i < length; i++) {
        printf("Addr of int at idx %d is: %p\n", i + 1, (p + i)); // or &(*(p + i)) note i means ith elem
    }

    // generic pointers (Powerful, flexible, unsafe!!! Programmers must cast the right type when dereferencing)
    int* integer = calloc(1, sizeof(int)); // calloc will set data to default values
    float* decimal = malloc(sizeof(float));
    *decimal = 3.14;
    bool yes = true;

    // create void pointers
    void* p1 = integer;
    void* p2 = decimal;
    void* p3 = &yes;

    // dereference void pointers
    printf("val pointed to by p1 is %d\n", *(int*)p1);
    printf("val pointed to by p2 is %f\n", *(float*)p2);
    printf("val pointed to by p3 is %d\n", *(bool*)p3);
}