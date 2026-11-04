#include <stdio.h>
#include <string.h>
#include "chip8.h"

static const uint8_t font[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void chip8_reset(Chip8* chip8) {
    // Resets the chip8 system to its initial state
    // input is a pointer to chip8

    memset(chip8, 0, sizeof(*chip8)); // reset chip8
    chip8->pc = CHIP8_START_OF_PROGRAM; // set PC to start of program
    memcpy(&chip8->memory[CHIP8_FONT_START], font, sizeof(font)); // copy font into memory
}

// Function to load a program into memory
int chip8_load_rom(Chip8* chip8,const char* file_path) {
    // open the file in binary mode
    FILE *f = fopen(file_path, "rb");
    if (f == NULL) {
        return -1; // file failed to open
    }

    // find the file size
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    if (fsize <= 0) {
        fclose(f);
        return -1;
    }
    fseek(f, 0, SEEK_SET);

    // check the file fits in memory (from 0x200 to the end)
    // if not close the file and return an error
    if (fsize > CHIP8_MAX_ROM_SIZE) {
        fclose(f);
        return -1;
    }

    // read the bytes into memory
    size_t fcheck = fread(&chip8->memory[CHIP8_START_OF_PROGRAM], 1, fsize, f);
    if (fcheck != (size_t) fsize) {
        fclose(f);
        return -1;
    }

    // close the file
    fclose(f);
    return 0;
}

// Runs an instruciton (fetch-decode-execute cycle)


// Function to update timers (delay and sound timers)