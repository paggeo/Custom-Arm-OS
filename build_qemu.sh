#!/bin/bash

qemu-system-aarch64 -machine type=raspi3ap -m 512 -serial stdio -kernel kernel8.elf
