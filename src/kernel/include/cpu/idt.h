#ifndef OS__KERNEL_CPU_IDT_H
#define OS__KERNEL_CPU_IDT_H

#include "../com/type.h"
#include "../com/string.h"

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

namespace OS { namespace KERNEL { namespace CPU {

    class IDT {
    private:
        static IDT* s_Instance;
    public:
        IDT();
        ~IDT();

        static IDT* getInstance();

        void setIDTEntry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
        void install();
    
    };

}}}

#endif