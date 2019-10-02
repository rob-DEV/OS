#ifndef OS_KERNEL_HW_COMM_VGA_H
#define OS_KERNEL_HW_COMM_VGA_H

#include "../com/type.h"
#include "../com/string.h"
#include "port.h"
#include "vga_fonts.h"

#define VGA_320x200_MEM_SIZE 320*200

#define VESA_WIDTH_ 1270
#define VESA_HEIGHT_ 1024

namespace OS { namespace KERNEL { namespace HW_COMM {

    
    class VESA {
    private:

    public:

        VESA();
        ~VESA();

        static VESA* getInstance();

        bool supportMode(uint32_t width, uint32_t height, uint32_t colorDepth);
        
        bool setMode(uint32_t width, uint32_t height, uint32_t colorDepth);
        
        void putPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);

        void putPixel(uint32_t x, uint32_t y, uint8_t color);

        void drawChar8(uint32_t x, uint32_t y, char c, uint8_t fgcolor);

        void drawChar16(uint32_t x, uint32_t y, char c, int fgcolor, int bgcolor);
        
        void fillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color);

        void fillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);

        void swapBuffers();
    };

}}}

#endif