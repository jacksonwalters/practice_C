#include <stdio.h>
#include <stdlib.h>

// Node definition
typedef struct Node {
    int data;
    struct Node* next;
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
    return new_node;
}

// Insert at the front
void insert_front(Node** head, int data) {
    Node* new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Insert at the back
void insert_back(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
}

// Delete the first node with a given value
void delete_node(Node** head, int data) {
    Node* curr = *head;
    Node* prev = NULL;

    while (curr != NULL && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Value %d not found.\n", data);
        return;
    }

    if (prev == NULL) {
        *head = curr->next; // deleting head
    } else {
        prev->next = curr->next;
    }

    free(curr);
}

// Print the list
void print_list(Node* head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Free all nodes
void free_list(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

// Reverse the list in-place
void reverse_list(Node** head) {
    Node* prev = NULL;
    Node* curr = *head;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next;     // Store next node
        curr->next = prev;     // Reverse the link
        prev = curr;           // Move prev forward
        curr = next;           // Move curr forward
    }

    *head = prev;              // New head is the last node
}

// Demo / test
int main() {
    Node* head = NULL;

    insert_back(&head, 10);
    insert_back(&head, 20);
    insert_front(&head, 5);
    insert_back(&head, 30);

    print_list(head); // 5 -> 10 -> 20 -> 30 -> NULL

    delete_node(&head, 20);
    print_list(head); // 5 -> 10 -> 30 -> NULL

    delete_node(&head, 99); // Value not found

    reverse_list(&head);
    print_list(head); // 30 -> 10 -> 5 -> NULL

    free_list(head);
    return 0;
}
