#include <stdio.h>
#include "chip8.h"

int main(void) {
    Chip8 chip8_test;
    chip8_reset(&chip8_test);
    int value = chip8_load_rom(&chip8_test, "roms/ibm.ch8");
    printf("%d \n", value);

    // print the program
    for (int i = 0x200; i < 0x290; i++) {
        printf("%02X ", chip8_test.memory[i]);
        if (i % 16 == 15) {
            printf("\n");
        }
    }


    return 0;
}
