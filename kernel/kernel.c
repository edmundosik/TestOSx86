// x86 Kernel for TestOS
// Version: v0.0.1

// Init drivers
#include <drivers/vga.h>
#include <descriptor_table.h>
#define ROOTDIR "$>"

void kmain(struct multiboot *mboot_ptr) {
  init_descriptor_tables();

  clear_screen();

  print("\nTestOS x86 Kernel.");
  set_cursor(get_screen_offset(-20,2*2));
  print(ROOTDIR);
  
  asm volatile("int $0x03");
  asm volatile("int $0x04");

  for (;;);
}
