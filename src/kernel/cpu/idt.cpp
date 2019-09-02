#include "../include/cpu/idt.h"


struct idt_entry idt[256];
struct idt_ptr idtp;

extern "C" void idt_load();

namespace OS { namespace KERNEL { namespace CPU {

    IDT::IDT() {

    }

    IDT::~IDT() {

    }

    void IDT::setIDTEntry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
        idt[num].base_lo = (base & 0xFFFF);
        idt[num].base_hi = (base >> 16) & 0xFFFF;

        idt[num].sel = sel;
        idt[num].always0 = 0;
        idt[num].flags = flags;
    }

    void IDT::install() {
         /* Sets the special IDT pointer up, just like in 'gdt.c' */
        idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
        idtp.base = (uint32_t)&idt;

        /* Clear out the entire IDT, initializing it to zeros */
        memset(&idt, 0, sizeof(struct idt_entry) * 256);

        /* Points the processor's internal register to the new IDT */
        idt_load();
    }

}}}