BITS 32

	section .multiboot
		ALIGN 4
		DD 0x1BADB002
		DD 0x00000000
		DD -(0x1BADB002 + 0x00000000)
	
	global start
	extern kmain

	start:
		CLI
		MOV esp, stack_space
		CALL kmain
		HLT
	HaltKernel:
		CLI
		HLT
		JMP HaltKernel

	section .bss
	RESB 4096
	stack_space: