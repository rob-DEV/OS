#ifndef OS__KERNEL_CPU_ISRS_H
#define OS__KERNEL_CPU_ISRS_H

#include "../com/type.h"
#include "../com/string.h"

#include "idt.h"

typedef struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
} regs_t;



extern "C" void fault_handler(regs_t* r);




static const char *exception_messages[32] =
        {
                "Division By Zero",
                "Debug",
                "Non Maskable Interrupt",
                "Breakpoint",
                "Into Detected Overflow",
                "Out of Bounds",
                "Invalid Opcode",
                "No Coprocessor",

                "Double Fault",
                "Coprocessor Segment Overrun",
                "Bad TSS",
                "Segment Not Present",
                "Stack Fault",
                "General Protection Fault",
                "Page Fault",
                "Unknown Interrupt",

                "Coprocessor Fault",
                "Alignment Check",
                "Machine Check",
                "Reserved",
                "Reserved",
                "Reserved",
                "Reserved",
                "Reserved",

                "Reserved",
                "Reserved",
                "Reserved",
                "Reserved",
                "Reserved",
                "Reserved",
                "Reserved",
                "Reserved"
        };






namespace OS { namespace KERNEL { namespace CPU {

    class ISR {
    private:
        IDT* idt;
        static ISR* s_Instance;
    public:
        ISR();
        ~ISR();

        static ISR* getInstance();

        void install();
        void handle_fault(regs_t* r);
    
    };

}}}

#endif