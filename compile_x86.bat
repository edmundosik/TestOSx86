@echo off

tools\nasm -f bin -o compiled/btlr_x86.bin boot/btlr_x86.asm
tools\nasm -f elf -o compiled/kernel/kernel_entry.o boot/kernel_entry.asm

gcc -ffreestanding -I include/ -c kernel/kernel.c -o compiled/kernel/kernel.o -lc
ld -T NUL -o compiled/kernel/kernel -Ttext 0x1000 compiled/kernel/kernel_entry.o compiled/kernel/kernel.o
objcopy -O binary -j .text compiled/kernel/kernel compiled/kernel/kernel.bin
REM ld -m i386pe -s -o compiled/kernel.bin -Ttext 0x1000 Compiled/kernel_entry.o kernel/kernel.o --oformat binary
REM elf_i386

del TestOSx86
del TestOSx86.img

type compiled\btlr_x86.bin compiled\kernel\kernel.bin > TestOSx86

tools\mkdosfs -C TestOSx86.img 1440

tools\dd conv=notrunc if=TestOSx86 of=TestOSx86.img

pause

