; x86 Bootloader for TestOS
; Version: v0.1.1

section .text
use16
org 0x7c00

;extern _kmain

;global start

_start:
  call clear_screen

  mov [BOOT_DRIVE], dl 
  mov bp, 0x9000
  mov sp, bp
  call load_krn
  
  mov si, kernel_loaded
  call _print

  cli

  xor ax, ax
  mov ds, ax

  lgdt [gdt_desc]
  
  mov eax, cr0
  or eax, 1
  mov cr0, eax

  jmp 08h:init
  jmp $

load_krn:
  mov bx, KERNEL_OFFSET
  mov dh, 15 ; Load first 15 Sectors
  mov dl, [BOOT_DRIVE]
  call disk_load
  ret

clear_screen:
  pusha
  mov ah, 0
  mov al, 3h
  int 10h
  popa
  ret

disk_load:
  mov si, mem_load_krnl
  call _print

  push dx
  mov ah, 0x02
  mov al, dh
  mov ch, 0x00
  mov dh, 0x00
  mov cl, 0x02
  
  int 13h 
  jc  .disk_error
  pop dx
  cmp dh, al
  jne .disk_error
  ret
  .disk_error:
    mov si, disk_err
    call _print
    jmp $

_print:
  pusha
  mov ah, 0Eh

  .repeat:
    lodsb
    cmp al, 0
    je .end
    int 10h
    jmp .repeat
  .end:
    popa
    ret

VIDMEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
KERNEL_OFFSET equ 0x1000
BOOT_DRIVE db 0
DATA_SEG equ gdt_data - gdt
CODE_SEG equ gdt_code - gdt

use32
_print_pm:
  pusha
  mov edx, VIDMEMORY
  add edx, 320 ; offset
  .repeat1:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK
    cmp al, 0
    je .end1
    mov [edx], ax
    add ebx, 1
    add edx, 2
    jmp .repeat1
  .end1: 
    popa
    ret

use32
init:
  mov ax, 10h
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ;mov ebp, 0x90000
  ;mov esp, ebp

  mov ebx, pm_mode
  call _print_pm

  call 8:KERNEL_OFFSET

  hang:
    jmp hang

disk_err db 'Disk read error.', 10, 13, 0
kernel_loaded db 'Kernel loaded into memory.', 10, 13, 0
mem_load_krnl db 'Loading kernel into memory...', 10, 13, 0
pm_mode db 'Booting kernel...', 0

gdt:
  gdt_null:
    dd 0
    dd 0
  gdt_code:
    dw 0FFFFh
    dw 0
    db 0
    db 10011010b
    db 11001111b
    db 0
  gdt_data:
    dw 0FFFFh
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0
  gdt_end:
  gdt_desc:
    dw gdt_end - gdt - 1
    dd gdt

times 510 - ( $ - $$ ) db 0
dw 0AA55h
