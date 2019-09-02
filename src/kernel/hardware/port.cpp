#include "include/port.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    unsigned char Port::inportb(uint16_t _port) {
        unsigned char rv;
        __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
        return rv;
    }



}}}