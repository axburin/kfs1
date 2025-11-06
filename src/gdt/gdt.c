#include "kernel.h"

extern void gdt_flush(uint32_t);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

void initGdt(){
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    setGdtGate(0,0,0,0,0);
    setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code k
    setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data k
    setGdtGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // code user  
    setGdtGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // data user

    gdt_flush((uint32_t)&gdt_ptr);

}

void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t acces, uint8_t gran){
    
    gdt_entries[num].lowBase = (base & 0xFFFF);
    
    gdt_entries[num].middleBase = (base >> 16) & 0xFF;
    gdt_entries[num].highBase = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].acces = acces;
}