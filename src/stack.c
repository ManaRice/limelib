#include "../limelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

struct IntStack
{
    int* stack_memory;
    int* stack_pointer;
    size_t stack_size;
};

IntStack* int_stack_create(size_t size)
{
    IntStack* stack;
    stack = malloc(sizeof(IntStack));
    if (stack== NULL)
    {
        fprintf(stderr, "Stack init failed\n");
        return NULL;
    }
    stack->stack_size = size;
    stack->stack_memory = calloc(size, sizeof(int));
    if (stack->stack_memory == NULL)
    {
        fprintf(stderr, "Stack init failed\n");
        return NULL;
    }
    stack->stack_pointer = stack->stack_memory;
    return stack;
}

int int_stack_push(IntStack* stack, int num)
{
    if (stack->stack_pointer - stack->stack_memory >= stack->stack_size)
    {
        fprintf(stderr, "Stack is full\n");
        return -1;
    }
    *stack->stack_pointer = num;
    stack->stack_pointer++;
    return 0;
}

int int_stack_pop(IntStack* stack)
{
    if (stack->stack_pointer == stack->stack_memory)
    {
        fprintf(stderr, "Dont pop an empty stack");
        return -1;
    }
    stack->stack_pointer--;
    return *stack->stack_pointer;
}

int int_stack_dupe(IntStack* stack)
{
    if (stack->stack_pointer - stack->stack_memory >= stack->stack_size)
    {
        fprintf(stderr, "Stack is full\n");
        return -1;
    }
    *stack->stack_pointer = *(stack->stack_pointer-1);
    stack->stack_pointer++;
    return 0;
}

void int_stack_swap(IntStack* stack)
{
    int temp = *(stack->stack_pointer-1);
    *(stack->stack_pointer-1) = *(stack->stack_pointer-2);
    *(stack->stack_pointer-2) = temp;
}

int int_stack_copy(IntStack* stack, size_t index)
{
    if (stack->stack_pointer - stack->stack_memory >= stack->stack_size)
    {
        fprintf(stderr, "Stack is full\n");
        return -1;
    }

    if (stack->stack_pointer - (index + 1) < stack->stack_memory)
    {
        fprintf(stderr, "Copy below 0\n");
        return -1;
    }
    *stack->stack_pointer = *(stack->stack_pointer - (index + 1));
    stack->stack_pointer++;

    return 0;
}

int int_stack_push_string(IntStack* stack, const char* string)
{
    size_t length = strlen(string);
    int i = length;
    while (i <= length)
    {
        if (int_stack_push(stack, string[i]))
        {
            int_stack_print(stack);
            return 1;
        }
        i--;
    }
    return 0;
}

void int_stack_destoy(IntStack* stack)
{
    free(stack->stack_memory);
    free(stack);
}

void int_stack_print(IntStack* stack)
{
    if (stack->stack_pointer - stack->stack_memory >= stack->stack_size)
    {
        printf("Stack pointer is above stack");
    }
    printf("\n");
    for (int i = stack->stack_size-1; i >= 0; i--)
    {
        printf("%d: %c", i, stack->stack_memory[i]);

        if (stack->stack_pointer - stack->stack_memory == i)
            printf("\t<- stack pointer");
        printf("\n");
    }
}


// I64Stack

struct I64Stack
{
    int64_t* stack_memory;
    int64_t* stack_pointer;
    size_t stack_size;
};

I64Stack* i64_stack_create(size_t size)
{
    I64Stack* stack;
    stack = malloc(sizeof(I64Stack));
    if (stack== NULL)
    {
        fprintf(stderr, "Stack init failed\n");
        return NULL;
    }
    stack->stack_size = size;
    stack->stack_memory = calloc(size, sizeof(int64_t));
    if (stack->stack_memory == NULL)
    {
        fprintf(stderr, "Stack init failed\n");
        return NULL;
    }
    stack->stack_pointer = stack->stack_memory;
    return stack;
}

int64_t i64_stack_push(I64Stack* stack, int64_t num)
{
    if (stack->stack_pointer - stack->stack_memory >= stack->stack_size)
    {
        fprintf(stderr, "Stack is full\n");
        return -1;
    }
    *stack->stack_pointer = num;
    stack->stack_pointer++;
    return 0;
}

int64_t i64_stack_pop(I64Stack* stack)
{
    if (stack->stack_pointer == stack->stack_memory)
    {
        fprintf(stderr, "Dont pop an empty stack");
        return -1;
    }
    stack->stack_pointer--;
    return *stack->stack_pointer;
}

int64_t i64_stack_dupe(I64Stack* stack)
{
    if (stack->stack_pointer - stack->stack_memory >= stack->stack_size)
    {
        fprintf(stderr, "Stack is full\n");
        return -1;
    }
    *stack->stack_pointer = *(stack->stack_pointer-1);
    stack->stack_pointer++;
    return 0;
}

void i64_stack_swap(I64Stack* stack)
{
    int64_t temp = *(stack->stack_pointer-1);
    *(stack->stack_pointer-1) = *(stack->stack_pointer-2);
    *(stack->stack_pointer-2) = temp;
}

int64_t i64_stack_copy(I64Stack* stack, size_t index)
{
    if (stack->stack_pointer - stack->stack_memory >= stack->stack_size)
    {
        fprintf(stderr, "Stack is full\n");
        return -1;
    }

    if (stack->stack_pointer - (index + 1) < stack->stack_memory)
    {
        fprintf(stderr, "Copy below 0\n");
        return -1;
    }
    *stack->stack_pointer = *(stack->stack_pointer - (index + 1));
    stack->stack_pointer++;

    return 0;
}

int64_t i64_stack_push_string(I64Stack* stack, const char* string)
{
    size_t length = strlen(string);
    int i = length;
    while (i <= length)
    {
        if (i64_stack_push(stack, string[i]))
            return 1;

        i--;
    }
    return 0;
}

void i64_stack_destoy(I64Stack* stack)
{
    free(stack->stack_memory);
    free(stack);
}
