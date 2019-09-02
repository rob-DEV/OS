#include "../include/hardware/port.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    unsigned char Port::inportb(uint16_t _port) {
        unsigned char rv;
        __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
        return rv;
    }

    void Port::outportb (unsigned short _port, unsigned char _data)
    {
        __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
    }

}}}
