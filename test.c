#include "limelib.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct test_struct
{
    int32_t val;
    uint8_t c;
    char* s;
};

void print_stack(I64Stack* stack)
{
    char c;
    while ((c = i64_stack_pop(stack)) != 0)
        printf("%c", c);
}

void test_stack()
{
    printf("TESTING STACK...\n");
    printf("----------------\n\n\n");

    const char* string = "Hejsan alla glada! Vad trevlig att se er!\n";
    const size_t stack_size = strlen(string) + 2;
    I64Stack* stack = i64_stack_create(stack_size);

    i64_stack_push_string(stack, string);

    i64_stack_copy(stack, 3);

    print_stack(stack);

    i64_stack_destoy(stack);
}

void test_list()
{
    printf("\nTESTING LIST...\n");
    printf("----------------\n\n\n");
    IntList* list = int_list_create(10000);
    int count = 0;
    for (int i = 0; i < 1000000; i++)
        if (int_list_append(list, i))
            count++;

    OptionalInt opt = int_list_get(list, 99092);
    if (opt.has_value)
        printf("Opt has value: %d\n", opt.value);
    else
        printf("Opt dosen't have a value\n");

    printf("Reallocs: %d\n", count);
    printf("\n");

    int_list_destroy(list);

    IntList* list2 = int_list_create(2);
    OptionalInt opt2 = int_list_get(list2, 0);
    if (opt2.has_value)
        printf("Opt has value: %d\n", opt.value);
    else
        printf("Opt dosen't have a value\n");

    int_list_destroy(list);

    U8List* u8list = u8_list_create(6);
    u8_list_append(u8list, 'H');
    u8_list_append(u8list, 'e');
    u8_list_append(u8list, 'j');
    u8_list_append(u8list, '!');
    printf("U8List as string: %s\n", u8_list_get_string(u8list));

    List* generic_list = list_create(3, sizeof(struct test_struct));

    struct test_struct s1 = {.val = 54, .c = 'G', .s="test1"};
    struct test_struct s2 = {.val = 127, .c = 'O', .s="test2"};
    struct test_struct s3 = {.val = 47, .c = 'O', .s="test3"};
    struct test_struct s4 = {.val = 1, .c = 'D', .s="test4"};

    int a = list_append(generic_list, &s1);
    int b = list_append(generic_list, &s2);
    int c = list_append(generic_list, &s3);
    int d = list_append(generic_list, &s4);

    printf("%d, %d, %d, %d\n", a, b, c, d);

    OptionalPtr optptr;
    optptr = list_get(generic_list, 3);
    struct test_struct result = *(struct test_struct*)optptr.value;
    printf("%s\n", result.s);
    printf("TESTING DONE LIST\n");
}

void test_linkedlist()
{

    printf("\nTESTING LINKEDLIST ...\n");
    printf("------------------------\n\n\n");

    IntLinkedlist* list = int_linkedlist_create();
    assert(list != NULL);

    int_linkedlist_append(list, 0);
    int_linkedlist_append(list, 1);
    int_linkedlist_append(list, 2);
    int_linkedlist_append(list, 3);

    OptionalInt opt = int_linkedlist_get(list, 2);

    assert(opt.has_value);
    assert(opt.value == 2);

    int_linkedlist_delete(list, 2);

    OptionalInt opt2 = int_linkedlist_get(list, 2);

    assert(opt2.has_value);
    assert(opt2.value == 3);
    assert(int_linkedlist_size(list) == 3);

    int_linkedlist_print(list);

    int_linkedlist_destroy(list);

    printf("TESTING DONE LINKEDLIST\n");
}

void test_hashmap()
{
    IntHashMap* hashmap = int_hashmap_create();
    int_hashmap_add(hashmap, "josefin", 39);

    assert(int_hashmap_add(hashmap, "josefin", 34) == false);
    int_hashmap_add(hashmap, "Josefin", 15);
    int_hashmap_add(hashmap, "daniel", 67);

    OptionalInt opt;
    opt = int_hashmap_get(hashmap, "josefin");
    assert(opt.has_value && opt.value == 39);

    opt = int_hashmap_get(hashmap, "Josefin");
    assert(opt.has_value && opt.value == 15);

    opt = int_hashmap_get(hashmap, "daniel");
    assert(opt.has_value && opt.value == 67);

    struct person
    {
        int32_t number;
    };

    struct person josefin = {.number = 39};
    struct person josefin2 = {.number = 34};
    struct person Josefin = {.number = 15};
    struct person daniel = {.number = 67};

    PtrHashMap* ptrhashmap = ptr_hashmap_create();
    ptr_hashmap_add(ptrhashmap, "josefin", &josefin);

    assert(ptr_hashmap_add(ptrhashmap, "josefin", &josefin2) == false);
    ptr_hashmap_add(ptrhashmap, "Josefin", &Josefin);
    ptr_hashmap_add(ptrhashmap, "daniel", &daniel);

    OptionalPtr opt2;
    opt2 = ptr_hashmap_get(ptrhashmap, "josefin");
    assert(opt2.has_value && ((struct person*)opt2.value)->number == 39);

    opt2 = ptr_hashmap_get(ptrhashmap, "Josefin");
    assert(opt2.has_value && ((struct person*)opt2.value)->number == 15);

    opt2 = ptr_hashmap_get(ptrhashmap, "daniel");
    assert(opt2.has_value && ((struct person*)opt2.value)->number == 67);

}

int main()
{
    test_stack();
    test_list();
    test_linkedlist();
    test_hashmap();
    printf("ALL TESTING DONE\n");
    return 0;
}
