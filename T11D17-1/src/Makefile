CC = gcc
CFLAGS = -Wall -Werror -Wextra

Quest_1 = ../build/Quest_1
Quest_2 = ../build/Quest_2
Quest_3 = ../build/Quest_3


objFile = door_struct.o dmanager_module.o main.o -o

.PHONY: all clean rebuild

all: door_struct list_test stack_test

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

door_struct: dmanager_module.c
	$(CC) $(CFLAGS) dmanager_module.c -o $(Quest_1)

list_test: list_test.c
	$(CC) $(CFLAGS) list_test.c list.c -o $(Quest_2)

stack_test: stack.c stack_test.c
	$(CC) $(CFLAGS) stack.c stack_test.c -o $(Quest_3)

clean:
	rm -f *.o $(Quest_1) $(Quest_2) $(Quest_3)

rebuild: clean all
