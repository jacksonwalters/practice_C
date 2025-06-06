#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

// Initialize stack
void init_stack(Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int is_empty(Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int is_full(Stack* s) {
    return s->top == MAX - 1;
}

// Push onto stack
void push(Stack* s, int val) {
    if (is_full(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = val;
}

// Pop from stack
int pop(Stack* s) {
    if (is_empty(s)) {
        printf("Stack underflow\n");
        return -1; // You can define a better sentinel if needed
    }
    return s->items[(s->top)--];
}

// Peek at top of stack
int peek(Stack* s) {
    if (is_empty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top];
}

// Print stack contents
void print_stack(Stack* s) {
    printf("Stack (top to bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

// Demo
int main() {
    Stack s;
    init_stack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    print_stack(&s);  // Stack (top to bottom): 30 20 10

    printf("Popped: %d\n", pop(&s)); // 30
    printf("Top: %d\n", peek(&s));   // 20

    print_stack(&s);  // Stack (top to bottom): 20 10

    return 0;
}
