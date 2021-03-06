#ifndef OS_KERNEL_HW_COMM_VGA_H
#define OS_KERNEL_HW_COMM_VGA_H

#include "../com/type.h"
#include "../com/string.h"
#include "port.h"
#include "vga_fonts.h"

#define VGA_320x200_MEM_SIZE 320*200

#define VGA_WIDTH_ 320
#define VGA_HEIGHT_ 200

namespace OS { namespace KERNEL { namespace HW_COMM {

    struct RGB_Color{
        uint8_t R,G,B = 0;

        inline RGB_Color() : R(0), G(0), B(0) { };
        inline RGB_Color(uint8_t r, uint8_t g, uint8_t b) : R(r), G(g), B(b) { };
        inline ~RGB_Color() { }

    };

    class VGA {
    private:
        HW_COMM::Port8Bit miscPort;
        HW_COMM::Port8Bit crtcIndexPort;
        HW_COMM::Port8Bit crtcDataPort;
        HW_COMM::Port8Bit sequencerIndexPort;
        HW_COMM::Port8Bit sequencerDataPort;
        HW_COMM::Port8Bit graphicsControllerIndexPort;
        HW_COMM::Port8Bit graphicsControllerDataPort;
        HW_COMM::Port8Bit attributeControllerIndexPort;
        HW_COMM::Port8Bit attributeControllerReadPort;
        HW_COMM::Port8Bit attributeControllerWritePort;
        HW_COMM::Port8Bit attributeControllerResetPort;



        void writeregisters(uint8_t* registers);
        
        uint8_t* getFrameBufferSegment();

        uint8_t getColorIndex(RGB_Color color);

        static VGA* s_Instance;

        uint8_t** m_VGA_Buffers;
        uint8_t m_VGA_Active_Buffer;
        bool initalFrameCopied;

    public:

        VGA();
        ~VGA();

        static VGA* getInstance();

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