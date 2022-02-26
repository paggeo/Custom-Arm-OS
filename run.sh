#!/bin/bash

aarch64-none-elf-gcc -mcpu=cortex-a53 -fpic -ffreestanding -c boot.S -o boot.o
aarch64-none-elf-gcc -mcpu=cortex-a53 -fpic -ffreestanding -std=gnu99 -c kernel.c -o kernel.o -O2 -Wall -Wextra

aarch64-none-elf-gcc -T linker.ld -o myos.elf -ffreestanding -O2 -nostdlib boot.o kernel.o

