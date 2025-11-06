#include "kernel.h"

void kmain(void);

void kmain(void){
    initGdt();
    Reset();
    print("Hello, alban!\n");
    printk("Hello, a     !\r\n");
    printk("1\t12\t123\t1234\t\n");
    print("probleme\n");
}