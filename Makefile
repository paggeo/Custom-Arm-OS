ARMGNU ?= aarch64-none-elf-gcc

CFLAGS = -Wall 
SFLAGS = -mcpu=cortex-a52 -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only


# Set kernel image name
IMG_NAME_64 = kernel8

BUILD_DIR = build
SRC_DIR = src
INC_DIR = include


.PHONY: clean all kernel8.img 

all: kernel8.img 





clean : 
	rm -rf $(BUILD_DIR) *.img

