#include "ht.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16

typedef struct {
    const char* key;
    void* value;
} ht_entry;

struct ht {
    ht_entry* entries;
    size_t capacity;
    size_t length;
};

ht* ht_create(void) {
    ht* table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }

    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    table->entries = calloc(table->capacity, sizeof(ht_entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

void ht_destroy(ht* table) {
    for (size_t i = 0; i < table->capacity; i++) {
        void* entry = table->entries[i].key;
        free(entry);
    }

    free(table->entries);
    free(table);
}

int main(int argc, char** argv) { return 0; }