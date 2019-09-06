#ifndef OS__KERNEL_CPU_IRQ_H
#define OS__KERNEL_CPU_IRQ_H

#include "../common/type.h"
#include "../hardware/port.h"
#include "isr.h"


extern "C" void irq_handler(regs* r);

namespace OS { namespace KERNEL { namespace CPU {

    class IRQ {
    private:
        static IRQ* m_Instance;
        
        void remap();

    public:
        IRQ();
        ~IRQ();
        
        static IRQ* getInstance();

        void install(); 
        
        void irq_install(int irq, void (*handler)(struct regs *r));
        void irq_uninstall(int irq);   
        void irq_handler(regs* registers);
       
    };

}}}

#endif