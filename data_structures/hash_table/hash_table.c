#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Entry {
    char* key;
    int value;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    Entry* buckets[TABLE_SIZE];
} HashTable;

// djb2 hash function (string -> index)
unsigned int hash(const char* key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

// Create an empty hash table
HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) exit(1);
    for (int i = 0; i < TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    return table;
}

// Insert or update key-value pair
void insert(HashTable* table, const char* key, int value) {
    unsigned int idx = hash(key);
    Entry* head = table->buckets[idx];

    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            head->value = value; // update
            return;
        }
        head = head->next;
    }

    Entry* new_entry = malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = table->buckets[idx];
    table->buckets[idx] = new_entry;
}

// Get value by key
int get(HashTable* table, const char* key) {
    unsigned int idx = hash(key);
    Entry* head = table->buckets[idx];
    while (head != NULL) {
        if (strcmp(head->key, key) == 0)
            return head->value;
        head = head->next;
    }
    return -1; // not found
}

// Delete entry by key
void delete(HashTable* table, const char* key) {
    unsigned int idx = hash(key);
    Entry* head = table->buckets[idx];
    Entry* prev = NULL;

    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            if (prev) prev->next = head->next;
            else table->buckets[idx] = head->next;
            free(head->key);
            free(head);
            return;
        }
        prev = head;
        head = head->next;
    }
}

// Free all entries and table
void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* head = table->buckets[i];
        while (head != NULL) {
            Entry* temp = head;
            head = head->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table);
}

// Print all key-value pairs
void print_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* head = table->buckets[i];
        while (head != NULL) {
            printf("Key: %s → Value: %d\n", head->key, head->value);
            head = head->next;
        }
    }
}

int main() {
    HashTable* table = create_table();

    insert(table, "apple", 3);
    insert(table, "banana", 5);
    insert(table, "orange", 7);

    printf("apple: %d\n", get(table, "apple"));   // 3
    printf("banana: %d\n", get(table, "banana")); // 5

    delete(table, "banana");
    printf("banana: %d\n", get(table, "banana")); // -1

    print_table(table);

    free_table(table);
    return 0;
}
