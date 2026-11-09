#include <stdio.h>

#define TABLE_SIZE 10

int hash(int key) { return key % TABLE_SIZE; }

typedef struct {
        int Key;
        int Value;
} Entry;

int mapGet(Entry *entries, int key) { return entries[hash(key)].Value; }

int main() {
    Entry entries[TABLE_SIZE] = {0};

    // Insert key value par
    entries[hash(25)].Key = 25;
    entries[hash(25)].Value = 42;

    // Retrieve  value
    printf("key: %d, value: %d\n", 25, mapGet(entries, 25));
}
