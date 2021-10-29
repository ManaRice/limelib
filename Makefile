CC=gcc
CFLAGS=-Wall -Werror -Wpedantic -O3

SRC=src/
INC=include/
OBJ=obj/
UTILS_PATH=../../utils/

all: limelib.so test.c obj
	$(CC) $(CFLAGS) -s test.c limelib.so -o test


limelib.so: $(OBJ)stack.o $(OBJ)list.o $(OBJ)linkedlist.o $(OBJ)hashmap.o
	$(CC) $(CFLAGS) -fPIC -s -shared $^ -o $@
	$(CC) $(CFLAGS) -fPIC -s -shared $^ -o $(UTILS_PATH)$@


$(OBJ)stack.o: $(SRC)stack.c $(INC)stack.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(OBJ)list.o: $(SRC)list.c $(INC)list.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(OBJ)linkedlist.o: $(SRC)linkedlist.c $(INC)linkedlist.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(OBJ)hashmap.o: $(SRC)hashmap.c $(INC)hashmap.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@


obj:
	mkdir obj

clean:
	rm -r obj/*
	rm limelib.so
	rm test.exe

run:
	@./test.exe
