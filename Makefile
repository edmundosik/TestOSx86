SOURCES=							\
$(KERNEL_DIR)/kernel.c				\
$(DRIVER_DIR)/vga.c					\
$(LIB_DIR)/low_level.c				\
$(LIB_DIR)/util.c					\
$(LIB_DIR)/descriptor_table.c		\
$(LIB_DIR)/isr.c

AS_SOURCES=						\
boot/grubBoot.s					

ASM_SOURCES=					\
$(INCLUDE_DIR)/gdt.asm 			\
$(LIB_DIR)/interrupt.asm 		
   		
	
KERNEL_DIR=kernel
DRIVER_DIR=drivers
LIB_DIR=lib
INCLUDE_DIR=include

COMPILED_DIR=compiled

OBJECTS=$(SOURCES:.c=.o) $(AS_SOURCES:.s=.o) $(ASM_SOURCES:.asm=.o)

TARGET=i686-elf
HOME=~

USER=whoami

GCCFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -I include/ -c
LDFLAGS=-T link.ld -ffreestanding -O2 -nostdlib
ASFLAGS=-f elf 
GENISOIMAGEFLAGS=-R -b boot/grub/grub -no-emul-boot -boot-load-size 4 -A TestOS -input-charset utf8 -quiet -boot-info-table -o TestOS.iso iso
CROSSCOMPILER=/home/edmundosik/opt/cross/bin/$(TARGET)
BOCHS=/cygdrive/c/Program\ Files/Bochs-2.6.11/bochs.exe
GCC=$(CROSSCOMPILER)-gcc
AS=$(CROSSCOMPILER)-as
ASM=tools/nasm

all: $(SOURCES) kernel.exe TestOS.iso

kernel.exe: $(OBJECTS)
	$(GCC) $(LDFLAGS) $(OBJECTS) -o compiled/kernel/kernel.exe

TestOS.iso: kernel.exe
	cp compiled/kernel/kernel.exe iso/TestOS/
	genisoimage $(GENISOIMAGEFLAGS)
	
run: TestOS.iso
	$(BOCHS) -f bochsrc.bxrc -q

%.o: %.c
	$(GCC) $(GCCFLAGS) $< -o $@
	
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@
	
%.o: %.asm
	$(ASM) $(ASFLAGS) $< -o $@
	
clean: 
	rm -f compiled/kernel/ *.o
	rm -f compiled/ *.o
	rm -f TestOS.iso