#include "../limelib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


struct IntList
{
    int* list_memory;
    size_t list_index;
    size_t list_size;
    char empty;
};

struct U8List
{
    uint8_t* list_memory;
    size_t list_index;
    size_t list_size;
    char empty;
};

struct List
{
    uint8_t* list_memory;
    size_t list_index;
    size_t list_size;
    size_t element_size;
    char empty;
};

float get_multiplyer(size_t size)
{
        if (size <= 10)
            return 2.0f;
        if (size <= 100)
            return 1.9f;
        if (size <= 1000)
            return 1.8f;
        if (size <= 10000)
            return 1.7f;
        if (size <= 100000)
            return 1.6f;

        return 1.5f;
}

IntList* int_list_create(size_t size)
{
    IntList* list;
    list = malloc(sizeof(IntList));
    if (list == NULL)
    {
        fprintf(stderr, "IntList init failed\n");
        return NULL;
    }
    list->list_size = size;
    list->list_memory = malloc(size * sizeof(int));
    if (list->list_memory == NULL)
    {
        fprintf(stderr, "IntList init failed\n");
        return NULL;
    }
    list->list_index = 0;
    list->empty = 0;
    return list;
}

U8List* u8_list_create(size_t size)
{
    U8List* list;
    list = malloc(sizeof(U8List));
    if (list == NULL)
    {
        fprintf(stderr, "IntList init failed\n");
        return NULL;
    }
    list->list_size = size;
    list->list_memory = malloc(size * sizeof(uint8_t));
    if (list->list_memory == NULL)
    {
        fprintf(stderr, "IntList init failed\n");
        return NULL;
    }
    list->list_index = 0;
    list->empty = 0;
    return list;
}

List* list_create(size_t size, size_t element_size)
{
    List* list;
    list = malloc(sizeof(List));
    if (list == NULL)
    {
        fprintf(stderr, "IntList init failed\n");
        return NULL;
    }
    list->list_size = size;
    list->element_size = element_size;
    list->list_memory = malloc(size * element_size);
    if (list->list_memory == NULL)
    {
        fprintf(stderr, "IntList init failed\n");
        return NULL;
    }
    list->list_index = 0;
    list->empty = 0;
    return list;
}

int int_list_append(IntList* list, int num)
{
    int reallocateing = 0;
    if (list->list_index >= list->list_size)
    {
        reallocateing = 1;
        size_t new_size = (size_t)(list->list_size * get_multiplyer(list->list_size));

        int* new_memory = malloc(new_size * sizeof(int));
        for (int i = 0; i < list->list_size; i++)
            new_memory[i] = list->list_memory[i];

        list->list_memory = new_memory;
        if (list->list_memory == NULL)
        {
            fprintf(stderr, "IntList expansion failed\n");
            return -1;
        }
        list->list_size = new_size;
    }
    list->list_memory[list->list_index] = num;
    list->list_index++;
    list->empty = 0;
    return reallocateing;
}

int u8_list_append(U8List* list, uint8_t num)
{
    int reallocateing = 0;
    if (list->list_index >= list->list_size)
    {
        reallocateing = 1;
        size_t new_size = (size_t)(list->list_size * get_multiplyer(list->list_size));

        uint8_t* new_memory = malloc(new_size * sizeof(uint8_t));
        for (int i = 0; i < list->list_size; i++)
            new_memory[i] = list->list_memory[i];

        list->list_memory = new_memory;
        if (list->list_memory == NULL)
        {
            fprintf(stderr, "IntList expansion failed\n");
            return -1;
        }
        list->list_size = new_size;
    }
    list->list_memory[list->list_index] = num;
    list->list_index++;
    list->empty = 0;
    return reallocateing;
}

int list_append(List* list, void* element)
{
    int reallocateing = 0;
    if (list->list_index >= list->list_size)
    {
        reallocateing = 1;
        size_t new_size = (size_t)(list->list_size * get_multiplyer(list->list_size));

        uint8_t* new_memory = malloc(new_size * list->element_size);
        memcpy(new_memory, list->list_memory,
            list->list_size * list->element_size);

        //for (int i = 0; i < list->list_size; i++)
            //new_memory[i] = list->list_memory[i];

        if (list->list_memory == NULL)
        {
            fprintf(stderr, "List expansion failed\n");
            return -1;
        }
        list->list_size = new_size;
    }
    memcpy(list->list_memory + (list->list_index * list->element_size),
    element, list->element_size);
    list->list_index++;
    list->empty = 0;
    return reallocateing;
}

OptionalInt int_list_get(IntList* list, size_t index)
{
    OptionalInt opt;
    if (index < 0 || index >= list->list_index || list->empty)
    {
        opt.value = 0;
        opt.has_value = false;
        return opt;
    }

    opt.value = list->list_memory[index];
    opt.has_value = true;
    return opt;
}

OptionalU8 u8_list_get(U8List* list, size_t index)
{
    OptionalU8 opt;
    if (index < 0 || index >= list->list_index || list->empty)
    {
        opt.value = 0;
        opt.has_value = false;
        return opt;
    }

    opt.value = list->list_memory[index];
    opt.has_value = true;
    return opt;
}

OptionalPtr list_get(List* list, size_t index)
{
    OptionalPtr opt;
    if (index < 0 || index >= list->list_index || list->empty)
    {
        opt.error = 1;
        opt.has_value = false;
        return opt;
    }

    uint8_t* temp_ptr = list->list_memory + (index * list->element_size);
    opt.value = (void*)temp_ptr;
    opt.has_value = true;
    return opt;
}

size_t int_list_size(IntList* list)
{
    return list->list_index;
}

size_t u8_list_size(U8List* list)
{
    return list->list_index;
}

size_t list_size(List* list)
{
    return list->list_index;
}

void int_list_destroy(IntList* list)
{
    free(list->list_memory);
    free(list);
}

void u8_list_destroy(U8List* list)
{
    free(list->list_memory);
    free(list);
}

void list_destroy(List* list)
{
    free(list->list_memory);
    free(list);
}

char* u8_list_get_string(U8List* list)
{
    u8_list_append(list, '\0');
    return (char*)list->list_memory;
}

void int_list_print(IntList* list)
{
    for (int i = 0; i < list->list_size; i++)
    {
        if (list->list_index > i)
            printf("%d: %d", i, list->list_memory[i]);
        else
            break;
        printf("\n");
    }

    printf("Current internal size: %lu\n", (unsigned long)list->list_size);
}
