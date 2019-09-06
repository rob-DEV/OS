#ifndef OS__KERNEL_CPU_GDT_H
#define OS__KERNEL_CPU_GDT_H

#include "../common/type.h"

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));


struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

namespace OS { namespace KERNEL { namespace CPU {

    class GDT {
    private:
        static GDT* m_Instance;
        void setGDTEntry(uint32_t num, long base, long limit, unsigned char access, unsigned char gran);

    public:
        GDT();
        ~GDT();
        static GDT* getInstance();
        void install();
    
    };

}}}

#endif