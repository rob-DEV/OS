#ifndef OS__KERNEL_CPU_PIT_H
#define OS__KERNEL_CPU_PIT_H

#include "../com/type.h"
#include "../hw/port.h"
#include "../io/terminal.h"
#include "isr.h"
#include "irq.h"

extern "C" void timer_handler(regs* r);

typedef uint32_t clock_t;

clock_t clock();


namespace OS { namespace KERNEL { namespace CPU {

    class PIT {
    private:
        static PIT* s_Instance;
        uint32_t m_Ticks = 0;

    public:
        PIT();
        ~PIT();
        
        static PIT* getInstance();

        void handler(regs* registers);
        void install();

        uint32_t getTicks();
        void waitForMilliSeconds(uint32_t milliseconds);
       
    };

}}}

#endif