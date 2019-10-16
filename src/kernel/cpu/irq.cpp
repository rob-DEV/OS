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

void* irq_routines[16] =
{
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};

void irq_handler(regs_t * registers) {
    OS::KERNEL::CPU::IRQ::getInstance()->irq_handler(registers);
}

namespace OS { namespace KERNEL { namespace CPU {

    IRQ* IRQ::s_Instance = NULL;

    IRQ::IRQ() {
        
    }

    IRQ::~IRQ() {

    }

    IRQ* IRQ::getInstance() {
        if(s_Instance == NULL)
            s_Instance = new IRQ();
        
        return s_Instance;
    }

    void IRQ::irq_install(int irq, void (*handler)(struct regs *r)){
        irq_routines[irq] = (void*)handler;
    }
    void IRQ::irq_uninstall(int irq){
        irq_routines[irq] = 0;
    }
    void IRQ::install(){
        remap();

        IDT::getInstance()->setIDTEntry(32, (unsigned)irq0, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(33, (unsigned)irq1, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(34, (unsigned)irq2, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(35, (unsigned)irq3, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(36, (unsigned)irq4, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(37, (unsigned)irq5, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(38, (unsigned)irq6, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(39, (unsigned)irq7, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(40, (unsigned)irq8, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(41, (unsigned)irq9, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(42, (unsigned)irq10, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(43, (unsigned)irq11, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(44, (unsigned)irq12, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(45, (unsigned)irq13, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(46, (unsigned)irq14, 0x08, 0x8E);
        IDT::getInstance()->setIDTEntry(47, (unsigned)irq15, 0x08, 0x8E);

        //restarting interrupts so this can actually work..
        __asm__ __volatile__ ("sti");
    }

    

    void IRQ::remap() {
        HW_COMM::Port::outportb(0x20, 0x11);
        HW_COMM::Port::outportb(0xA0, 0x11);
        HW_COMM::Port::outportb(0x21, 0x20);
        HW_COMM::Port::outportb(0xA1, 0x28);
        HW_COMM::Port::outportb(0x21, 0x04);
        HW_COMM::Port::outportb(0xA1, 0x02);
        HW_COMM::Port::outportb(0x21, 0x01);
        HW_COMM::Port::outportb(0xA1, 0x01);
        HW_COMM::Port::outportb(0x21, 0x0);
        HW_COMM::Port::outportb(0xA1, 0x0);
    }

    void IRQ::irq_handler(regs_t* registers) {
        /* This is a blank function pointer */
        void (*handler)(regs_t *r);

        /* Find out if we have a custom handler to run for this
        *  IRQ, and then finally, run it */
        handler = (void (*)(regs_t*))irq_routines[registers->int_no - 32];
        if (handler)
        {
            handler(registers);
        }
        /* If the IDT entry that was invoked was greater than 40
        *  (meaning IRQ8 - 15), then we need to send an EOI to
        *  the slave controller */
        if (registers->int_no >= 40)
        {
            OS::KERNEL::HW_COMM::Port::outportb(0xA0, 0x20);
        }

        /* In either case, we need to send an EOI to the master
        *  interrupt controller too */
        OS::KERNEL::HW_COMM::Port::outportb(0x20, 0x20);
    }

}}}