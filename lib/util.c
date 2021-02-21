#include <util.h>

void memcpy(char* source , char* dest , int no_bytes) {
  int i;
  for (i = 0; i < no_bytes; i++) {
    *(dest + i) = *(source + i);
  }
}

void memorySet(uint8_t *dest, uint8_t val, uint32_t len) {
  uint8_t *temp = (uint8_t*)dest;

  for (; len != 0; len--) {
    *temp++ = val;
  }
}
