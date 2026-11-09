#include <stdio.h>

#define TABLE_SIZE 10

int hash(int key) { return key % TABLE_SIZE; }

typedef struct Node {
        int key;
        int value;
        struct Node *next;
} Node;

typedef struct {
        Node **entries;
        int capacity;
} Map;

int mapGet(Map *map, int key) {
    int hash_val = hash(key);
    Node **nodes = map->entries;
    if (nodes == NULL) {
        printf("invalid Map, entries not initialized");
        // I think ideally we would want to crash the project at this point
        return -1;
    }

    if (hash_val >= map->capacity) {
        printf("invalid node index, index larger than map capacity");
        return -1;
    }

    Node *current = nodes[hash_val];
    while (current != NULL) {
        if (key == current->key) {
            return current->value;
        }
        current = current->next;
    }

    return -1;
}

int main() { return 0; }
