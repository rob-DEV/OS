#ifndef OS__KERNEL_MEMORY_GDT_H
#define OS__KERNEL_MEMORY_GDT_H

#include "../common/type.h"

namespace OS { namespace KERNEL { namespace MEMORY {

    class GDT {
    private:
        
        void setGDTEntry(uint32_t num, long base, long limit, unsigned char access, unsigned char gran);
        void init();

    public:
        GDT();
        ~GDT();

        void install();
    
    };

}}}

#endif