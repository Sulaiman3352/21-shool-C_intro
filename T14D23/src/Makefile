CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
BUILD=../build/

all: state_sort state_search

state_sort: state_sort.c
	$(CC) $(CFLAGS) state_sort.c  -o $(BUILD)Quest_1

state_search: state_search.c
	$(CC) $(CFLAGS) state_search.c -o $(BUILD)Quest_2

clean:
	rm -rf $(BUILD)Quest*

rebuild: clean all
