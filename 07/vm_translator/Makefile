CC=g++
CFLAGS=-g -std=c++14
DEPS=parser.hpp writer.hpp
OBJ=main.o parser.o writer.o


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

vm_translator: $(OBJ)
	$(CC)  -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o *.asm vm_translator
