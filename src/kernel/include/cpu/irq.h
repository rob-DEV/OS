#ifndef OS__KERNEL_CPU_IRQ_H
#define OS__KERNEL_CPU_IRQ_H

#include "../com/type.h"
#include "../hw/port.h"
#include "isr.h"


extern "C" void irq_handler(regs_t* r);

namespace OS { namespace KERNEL { namespace CPU {

    class IRQ {
    private:
        static IRQ* s_Instance;
        
        void remap();

    public:
        IRQ();
        ~IRQ();
        
        static IRQ* getInstance();

        void install(); 
        
        void irq_install(int irq, void (*handler)(struct regs *r));
        void irq_uninstall(int irq);   
        void irq_handler(regs_t* registers);
       
    };

}}}

#endif