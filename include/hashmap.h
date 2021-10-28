#pragma once
#include <stdbool.h>
#include "optional.h"

typedef struct IntHashMap IntHashMap;

typedef struct PtrHashMap PtrHashMap;

IntHashMap* int_hashmap_create();

bool int_hashmap_add(IntHashMap* hashmap, char* key, int value);

OptionalInt int_hashmap_get(IntHashMap* hashmap, char* key);

void int_hashmap_destroy(IntHashMap* hashmap);

PtrHashMap* ptr_hashmap_create();

bool ptr_hashmap_add(PtrHashMap* hashmap, char* key, void* ptr);

OptionalPtr ptr_hashmap_get(PtrHashMap* hashmap, char* key);
