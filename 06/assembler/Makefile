CC=g++
CFLAGS=-g -std=c++14
DEPS=parser.hpp tables.hpp
OBJ=main.o parser.o tables.o


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

assembler: $(OBJ)
	$(CC)  -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o assembler
