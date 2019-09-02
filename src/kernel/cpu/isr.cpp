#include "../include/cpu/isr.h"

//terminal hack
#include "../include/io/terminal.h"

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

void fault_handler(regs* r) {

    //c wrapper to static function to be changed to singleton
    OS::KERNEL::CPU::ISR::faults(r);

}


namespace OS { namespace KERNEL { namespace CPU {

    uint32_t ISR::terminalAddress = 0;
    ISR::ISR() {
        
    }

    ISR::~ISR() {

    }

    void ISR::install() {
        idt->setIDTEntry(0, (unsigned)isr0, 0x08, 0x8E);
        idt->setIDTEntry(1, (unsigned)isr1, 0x08, 0x8E);
        idt->setIDTEntry(2, (unsigned)isr2, 0x08, 0x8E);
        idt->setIDTEntry(3, (unsigned)isr3, 0x08, 0x8E);
        idt->setIDTEntry(4, (unsigned)isr4, 0x08, 0x8E);
        idt->setIDTEntry(5, (unsigned)isr5, 0x08, 0x8E);
        idt->setIDTEntry(6, (unsigned)isr6, 0x08, 0x8E);
        idt->setIDTEntry(7, (unsigned)isr7, 0x08, 0x8E);
        idt->setIDTEntry(8, (unsigned)isr8, 0x08, 0x8E);
        idt->setIDTEntry(9, (unsigned)isr9, 0x08, 0x8E);
        idt->setIDTEntry(10, (unsigned)isr10, 0x08, 0x8E);
        idt->setIDTEntry(11, (unsigned)isr11, 0x08, 0x8E);
        idt->setIDTEntry(12, (unsigned)isr12, 0x08, 0x8E);
        idt->setIDTEntry(13, (unsigned)isr13, 0x08, 0x8E);
        idt->setIDTEntry(14, (unsigned)isr14, 0x08, 0x8E);
        idt->setIDTEntry(15, (unsigned)isr15, 0x08, 0x8E);
        idt->setIDTEntry(16, (unsigned)isr16, 0x08, 0x8E);
        idt->setIDTEntry(17, (unsigned)isr17, 0x08, 0x8E);
        idt->setIDTEntry(18, (unsigned)isr18, 0x08, 0x8E);
        idt->setIDTEntry(19, (unsigned)isr19, 0x08, 0x8E);
        idt->setIDTEntry(20, (unsigned)isr20, 0x08, 0x8E);
        idt->setIDTEntry(21, (unsigned)isr21, 0x08, 0x8E);
        idt->setIDTEntry(22, (unsigned)isr22, 0x08, 0x8E);
        idt->setIDTEntry(23, (unsigned)isr23, 0x08, 0x8E);
        idt->setIDTEntry(24, (unsigned)isr24, 0x08, 0x8E);
        idt->setIDTEntry(25, (unsigned)isr25, 0x08, 0x8E);
        idt->setIDTEntry(26, (unsigned)isr26, 0x08, 0x8E);
        idt->setIDTEntry(27, (unsigned)isr27, 0x08, 0x8E);
        idt->setIDTEntry(28, (unsigned)isr28, 0x08, 0x8E);
        idt->setIDTEntry(29, (unsigned)isr29, 0x08, 0x8E);
        idt->setIDTEntry(30, (unsigned)isr30, 0x08, 0x8E);
        idt->setIDTEntry(31, (unsigned)isr31, 0x08, 0x8E);
    }

    void ISR::faults(regs* r) {
        /* Is this a fault whose number is from 0 to 31? */
        if (r->int_no < 32)
        {
            /* Display the description for the Exception that occurred.
            *  In this tutorial, we will simply halt the system using an
            *  infinite loop */
           Terminal* terminal = (Terminal*)terminalAddress;
            terminal->print(exception_messages[r->int_no]);
            terminal->print(" Exception. System Halted!\n");
            //puts(exception_messages[r->int_no]);
            //puts(" Exception. System Halted!\n");
            for (;;);
            
        }

    }

}}}