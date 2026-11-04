#include <stdio.h>
#include "chip8.h"

int main(void) {
    Chip8 chip8_test;
    chip8_reset(&chip8_test);
    printf("PC: %04X\n", chip8_test.pc); // print PC

    // print memory 0x04B-0x0A4
    for (int i = 0x000; i < 0x200; i++) {
        printf("%02X ", chip8_test.memory[i]);
        if (i % 16 == 15) {
            printf("\n");
        }
    }


    return 0;
}
