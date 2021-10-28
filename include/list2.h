#pragma once
//#include <stdlib.h>

#define Char char
#define Short short
#define Int int
#define Long long
#define LongLong long long

#define get_type(type)type

#define make_list(type)                                             \
typedef struct type##List type##List;                               \
                                                                    \
type##List* type##_list_create(size_t init_size);                   \
                                                                    \
int type##list_append(type##List* list, type num);                  \
                                                                    \
Optional##type type##list_get(type##List* list, size_t index);      \
                                                                    \
void type##list_destroy(type##List* list);                          \
                                                                    \
void type##list_print(type##List* list);

make_list(Int)
