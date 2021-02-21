#ifndef IDT_H
#define IDT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct idtDesc {
    uint16_t base;
    uint32_t limit;
};

#endif