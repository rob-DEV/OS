#ifndef OS_KERNEL_TERMINAL_H
#define OS_KERNEL_TERMINAL_H

#include "../common/include/type.h"
#include "../common/include/string.h"
#include "../hardware/include/port.h"

namespace OS { namespace KERNEL {


    enum vga_color{
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
        VGA_COLOR_LIGHT_GREY = 7,
        VGA_COLOR_DARK_GREY = 8,
        VGA_COLOR_LIGHT_BLUE = 9,
        VGA_COLOR_LIGHT_GREEN = 10,
        VGA_COLOR_LIGHT_CYAN = 11,
        VGA_COLOR_LIGHT_RED = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN = 14,
        VGA_COLOR_WHITE = 15,
    };

    class Terminal {
    
    private:
        
        const uint16_t VGA_WIDTH = 80;
        const uint16_t VGA_HEIGHT = 25;
        unsigned char* VGA_MEMORY = (unsigned char*)0xB8000;

        uint16_t m_CursorX;
        uint16_t m_CursorY;
        uint8_t m_Color;

        uint8_t setColor(enum vga_color fg,  enum vga_color bg);
        
        void init();
        int putchar(char c);
        void scroll();
        void moveCursor();
        

    public:
        Terminal();
        ~Terminal();
        
        void print(char c);
        void print(const char* str);
        void cls();


    };
}}

#endif