NAME		= kernel
ISO			= kernel.iso

CC			= gcc
AS			= nasm
LD			= ld

CFLAGS		= -m32 -fno-builtin -fno-exceptions -fno-stack-protector \
			  -nostdlib -nodefaultlibs -Iinclude
ASFLAGS		= -f elf32
LDFLAGS		= -m elf_i386 -T linker.ld

SRC_DIR		= src
GDT_DIR		= $(SRC_DIR)/gdt
ISO_DIR		= axburin-

C_SRC		= $(SRC_DIR)/kernel.c \
			  $(SRC_DIR)/vga.c \
			  $(SRC_DIR)/cursor.c \
			  $(SRC_DIR)/printk.c \
			  $(SRC_DIR)/ft_put.c \
			  $(SRC_DIR)/utils.c \
			  $(GDT_DIR)/gdt.c

ASM_SRC		= $(SRC_DIR)/boot.s \
			  $(GDT_DIR)/gdts.s

OBJS		= $(C_SRC:.c=.o) $(ASM_SRC:.s=.o)

all: $(ISO)

$(ISO): $(NAME)
	@mv $(NAME) $(ISO_DIR)/boot/
	@grub-mkrescue -o $@ $(ISO_DIR) --compress=xz -d /usr/lib/grub/i386-pc
	@echo "ISO: $$(du -h $@ | cut -f1)"

$(NAME): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(ISO)

re: fclean all

run:
	qemu-system-i386 -cdrom $(ISO)

.PHONY: all clean fclean re run