#ifndef OS_KERNEL_HW_COMM_PORT_H
#define OS_KERNEL_HW_COMM_PORT_H

#include "../common/type.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    class Port {
    
    public:

    static unsigned char inportb(uint16_t _port);
    static void outportb(uint16_t _port, unsigned char _data);
    };

}}}

#endif