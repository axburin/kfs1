all: clean kernel boot image

clean:
	# Supprimer tous les fichiers .o générés lors de la compilation
	rm -rf *.o

kernel:
	gcc -m32 -fno-stack-protector -fno-exceptions -fno-rtti -nostdlib -nodefaultlibs -fno-builtin -c kernel.c -o kernel.o
	gcc -m32 -fno-stack-protector -fno-exceptions -fno-rtti -nostdlib -nodefaultlibs -fno-builtin -c vga.c -o vga.o
	gcc -m32 -fno-stack-protector -fno-exceptions -fno-rtti -nostdlib -nodefaultlibs -fno-builtin -c gdt/gdt.c -o gdt.o

boot:
	nasm -f elf32 boot.s -o boot.o
	nasm -f elf32 gdt/gdt.s -o gdts.o

run:
	qemu-system-i386 kernel.iso

image:
	ld -m elf_i386 -T linker.ld -o kernel boot.o kernel.o vga.o gdt.o gdts.o
	mv kernel axburin-/boot/kernel
	grub-mkrescue -o kernel.iso axburin-/
	rm *.o

