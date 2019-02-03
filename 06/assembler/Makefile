CC=g++
CFLAGS=-g -std=c++11
DEPS=parser.hpp tables.hpp
OBJ=main.o parser.o tables.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

assembler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o assembler
