#ifndef OS_KERNEL_HW_COMM_PORT_H
#define OS_KERNEL_HW_COMM_PORT_H

#include "../com/type.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    class Port {
    
    public:
        static uint8_t inportb(uint16_t _port);
        static void outportb(uint16_t _port, uint8_t _data);
    };

    class Port8Bit {
    private:
        uint16_t m_PortNumber;
    public:
        inline Port8Bit(uint16_t portNumber) { this->m_PortNumber = portNumber;}
        inline ~Port8Bit() {}

        inline void write(uint8_t data) { Port::outportb(m_PortNumber, data); }
        inline uint8_t read() { return Port::inportb(m_PortNumber); } 
    };

}}}

#endif