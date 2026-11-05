FLAGS=-Wall -Werror -Wextra

all: main

main: main.o stack.o graph.o
	gcc $(FLAGS) graph.c main.c stack.c -o ../build/graph -lm

main.o: main.c
	@mkdir -p ../build
	gcc $(FLAGS) -c main.c

stack.o: stack.c stack.h
	gcc $(FLAGS) -c stack.c

graph.o: graph.c graph.h
	gcc $(FLAGS) -c graph.c

clean:
	rm -rf *.o ../build/graph

rebuild: clean all

.PHONY: clean all rebuild