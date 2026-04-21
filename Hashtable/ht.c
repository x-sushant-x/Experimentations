#include "ht.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

ht* ht_create(void) {
    ht* table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }

    table->length = 0;
    table->cap = INITIAL_CAPACITY;

    table->entries = calloc(table->cap, sizeof(ht_entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

void ht_destroy(ht* table) {
    for (size_t i = 0; i < table->cap; i++) {
        void* entry = table->entries[i].key;
        free(entry);
    }

    free(table->entries);
    free(table);
}

/*
    Simple hashing function using FNV-1a algorithm.

    Steps:
    1. Xor each byte of key with OFFSET constant.
    2. Multiply result by PRIME constant.
    3. OFFSET & PRIME are already defined.
*/
static size_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;

    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }

    return hash;
}

void* ht_get(ht* table, const char* key) {
    uint64_t hash = hash_key(key);

    // This is equivalent to hash % table->capacity but faster.
    // This only works because capacity is power of 2.
    size_t index = (size_t)(hash & (uint64_t)(table->cap - 1));

    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            return table->entries[index].value;
        }

        index++;

        if (index >= table->cap) {
            index = 0;
        }
    }

    return NULL;
}

const char* ht_set(ht* table, const char* key, void* value) {
    if (value == NULL) {
        return NULL;
    }

    if (table->length >= table->cap / 2) {
        if (!ht_expand(table)) {
            return NULL;
        }
    }

    // TODO - Set Entry Function
}

static bool ht_expand(ht* table) {
    size_t new_cap = table->cap * 2;
    if (new_cap < table->cap) {
        return false;
    }

    ht_entry* new_entries = calloc(new_cap, sizeof(ht_entry));
    if (new_entries == NULL) {
        return false;
    }

    for (size_t i = 0; i < table->cap; i++) {
        ht_entry entry = table->entries[i];

        if (entry.key != NULL) {
            // TODO - Set Entry function
        }
    }

    free(table->entries);
    table->entries = new_entries;
    table->cap = new_cap;
    return true;
}

int main(int argc, char** argv) { return 0; }