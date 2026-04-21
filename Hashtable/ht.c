#include "ht.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

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

int main(int argc, char** argv) { return 0; }