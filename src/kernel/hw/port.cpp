#include "../include/hw/port.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    uint8_t Port::inportb(uint16_t _port) {
        uint8_t rv;
        __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
        return rv;
    }

    void Port::outportb (uint16_t _port, uint8_t _data)
    {
        __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
    }

}}}
