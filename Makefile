NAME		= kernel
ISO			= kernel.iso

CC			= gcc
AS			= nasm
LD			= ld

CFLAGS		= -m32 -fno-builtin -fno-exceptions -fno-stack-protector \
			  -nostdlib -nodefaultlibs -Iinclude -O0
ASFLAGS		= -f elf32
LDFLAGS		= -m elf_i386 -T linker.ld

SRC_DIR		= src
GDT_DIR		= $(SRC_DIR)/gdt
ISO_DIR		= axburin-

ASM_SRC		= $(SRC_DIR)/boot.s \
			  $(GDT_DIR)/gdts.s

C_SRC		= $(SRC_DIR)/kernel.c \
			  $(SRC_DIR)/vga.c \
			  $(SRC_DIR)/cursor.c \
			  $(SRC_DIR)/printk.c \
			  $(SRC_DIR)/ft_put.c \
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/stack_dump.c \
			  $(GDT_DIR)/gdt.c

OBJS		= $(ASM_SRC:.s=.o) $(C_SRC:.c=.o)

all: $(ISO)

$(ISO): $(NAME)
	@mv $(NAME) $(ISO_DIR)/boot/
	@grub-mkrescue -o $@ $(ISO_DIR) --compress=xz -d /usr/lib/grub/i386-pc
	@echo "ISO: $$(du -h $@ | cut -f1)"

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(ISO)

re: fclean all

run:
	qemu-system-i386 -cdrom $(ISO)

.PHONY: all clean fclean re run