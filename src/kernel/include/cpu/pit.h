#ifndef OS__KERNEL_CPU_PIC_H
#define OS__KERNEL_CPU_PIC_H

#include "../common/type.h"
#include "../hardware/port.h"
#include "../io/terminal.h"
#include "isr.h"
#include "irq.h"

extern "C" void timer_handler(regs* r);

namespace OS { namespace KERNEL { namespace CPU {

    class PIT {
    private:
        static PIT* m_Instance;
        uint32_t m_Ticks = 0;

    public:
        PIT();
        ~PIT();
        
        static PIT* getInstance();

        void handler(regs* registers);
        void install();

        void waitForMilliSeconds(uint32_t milliseconds);
       
    };

}}}

#endif