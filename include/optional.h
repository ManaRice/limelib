#pragma once
#include <stdbool.h>
#include <stdint.h>

/*
#define Char char
#define Short short
#define Int int
#define Long long
#define LongLong long long

#define make_opt(type)  \
typedef struct          \
{                       \
    type value;         \
    bool has_value;     \
}Optional##type

make_opt(Char);
make_opt(Short);
make_opt(Int);
make_opt(Long);
make_opt(LongLong);

#undef Char
#undef Short
#undef Int
#undef Long
#undef LongLong
#undef make_opt

*/

typedef struct
{
    uint8_t value;
    bool has_value;
} OptionalU8;

typedef struct
{
    int8_t value;
    bool has_value;
} OptionalI8;

typedef struct
{
    uint16_t value;
    bool has_value;
} OptionalU16;

typedef struct
{
    int16_t value;
    bool has_value;
} OptionalI16;

typedef struct
{
    uint32_t value;
    bool has_value;
} OptionalU32;

typedef struct
{
    int32_t value;
    bool has_value;
} OptionalI32;

typedef OptionalI32 OptionalInt;

typedef struct
{
    uint64_t value;
    bool has_value;
} OptionalU64;

typedef struct
{
    uint8_t value;
    bool has_value;
} OptionalI64;

typedef struct
{
    union
    {
        void* value;
        int32_t error;
    };
    bool has_value;
} OptionalPtr;
