#ifndef OS_KERNEL_HW_COMM_VGA_H
#define OS_KERNEL_HW_COMM_VGA_H

#include "../common/type.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    class VGA {
    
    public:

        VGA();
        ~VGA();

        void init();

        void putPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
        void fillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);

    };

}}}

#endif