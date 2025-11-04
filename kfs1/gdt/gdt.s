global gdt_flush

gdt_flush:
    MOV eax, [esp+4]
    LGDT [eax];

    MOV eax, 0x10
    MOV cs, ax
    MOV ss, ax
    MOV ds, ax
    MOV es, ax
    JMP 0x08:.flush

.flush
    RET