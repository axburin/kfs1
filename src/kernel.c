#include "kernel.h"

void kmain(void);

void test_kdump_string(void)
{
    char *test_string = "Hello, World! This is a test string for kdump.";
    kdump((uint32_t)test_string, 48);
}

void test_kdump_stack(void)
{
    uint32_t esp, ebp;
    
    __asm__ volatile(
        "mov %%esp, %0\n"
        "mov %%ebp, %1"
        : "=r"(esp), "=r"(ebp)
    );
    
    volatile uint32_t test1 = 0xAAAAAAAA;
    volatile uint32_t test2 = 0xBBBBBBBB;
    
    // Dump 128 bytes du stack
    kdump(esp, 128);
}

void kmain(void){
    initGdt();
    Reset();
    printk("GDT is done !\n");
    
    printk("=== In kmain ===\n");
    test_kdump_stack();
    test_kdump_string();
}