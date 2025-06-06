#include <stdio.h>
#include <stdlib.h>

// Doubly linked list node
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Create a new node
Node* create_node(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Insert at front
void insert_front(Node** head, int data) {
    Node* new_node = create_node(data);
    new_node->next = *head;

    if (*head != NULL)
        (*head)->prev = new_node;

    *head = new_node;
}

// Insert at back
void insert_back(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* curr = *head;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = new_node;
    new_node->prev = curr;
}

// Delete first node with given value
void delete_node(Node** head, int data) {
    Node* curr = *head;

    while (curr != NULL && curr->data != data)
        curr = curr->next;

    if (curr == NULL) {
        printf("Value %d not found.\n", data);
        return;
    }

    if (curr->prev != NULL)
        curr->prev->next = curr->next;
    else
        *head = curr->next;

    if (curr->next != NULL)
        curr->next->prev = curr->prev;

    free(curr);
}

// Print list forward
void print_forward(Node* head) {
    printf("Forward: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Print list backward from tail
void print_backward(Node* head) {
    if (head == NULL) {
        printf("Backward: (empty)\n");
        return;
    }

    // Go to tail
    while (head->next != NULL)
        head = head->next;

    // Traverse backward
    printf("Backward: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->prev;
    }
    printf("\n");
}

// Free list
void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Demo
int main() {
    Node* head = NULL;

    insert_front(&head, 10);
    insert_front(&head, 5);
    insert_back(&head, 20);
    insert_back(&head, 30);

    print_forward(head);  // 5 10 20 30
    print_backward(head); // 30 20 10 5

    printf("Deleting 20...\n");
    delete_node(&head, 20);
    print_forward(head);  // 5 10 30
    print_backward(head); // 30 10 5

    free_list(head);
    return 0;
}
