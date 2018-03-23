CC=gcc
CCFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector\
 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

AS=nasm
ASFLAGS=-f elf32

LD=ld
LDFLAGS=-T link.ld -melf_i386

BUILD_DIR=build
SOURCE_DIR=src

CSRC_FILES=$(shell find $(SOURCE_DIR) -name *.c -print)
ASM_FILES=$(shell find $(SOURCE_DIR) -name *.s -print)
HEADER_FILES=$(shell find $(SOURCE_DIR) -name *.h -print)

OBJ_FILES=$(patsubst $(SOURCE_DIR)%,$(BUILD_DIR)%, $(CSRC_FILES:c=o) $(ASM_FILES:s=o))

all: $(BUILD_DIRS) $(BUILD_DIR)/os.iso

$(BUILD_DIR):
	mkdir -p $@

run: $(BUILD_DIR) $(BUILD_DIR)/os.iso
	bochs -f bochs/bochsrc.txt -q -rc bochs/continue

$(BUILD_DIR)/os.iso: $(BUILD_DIR)/kernel.elf iso/boot/grub/grub.cfg
	cp $(BUILD_DIR)/kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o $@ iso

$(BUILD_DIR)/kernel.elf: $(OBJ_FILES)
	echo $(OBJ_FILES)
	$(LD) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.s $(HEADER_FILES)
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -o $@ $<

clean:
	rm -rf build/

.PHONY: all run clean