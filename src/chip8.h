// include guards to prevent multiple inclusions of the header file
#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define CHIP8_DISPLAY_HEIGHT 32
#define CHIP8_DISPLAY_WIDTH 64
#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_REGISTER_COUNT 16
#define CHIP8_STACK_SIZE 16
#define CHIP8_KEY_COUNT 16
#define CHIP8_START_OF_PROGRAM 0x200
#define CHIP8_FONT_START 0x50

typedef struct {
    uint8_t memory[CHIP8_MEMORY_SIZE]; // 4K memory
    uint8_t V[CHIP8_REGISTER_COUNT]; // 16 registers (V0 to VF), (VF is the flag register)
    uint16_t I; // Index register (only uses lower 12 bits)
    uint16_t pc; // Program counter (only uses lower 12 bits)
    uint16_t stack[CHIP8_STACK_SIZE]; // Stack for subroutine calls
    uint8_t sp; // Stack pointer (index of top entry)
    uint8_t delay_timer; // Delay timer
    uint8_t sound_timer; // Sound timer
    uint8_t display[CHIP8_DISPLAY_HEIGHT][CHIP8_DISPLAY_WIDTH]; // Display buffer [y][x]
    uint16_t keys; // Key states (bitmask for 16 keys)
} Chip8;

void chip8_reset(Chip8* chip8);

#endif // CHIP8_H
