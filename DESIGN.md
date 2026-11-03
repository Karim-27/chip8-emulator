# Design Notes

This document records the design decisions behind this CHIP-8 emulator and the reasoning for each
one. The README explains what the project is and how to run it; this file explains *why* the code
is structured the way it is. Each decision is written down when it's made.

## Machine state

How each part of the CHIP-8 machine is represented in C. Fixed-width unsigned types from
`<stdint.h>` are used for all machine state, so values are exactly as wide as the hardware's and
wrap around in a well-defined way.

| State                       | Bits                       | Type                                   |
|-----------------------------|----------------------------|----------------------------------------|
| Memory (4 KB)               | 8 each, 4096 locations     | array of uint8_t                       |
| V registers (V0–VF)         | 8 each, 16 registers       | array of uint8_t                       |
| I (index register)          | 12                         | uint16_t                               |
| PC (program counter)        | 12                         | uint16_t                               |
| Stack                       | 12 each, 16 entries        | array of uint16_t                      |
| SP (stack pointer)          | 8                          | uint8_t                                |
| Delay timer                 | 8                          | uint8_t                                |
| Sound timer                 | 8                          | uint8_t                                |
| Display (64×32)             | 1 byte per pixel, 2048     | 2D array of uint8_t (32 rows × 64 cols) |
| Keypad (16 keys)            | 1 bit per key, 16          | uint16_t (bitmask)                     |


## Decisions

### 1. Keypad as a 16-bit bitmask

- **Decision:** Store the keypad state in a single `uint16_t`, one bit per key (bit N = key N).
- **Alternatives considered:** An array of 16 one-byte values (`bool` or `uint8_t`), one per key.
- **Reasoning:** Compact, mirrors how hardware often reports button state, and gives practice with
  setting, clearing, and testing individual bits.
- **Trade-offs:** Every key check needs a bit operation instead of a plain array lookup, so it's
  slightly less readable. Performance is not a factor either way with only 16 keys.

### 2. Display as a 2D array, one byte per pixel

- **Decision:** Store the display as a 2D array of `uint8_t`, 32 rows × 64 columns, one byte per
  pixel.
- **Alternatives considered:** A 1D array of 2048 bytes; packed bits (8 pixels per byte, 256 bytes).
- **Reasoning:** Every display operation (DXYN draw, 00E0 clear, rendering) works pixel by pixel,
  so one byte per pixel keeps each access a simple read or write. A 2D array makes looking up the
  pixel at (x, y) intuitive. The memory cost (2 KB) doesn't matter on a modern machine, and DXYN
  still provides bit-manipulation practice when unpacking sprite bytes.
- **Trade-offs:** Uses 8× more memory than packed bits. Index order must be correct: the first index
  selects the row. C stores the array as one contiguous block, row after row.
