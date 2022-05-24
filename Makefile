# Set Compiler flags
SFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -nostdlib -nostartfiles $(DIRECTIVES)
CFLAGS = -O2 -Wall -Wextra -g
CFLAGS += -Wno-int-to-pointer-cast -Wno-unused-parameter -Wno-pointer-to-int-cast
LDFLAGS = -ffreestanding -O2 -nostdlib

# Set Cross-Compiler Toolchain
ARMGNU = aarch64-none-elf

# Set kernel image name
IMG_NAME = kernel8


# Set Raspi Model, if not set
RASPI_MODEL = 4

ifeq ($(RASPI_MODEL), 3)
	MODEL = MODEL_3
else ifeq ($(RASPI_MODEL), 4)
	MODEL = MODEL_4
endif

# Set flags and variables dependent on the Raspi Model
AARCH = AARCH_64
ARCH_DIR = arch/armv8-a
SFLAGS += -mgeneral-regs-only
CPU = cortex-a53
DIRECTIVES = -D $(MODEL) -D $(AARCH)

# Set Build / Source / Include / Docs directories
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include

KER_SRC = src/kernel
COMMON_SRC = src/clib

KERNEL_VERSION = 0.1.0

.PHONY: clean all build release 

all: build

# Compile project
## Compile every asm file in /arch/$(ARCH_DIR)
$(BUILD_DIR)/%_s.o: $(ARCH_DIR)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

## Compile every C file in /src/kernel
$(BUILD_DIR)/%_c.o: $(KER_SRC)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

## Compile every C file in /src/common
$(BUILD_DIR)/%_c.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

## Find all object files (from corresponding C, asm files)
ASM_FILES = $(wildcard $(ARCH_DIR)/*.S)
KER_C_FILES = $(wildcard $(KER_SRC)/*.c)
COMMON_C_FILES = $(wildcard $(COMMON_SRC)/*.c)

OBJ_FILES = $(ASM_FILES:$(ARCH_DIR)/%.S=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(KER_C_FILES:$(KER_SRC)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(COMMON_C_FILES:$(COMMON_SRC)/%.c=$(BUILD_DIR)/%_c.o)

## Link all object files and create final image
build: $(OBJ_FILES)
	@echo "----- Building for Raspberry Pi $(value RASPI_MODEL) -----"
	@echo "----- Building for $(value AARCH) -----"

	$(ARMGNU)-gcc -T $(ARCH_DIR)/linker.ld -o $(IMG_NAME).elf $(LDFLAGS) $^
	$(ARMGNU)-objcopy -O binary $(IMG_NAME).elf $(IMG_NAME).img

# Release project
## Create compressed binaries for version releasing
# release: build
# 	@echo "----- Releasing for Raspberry Pi $(value RASPI_MODEL) -----"
# 	@echo "----- Releasing for $(value AARCH) -----"
# 	tar -czvf $(IMG_NAME)-v$(KERNEL_VERSION).tar.gz $(IMG_NAME).img
# 	zip $(IMG_NAME)-v$(KERNEL_VERSION).zip $(IMG_NAME).img

# Clean rules
clean:
	rm -rf $(BUILD_DIR) *.img *.elf *.bin *.gz *.zip $(STUB_DIR)/$(BUILD_DIR)

