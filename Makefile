.PHONY: clean all

FLAGS = -std=c11 -Wall -Wextra -g -fsanitize=address,undefined
OUTPUT = chip8

all: chip8


$(OUTPUT): chip8.o main.o
	gcc $(FLAGS) chip8.o main.o -o $(OUTPUT)

chip8.o: src/chip8.c src/chip8.h
	gcc $(FLAGS) -c src/chip8.c -o chip8.o

main.o: src/main.c src/chip8.h
	gcc $(FLAGS) -c src/main.c -o main.o


clean:
	rm -f $(OUTPUT) chip8.o main.o
