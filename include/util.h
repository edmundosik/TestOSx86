#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void memcpy(char* source , char* dest , int no_bytes);
void memorySet(uint8_t *dest, uint8_t val, uint32_t len);

#endif