#pragma once
#include "../stdint.h"

struct gdt_entry_struct{
    uint16_t limit;
    uint16_t lowBase;
    uint8_t middleBase;
    uint8_t acces;
    uint8_t flags;
    uint8_t highBase;
}__attribute__((packed));

struct gdt_ptr_struct{
    uint16_t limit;
    unsigned int base;
}__attribute__((packed));

void initGdt();
void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t acces, uint8_t flags);