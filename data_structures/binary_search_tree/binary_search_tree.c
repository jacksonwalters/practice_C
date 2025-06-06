#include <stdio.h>
#include <stdlib.h>

// Node definition
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* create_node(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insert into BST
Node* insert(Node* root, int data) {
    if (root == NULL)
        return create_node(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    // If equal, do nothing or handle duplicates here

    return root;
}

// Search for a value
int search(Node* root, int key) {
    if (root == NULL)
        return 0;
    if (key == root->data)
        return 1;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Inorder traversal (sorted order)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Free the entire tree
void delete_tree(Node* root) {
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

// Find minimum node in a subtree
Node* find_min(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// Delete a node with given key
Node* delete_node(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->data)
        root->left = delete_node(root->left, key);
    else if (key > root->data)
        root->right = delete_node(root->right, key);
    else {
        // Node to delete found
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node has two children
        Node* successor = find_min(root->right);
        root->data = successor->data;
        root->right = delete_node(root->right, successor->data);
    }
    return root;
}

int main() {
    Node* root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; ++i)
        root = insert(root, values[i]);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Deleting 20...\n");
    root = delete_node(root, 20);  // Leaf
    inorder(root); printf("\n");

    printf("Deleting 30...\n");
    root = delete_node(root, 30);  // One child
    inorder(root); printf("\n");

    printf("Deleting 50...\n");
    root = delete_node(root, 50);  // Two children
    inorder(root); printf("\n");

    delete_tree(root);
    return 0;
}

