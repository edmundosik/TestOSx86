#include <low_level.h>

uint8_t inb(unsigned short port) {
  // A handy C wrapper  function  that  reads a byte  from  the  specified  port
  //   "=a" (result) means: put AL  register  in  variable  RESULT  when  finished
  //   "d" (port) means: load  EDX  with  port
  uint8_t result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port ));
  return  result;
}

void outb(unsigned short port, unsigned char data) {
  // "a" (data) means: load  EAX  with  data
  // "d" (port) means: load  EDX  with  port
  __asm__("out %%al, %%dx" : :"a" (data), "d" (port ));
}

/*uint16_t inw(unsigned short port) {
    uint16_t  result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port ));
    return  result;
}*/

void  outw(unsigned short port, unsigned short data) {
  __asm__("out %%ax, %%dx" : :"a" (data), "d" (port ));
}
