#ifndef OS_KERNEL_HW_PC_SPEAKER_H
#define OS_KERNEL_HW_PC_SPEAKER_H

#include "../com/type.h"
#include "port.h"


namespace OS { namespace KERNEL { namespace HW_COMM {

    class PCI {
    
    private:
        static PCI* s_Instance;

    public:
        PCI();
        ~PCI();

         static PCI* getInstance();

    };

}}}

#endif