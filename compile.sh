#!/bin/bash

TARGET=i686-elf

#tools/nasm -f elf -o compiled/boot.o boot/grubBoot.asm
$HOME/opt/cross/bin/$TARGET-as boot/grubBoot.s -o compiled/boot.o

$HOME/opt/cross/bin/$TARGET-gcc -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I include/ -c kernel/kernel.c -o compiled/kernel/kernel.o
#$HOME/opt/cross/bin/$TARGET-ld -T link.ld compiled/boot.o -o compiled/kernel/kernel.elf -Map testos.map
$HOME/opt/cross/bin/$TARGET-gcc -T link.ld -ffreestanding -O2 -nostdlib -o compiled/kernel/kernel.exe compiled/boot.o compiled/kernel/kernel.o -lgcc

#cp compiled/boot.o iso/boot/grub/
cp compiled/kernel/kernel.exe iso/TestOS/

genisoimage -R                              \
            -b boot/grub/grub				\
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A TestOS                       \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o TestOS.iso                   \
            iso