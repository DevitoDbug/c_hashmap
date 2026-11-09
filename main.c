#include <stdbool.h>
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
} Map;

Map *mapNew() {
    if (TABLE_SIZE <= 0) {
        return NULL;
    }

    Node **entries = malloc(sizeof(Node *) * TABLE_SIZE);
    if (entries == NULL) {
        printf("failed to allocate memory for the entries");
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        // It is easier to check for indexes that have no lists or rather no
        // node
        entries[i] = NULL;
    }

    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        printf("failed to allocate memory for map");
        return NULL;
    }
    map->entries = entries;

    return map;
}

bool mapSet(Map *map, int key, int value) {
    if (map == NULL) {
        printf("invalid map passed. Map is NULL");
        return false;
    }

    int hash_val = hash(key);
    Node *current = map->entries[hash_val];
    Node *prev = NULL;

    if (current == NULL) {
        Node *new_entry = malloc(sizeof(Node));
        if (new_entry == NULL) {
            printf("failed to allocate memory for all the entries");
            return false;
        }
        new_entry->value = value;
        new_entry->key = key;
        new_entry->next = NULL;
        map->entries[hash_val] = new_entry;
        return true;
    }

    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return true;
        }
        prev = current;
        current = current->next;
    }

    // No key found with that value
    // At this point the assumption is prev can not be NULL
    Node *new_entry = malloc(sizeof(Node));
    if (new_entry == NULL) {
        printf("failed to allocate memory for all the entries");
        return false;
    }
    new_entry->value = value;
    new_entry->key = key;
    new_entry->next = NULL;
    prev->next = new_entry;

    return true;
}

bool mapGet(Map *map, int key, int *value) {
    // Reset value
    *value = -1;

    if (map == NULL) {
        printf("invalid map instance. Map is set to NULL");
        return false;
    }

    int hash_val = hash(key);
    Node **nodes = map->entries;
    if (nodes == NULL) {
        printf("invalid Map, entries not initialized \n");
        // I think ideally we would want to crash the project at this point
        return false;
    }

    if (hash_val >= TABLE_SIZE) {
        printf("invalid node index, index larger than map capacity\n");
        return false;
    }

    Node *current = nodes[hash_val];
    while (current != NULL) {
        if (key == current->key) {
            *value = current->value;
            return true;
        }
        current = current->next;
    }

    return false;
}

bool mapDelete(Map *map, int key) {
    if (map == NULL) {
        printf("invalid map instance. Map is set to NULL");
        return false;
    }

    int hash_val = hash(key);
    Node *current = map->entries[hash_val];
    Node *prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            Node *deleted = current;
            if (prev == NULL) {
                map->entries[hash_val] = current->next;

                if (deleted != NULL) {
                    free(deleted);
                }
                return true;
            }
            prev->next = current->next;
            if (deleted != NULL) {
                free(deleted);
            }
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

void mapFree(Map *map) {
    if (map == NULL) {
        printf("Map is empty");
        return;
    }

    if (map->entries != NULL) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node *current = map->entries[i];

            while (current != NULL) {
                Node *next = current->next;
                free(current);

                current = next;
            }
        }

        free(map->entries);
    }

    free(map);
}

// TODO:
//  - Deleting
//  - Resizing
//  - Generic values

int main() {
    Map *map = mapNew();
    mapSet(map, 2, 10);
    mapSet(map, 100, 9);
    mapSet(map, 50, 3);
    int val = -1;
    mapGet(map, 2, &val);
    printf("key: %d, value: %d\n", 2, val);
    mapGet(map, 100, &val);
    printf("key: %d, value: %d\n", 100, val);
    mapGet(map, 50, &val);
    printf("key: %d, value: %d\n", 50, val);

    mapDelete(map, 100);
    mapGet(map, 100, &val);
    printf("after delete==>key: %d, value: %d\n", 100, val);
    mapFree(map);

    return 0;
}
