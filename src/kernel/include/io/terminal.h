#ifndef OS_KERNEL_IO_TERMINAL_H
#define OS_KERNEL_IO_TERMINAL_H

#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>

#include "../common/type.h"
#include "../common/string.h"
#include "../hardware/port.h"
#include "../util/util.h"
#include "../memory/memorymanagement.h"

#define EOF -1

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

        static Terminal* m_Instance;

      
        void init();
        int putchar(char c);
        bool print(const char* data, size_t length);
        void scroll();
        void moveCursor();
        
    public:
        Terminal();
        ~Terminal();

        static Terminal* getInstance();

        void print(char c);
        void print(const char* str);
        int printf(const char* __restrict format, ...);

        void setColor(enum vga_color fg,  enum vga_color bg);
        void cls();


    };
}}

#endif