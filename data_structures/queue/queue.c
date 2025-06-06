#include <stdio.h>
#include <stdlib.h>

// Node definition
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialize an empty queue
void init_queue(Queue* q) {
    q->front = q->rear = NULL;
}

// Check if queue is empty
int is_empty(Queue* q) {
    return q->front == NULL;
}

// Enqueue a value
void enqueue(Queue* q, int val) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = val;
    new_node->next = NULL;

    if (is_empty(q)) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

// Dequeue a value
int dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue underflow\n");
        return -1;
    }

    Node* temp = q->front;
    int val = temp->data;
    q->front = temp->next;

    if (q->front == NULL) {
        q->rear = NULL; // queue is now empty
    }

    free(temp);
    return val;
}

// Peek at front value
int peek(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->front->data;
}

// Print queue contents
void print_queue(Queue* q) {
    Node* current = q->front;
    printf("Queue (front to rear): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Free all nodes
void free_queue(Queue* q) {
    Node* temp;
    while (q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}

// Demo
int main() {
    Queue q;
    init_queue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    print_queue(&q); // 10 20 30

    printf("Dequeued: %d\n", dequeue(&q)); // 10
    printf("Peek: %d\n", peek(&q));        // 20

    print_queue(&q); // 20 30

    free_queue(&q);
    return 0;
}
