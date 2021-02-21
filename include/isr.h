#ifndef ISR_H
#define ISR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct registers
{
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, useless_esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, esp, ss; // Pushed by the processor automatically.
} registers_t;


#endif