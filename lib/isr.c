#include <isr.h>
#include <drivers/vga.h>

void isrHandler(registers_t _regs)
{
    print("recieved interrupt: ");
    printDec(_regs.int_no);
    print('\n');
}
