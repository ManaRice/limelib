#include "../include/hashmap.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HASHMAP_SIZE 100
#define MAX_KEY_LEN 255


struct IntEntry
{
    int64_t          hash;
    int32_t          value;
    struct IntEntry* next;
};

struct IntBucket
{
    bool             empty;
    struct IntEntry* entry;
};

struct IntHashMap
{
    size_t            size;
    struct IntBucket* map;
};

struct PtrEntry
{
    int64_t          hash;
    void*            ptr;
    struct PtrEntry* next;
};

struct PtrBucket
{
    bool empty;
    struct PtrEntry* entry;
};

struct PtrHashMap
{
    size_t size;
    struct PtrBucket* map;
};


IntHashMap* int_hashmap_create()
{
    IntHashMap* hashmap;
    hashmap = malloc(sizeof(IntHashMap));
    if (hashmap == NULL)
    {
        fprintf(stderr, "IntHashMap init failed\n");
        return NULL;
    }
    hashmap->size = HASHMAP_SIZE;
    hashmap->map = malloc(sizeof(struct IntBucket) * HASHMAP_SIZE);
    if (hashmap->map == NULL)
    {
        fprintf(stderr, "IntHashMap init failed\n");
        return NULL;
    }
    struct IntBucket empty_bucket = {.empty = true, .entry = NULL};

    for (size_t i = 0; i < HASHMAP_SIZE; i++)
    {
        memcpy(hashmap->map + i, &empty_bucket, sizeof(struct IntBucket));
    }

    return hashmap;
}

PtrHashMap* ptr_hashmap_create()
{
    PtrHashMap* hashmap;
    hashmap = malloc(sizeof(PtrHashMap));
    if (hashmap == NULL)
    {
        fprintf(stderr, "HashMap init failed\n");
        return NULL;
    }
    hashmap->size = HASHMAP_SIZE;
    hashmap->map = malloc(sizeof(struct PtrBucket) * HASHMAP_SIZE);
    if (hashmap->map == NULL)
    {
        fprintf(stderr, "HashMap init failed\n");
        return NULL;
    }
    struct PtrBucket empty_bucket = {.empty = true, .entry = NULL};

    for (size_t i = 0; i < HASHMAP_SIZE; i++)
    {
        memcpy(hashmap->map + i, &empty_bucket, sizeof(struct PtrBucket));
    }

    return hashmap;
}

int64_t get_hash(char* key)
{
    char c = *key;
    int64_t hash = 5381;

    for (size_t i = 0; c != '\0' && i < 255; i++)
    {
        hash = ((hash << 5) + hash) + c;
        c = *(++key);
    }
    return hash = hash < 0 ? -hash : hash;
}

bool int_hashmap_add(IntHashMap* hashmap, char* key, int32_t value)
{
    int64_t hash = get_hash(key);
    int32_t index = hash % HASHMAP_SIZE;
    struct IntEntry new_entry = {.hash = hash, .value = value, .next = NULL};

    if (hashmap->map[index].empty == true)
    {
        void* new_entry_mem = malloc(sizeof(struct IntEntry));
        memcpy(new_entry_mem, &new_entry, sizeof(struct IntEntry));
        hashmap->map[index].empty = false;
        hashmap->map[index].entry = new_entry_mem;
        return true;
    }

    struct IntEntry* old_entry = hashmap->map[index].entry;

    while (old_entry->next != NULL && old_entry->hash == hash)
        old_entry = old_entry->next;


    if (old_entry->hash == hash)
        return false;

    void* new_entry_mem = malloc(sizeof(struct IntEntry));
    if (new_entry_mem == NULL)
    {
        fprintf(stderr ,"Adding to hashmap failed\n");
        return false;
    }
    memcpy(new_entry_mem, &new_entry, sizeof(struct IntEntry));
    old_entry->next = new_entry_mem;
    return true;
}

bool ptr_hashmap_add(PtrHashMap* hashmap, char* key, void* ptr)
{
    int64_t hash = get_hash(key);
    int32_t index = hash % HASHMAP_SIZE;
    struct PtrEntry new_entry = {.hash = hash, .ptr = ptr, .next = NULL};

    if (hashmap->map[index].empty == true)
    {
        void* new_entry_mem = malloc(sizeof(struct PtrEntry));
        memcpy(new_entry_mem, &new_entry, sizeof(struct PtrEntry));
        hashmap->map[index].empty = false;
        hashmap->map[index].entry = new_entry_mem;
        return true;
    }

    struct PtrEntry* old_entry = hashmap->map[index].entry;

    while (old_entry->next != NULL && old_entry->hash == hash)
        old_entry = old_entry->next;


    if (old_entry->hash == hash)
        return false;

    void* new_entry_mem = malloc(sizeof(struct PtrEntry));
    if (new_entry_mem == NULL)
    {
        fprintf(stderr ,"Adding to hashmap failed\n");
        return false;
    }
    memcpy(new_entry_mem, &new_entry, sizeof(struct PtrEntry));
    old_entry->next = new_entry_mem;
    return true;
}

OptionalInt int_hashmap_get(IntHashMap* hashmap, char* key)
{
    OptionalInt opt = {.value = 0, .has_value = false};

    int64_t hash = get_hash(key);
    int32_t index = hash % HASHMAP_SIZE;

    if (hashmap->map[index].empty)
        return opt;


    struct IntEntry* entry = hashmap->map[index].entry;


    if (entry->hash == hash)
    {
        opt.value = entry->value;
        opt.has_value = true;
        return opt;
    }

    while (entry->next != NULL)
    {
        entry = entry->next;
        if (entry->hash == hash)
        {
            opt.value = entry->value;
            opt.has_value = true;
            return opt;
        }
    }

    return opt;
}

OptionalPtr ptr_hashmap_get(PtrHashMap* hashmap, char* key)
{
    OptionalPtr opt = {.value = NULL, .has_value = false};

    int64_t hash = get_hash(key);
    int32_t index = hash % HASHMAP_SIZE;

    if (hashmap->map[index].empty)
        return opt;

    struct PtrEntry* entry = hashmap->map[index].entry;


    if (entry->hash == hash)
    {
        opt.value = entry->ptr;
        opt.has_value = true;
        return opt;
    }

    while (entry->next != NULL)
    {
        entry = entry->next;
        if (entry->hash == hash)
        {
            opt.value = entry->ptr;
            opt.has_value = true;
            return opt;
        }
    }

    return opt;
}
