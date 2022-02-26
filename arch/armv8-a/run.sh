#!/bin/bash


aarch64-none-elf-gcc -mcpu=cortex-a53 -fpic -ffreestanding -c boot.S -o boot.o

