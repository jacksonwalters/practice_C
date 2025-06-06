#include <stdio.h>
#include <stdlib.h>

// Node definition
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Push: add new node at top
void push(Node** top, int val) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = val;
    new_node->next = *top;
    *top = new_node;
}

// Pop: remove top node and return value
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack underflow\n");
        return -1;
    }
    Node* temp = *top;
    int val = temp->data;
    *top = temp->next;
    free(temp);
    return val;
}

// Peek: look at top value without removing
int peek(Node* top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}

// Is empty
int is_empty(Node* top) {
    return top == NULL;
}

// Print stack contents
void print_stack(Node* top) {
    printf("Stack (top to bottom): ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

// Free all nodes
void free_stack(Node* top) {
    Node* temp;
    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
}

// Demo
int main() {
    Node* stack = NULL;

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    print_stack(stack); // 30 20 10

    printf("Popped: %d\n", pop(&stack)); // 30
    printf("Peek: %d\n", peek(stack));   // 20

    print_stack(stack); // 20 10

    free_stack(stack);
    return 0;
}
