#include "vga.h"
#include "stdint.h"

/* fonctions d'accès aux ports x86 (outb) - inline assembly */
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void move_cursor_hardware(uint16_t x, uint16_t y) {
    if (x >= width) x = width - 1;
    if (y >= height) y = height - 1;

    uint16_t pos = (y - 1) * width + x;

    /* Registre 0x0E = high byte, 0x0F = low byte */
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
}

void set_cursor_pos(uint16_t x, uint16_t y) {
    uint16_t column = x;
    uint16_t line = y;
    move_cursor_hardware(x, y);
}