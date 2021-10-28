#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct IntStack IntStack;

IntStack* int_stack_create(size_t size);

int int_stack_push(IntStack* stack, int num);

int int_stack_pop(IntStack* stack);

int int_stack_dupe(IntStack* stack);

void int_stack_swap(IntStack* stack);

int int_stack_copy(IntStack* stack, size_t index);

int int_stack_push_string(IntStack* stack, const char* string);

void int_stack_destoy(IntStack* stack);

void int_stack_print(IntStack* stack);


typedef struct I64Stack I64Stack;

I64Stack* i64_stack_create(size_t size);

int64_t i64_stack_push(I64Stack* stack, int64_t num);

int64_t i64_stack_pop(I64Stack* stack);

int64_t i64_stack_dupe(I64Stack* stack);

void i64_stack_swap(I64Stack* stack);

int64_t i64_stack_copy(I64Stack* stack, size_t index);

int64_t i64_stack_push_string(I64Stack* stack, const char* string);

void i64_stack_destoy(I64Stack* stack);
