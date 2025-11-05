#include "gdt.h"

extern void gdt_flush(addr_t);

struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

void initGdt(){
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 5) - 1;
    gdt_ptr.base = &gdt_entries;

    setGdtGate(0,0,0,0,0);
    setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code k
    setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data k
    setGdtGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // code
    setGdtGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user

    gdt_flush(&gdt_ptr);

}

void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t acces, uint8_t gran){
    
    gdt_entries[num].lowBase = (base & 0xFFFF);
    
    gdt_entries[num].middleBase = (base >> 16) & 0xFF;
    gdt_entries[num].highBase = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0xF;
    gdt_entries[num].flags = (gran & 0xcF);

    gdt_entries[num].acces = acces;
}