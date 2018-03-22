CC=gcc
CCFLAGS=

ASM=nasm
ASMFLAGS=-f elf32

LD=ld
LDFLAGS=-T link.ld -melf_i386

BUILD_DIR=build
SOURCE_DIR=src

CSRC_FILES=$(wildcard $(SOURCE_DIR)/*.c)
ASM_FILES=$(wildcard $(SOURCE_DIR)/*.s)

OBJ_FILES=$(addprefix $(BUILD_DIR)/, $(notdir $(CSRC_FILES:c=o) $(ASM_FILES:=.o)))


all: $(BUILD_DIR)/os.iso

$(BUILD_DIR)/os.iso: $(BUILD_DIR)/kernel.elf
	grub-mkrescue -o $^ iso

$(BUILD_DIR)/kernel.elf: $(OBJ_FILES)
	$(LD) $(LDFLAGS) $^ -o $@


$(BUILD_DIR)/%.s.o: %.s
	$(ASM) $(ASMFLAGS) -o $(BUILD_DIR)/$@ $<

$(BUILD_DIR)/%.o: %.c
	echo "C not implemented"

.PHONY: all