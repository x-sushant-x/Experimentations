#include <stdio.h>
#include <stdlib.h>

#include "ht.h"

int main(int argc, char** argv) {
    ht* table = ht_create();
    if (!table) {
        printf("Failed to create table\n");
        return 1;
    }

    int* age = malloc(sizeof(int));
    *age = 22;

    ht_set(table, "sushant", age);

    int* result = (int*)ht_get(table, "sushant");

    if (result != NULL) {
        printf("Age: %d\n", *result);
    }

    return 0;
}