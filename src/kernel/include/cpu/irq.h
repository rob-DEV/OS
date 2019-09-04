#ifndef OS__KERNEL_CPU_IRQ_H
#define OS__KERNEL_CPU_IRQ_H

#include "../common/type.h"
#include "../hardware/port.h"
#include "isr.h"

namespace OS { namespace KERNEL { namespace CPU {

    class IRQ {
    private:
        
    public:
        IRQ();
        ~IRQ();

        void install();
    };

}}}

#endif