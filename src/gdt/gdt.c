#include "kernel.h"

extern void gdt_flush(uint32_t);
extern void tss_flush();

struct gdt_entry_struct *gdt_entries = (struct gdt_entry_struct*)0x00000800;
struct gdt_ptr_struct gdt_ptr;
struct tss_entry_struct tss_entry;

void initGdt(){
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 6) - 1;
    gdt_ptr.base = 0x00000800;

    setGdtGate(0,0,0,0,0);
    setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code k
    setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data k
    setGdtGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // code user  
    setGdtGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // data user
    writeTSS(5, 0x10, 0x0);

    gdt_flush((uint32_t)&gdt_ptr);
    tss_flush();
}

void	writeTSS(uint32_t num, uint32_t ss0, uint32_t esp0) {
    uint32_t    base = (uint32_t)&tss_entry;
    uint32_t    limit = base + sizeof(tss_entry);

    setGdtGate(num, base, limit, 0xE9, 0x00);
    ft_memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;
    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
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