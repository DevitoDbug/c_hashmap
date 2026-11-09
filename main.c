#include <stdio.h>
#include <stdlib.h>

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

Map *mapNew(int capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    Node **entries = malloc(sizeof(Node *) * capacity);
    if (entries == NULL) {
        printf("failed to allocate memory for the entries");
        return NULL;
    }
    for (int i = 0; i < capacity; i++) {
        Node *entry = malloc(sizeof(Node));
        if (entry == NULL) {
            printf("failed to allocate memory for all the entries");
            return NULL;
        }
        entries[i] = entry;
    }

    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        printf("failed to allocate memory for map");
        return NULL;
    }
    map->entries = entries;
    map->capacity = capacity;

    return map;
}

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

int main() {
    Map *map = mapNew(4);

    return 0;
}
