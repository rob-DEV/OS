#ifndef OS_KERNEL_SYS_H
#define OS_KERNEL_SYS_H


///GLOBAL KERNEL INCLUDE

#include "com/type.h"
#include "com/string.h"
#include "com/multiboot.h"

#include "cpu/isr.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/irq.h"
#include "cpu/pit.h"

#include "hw/port.h"
#include "hw/pci.h"
#include "hw/keyboard.h"
#include "hw/mouse.h"
#include "hw/vga.h"
#include "hw/vesa.h"

#include "io/terminal.h"

#include "mm/memorymanagement.h"

#include "shell/shell.h"


#include "gui/window.h"
#include "gui/desktop.h"
#include "gui/textbox.h"




#endif