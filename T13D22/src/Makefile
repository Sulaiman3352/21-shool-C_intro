CC = gcc
CFLAGS = -Wall -Werror -Wextra

Quest_1 = ../build/cipher
Quest_5 = ../build/logging_cipher

objFile = cipher.o logger.o -o

all: cipher logging_cipher

main.o: main.c
	$(CC) $(CFLAGS) -c cipher.c -o main.o

cipher: cipher.c
	@mkdir -p ../build
	$(CC) $(CFLAGS) logger.c cipher.c -o $(Quest_1) -lssl -lcrypto

logging_cipher: logger.c
	@mkdir -p ../build
	$(CC) $(CFLAGS) logger.c cipher.c -o $(Quest_5) -lssl -lcrypto

# Compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(Quest_1) $(Quest_5)

rebuild: clean all
.PHONY: all clean rebuild
