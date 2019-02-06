CC=g++
CFLAGS=-g -std=c++11 -Wall -Wextra
DEPS=parser.hpp tables.hpp
OBJ=main.o parser.o tables.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

assembler: $(OBJ)
	$(CC)  -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o assembler
