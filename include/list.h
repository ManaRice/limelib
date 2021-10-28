#pragma once
#include <stdlib.h>

typedef struct IntList IntList;

IntList* int_list_create(size_t init_size);

int int_list_append(IntList* list, int num);

OptionalInt int_list_get(IntList* list, size_t index);

size_t int_list_size(IntList* list);

void int_list_destroy(IntList* list);

void int_list_print(IntList* list);
typedef struct U8List U8List;

U8List* u8_list_create(size_t init_size);

int u8_list_append(U8List* list, uint8_t num);

OptionalU8 u8_list_get(U8List* list, size_t index);

size_t u8_list_size(U8List* list);

void u8_list_destroy(U8List* list);

char* u8_list_get_string(U8List* list);

typedef struct List List;

List* list_create(size_t size, size_t element_size);

int list_append(List* list, void* element);

OptionalPtr list_get(List* list, size_t index);

size_t list_size(List* list);

void list_destroy(List* list);
