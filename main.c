#include <stdio.h>

#define TABLE_SIZE 10

typedef struct {
        int Key;
        int Value;
} Entry;

int hash(int key) { return key % TABLE_SIZE; }

int main() {
    Entry entries[TABLE_SIZE] = {0};

    // Insert key value par
    entries[hash(25)].Key = 25;
    entries[hash(25)].Value = 42;

    // Retrieve  value
    printf("key: %d, value: %d\n", entries[hash(25)].Key,
           entries[hash(25)].Value);
}
