/*
A struct is a non-primitive user-defined data structure in C
*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct node_t Node;

struct node_t {
    int data;
    Node* next;
};

typedef struct queue_t Queue;

// FIFO structure implemented via a linked list
struct queue_t {
    Node* front;
    Node* back;
};

// Both front and back points to a dummy node
Queue* new_queue() {
    Queue* new = malloc(sizeof(Queue));
    new->back = malloc(sizeof(Node)); // back points to a dummy node
    new->front = new->back;
    return new;
}

bool q_is_empty(Queue* Q) {
    //Requires Q != NULL;
    return Q->front == Q->back;
}

// Add at the back, doesn't affect front
void enq(Queue* Q, int data) {
    Q->back->data = data; // Update back's value
    Q->back->next = malloc(sizeof(Node)); // Back's next is a new dummy node
    Q->back = Q->back->next; // Let back points to the new dummy node
}

int deq(Queue* Q) {
    //Requires !q_is_empty(Q);
    int data = Q->front->data;
    Node* old_front = Q->front;
    Q->front = Q->front->next;
    free(old_front); // It's important to free the dequed node to prevent memory leaks!
    return data;
}

typedef struct stack_t Stack;
struct stack_t {
    Node* top;
};

Stack* new_stack() {
    Stack* new = malloc(sizeof(Stack));
    new->top = NULL;
}

bool s_is_empty(Stack* S) {
    //Requires S != NULL;
    return S->top == NULL;
}

void push(Stack* S, int data) {
    Node* new_top = malloc(sizeof(Node));
    new_top->data = data;
    new_top->next = S->top;
    S->top = new_top;
}

int pop(Stack* S) {
    //Requires !s_is_empty(S);
    Node* old_top = S->top;
    int data = S->top->data;
    S->top = S->top->next;
    free(old_top);
    return data;
}

void print_q(Queue* Q) {
    Node* temp = Q->front;
    printf("Queue: ");
    while (temp != Q->back) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void print_s(Stack* S) {
    printf("Stack: ");
    Node* temp = S->top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue* Q = new_queue();
    printf("Printing empty Q...\n");
    print_q(Q);
    enq(Q, 1);
    enq(Q, 2);
    enq(Q, 3);
    printf("After enq 1, 2, and 3...\n");
    print_q(Q);
    printf("Run deq and we get %d\n", deq(Q));
    printf("Run deq and we get %d\n", deq(Q));
    printf("Now Q is ");
    print_q(Q);
    Stack* S = new_stack();
    printf("Printing empty S...\n");
    print_s(S);
    push(S, 1);
    push(S, 2);
    push(S, 3);
    printf("After push 1, 2, and 3...\n");
    print_s(S);
    printf("After pop we get %d\n", pop(S));
    printf("Now the stack is ");
    print_s(S);
}