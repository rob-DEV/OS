#include "../include/cpu/irq.h"

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

 void *irq_routines[16] =
    {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    };

extern "C" void irq_handler(regs *r)
{
    /* This is a blank function pointer */
    void (*handler)(regs *r);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = (void (*)(regs*))irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }
    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        OS::KERNEL::HW_COMM::Port::outportb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    OS::KERNEL::HW_COMM::Port::outportb(0x20, 0x20);
}

namespace OS { namespace KERNEL { namespace CPU {

   

    IRQ::IRQ() {
        
    }

    IRQ::~IRQ() {

    }


}}}