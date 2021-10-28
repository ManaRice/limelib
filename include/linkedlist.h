#pragma once

typedef struct IntLinkedlist IntLinkedlist;

IntLinkedlist* int_linkedlist_create();

size_t int_linkedlist_size(IntLinkedlist* list);

int int_linkedlist_append(IntLinkedlist* list, int num);

OptionalInt int_linkedlist_get(IntLinkedlist* list, size_t index);

int int_linkedlist_delete(IntLinkedlist* list, size_t index);

void int_linkedlist_destroy(IntLinkedlist* list);

void int_linkedlist_print(IntLinkedlist* list);
