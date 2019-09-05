#include "../include/io/terminal.h"

namespace OS { namespace KERNEL {

    Terminal* Terminal::m_Instance = NULL;

    Terminal::Terminal(){
        init();
    }

    Terminal::~Terminal(){

    }

    Terminal* Terminal::getInstance() {
        if(m_Instance == NULL) 
            m_Instance = new Terminal();

        return m_Instance;
    }

    void Terminal::setColor(enum vga_color fg,  enum vga_color bg) {
        m_Color = fg | bg << 4;
        cls();
    }

    void Terminal::init() {
        m_CursorX = 0;
        m_CursorY = 0;
        
        setColor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        
        cls();
    }

    int Terminal::putchar(char c) {
        if(c == '\n' || c == '\r'){
            m_CursorX = 0;
            ++m_CursorY;
        }
        else if(c == '\b') {
            //MOVE THE CURSOR BACKWARDS
            //THIS DOESN'T DELETE THE CHARACTER
            //IT SIMPLY ALLOWS YOU TO OVERWRITE IT
            //TODO: replace with space char
            m_CursorX--;
        }
        else {
            unsigned int position = m_CursorY * VGA_WIDTH + m_CursorX;
            unsigned char*  _videoMemAddr = VGA_MEMORY + position*2;
            *_videoMemAddr = c;
            *(_videoMemAddr+1) = m_Color;
            m_CursorX++;

            if (m_CursorX == VGA_WIDTH)
            {
                m_CursorX = 0;
                m_CursorY++;
            }
        }

         if (m_CursorY == VGA_HEIGHT) {
            memmove(VGA_MEMORY, VGA_MEMORY + (VGA_WIDTH * 2), (VGA_WIDTH * (VGA_HEIGHT - 1)) * 2);
            memset(VGA_MEMORY + ((VGA_WIDTH * (VGA_HEIGHT - 1)) * 2), VGA_WIDTH * 2, 0);
            m_CursorY--;
        }
        scroll();
        moveCursor();
        return 0;
    }

    bool Terminal::print(const char* data, size_t length) {
        const unsigned char* bytes = (const unsigned char*) data;
        for (size_t i = 0; i < length; i++)
            if (putchar(bytes[i]) == EOF)
                return false;
        return true;
    }

    void Terminal::scroll() {

        unsigned blank, temp;
        int attrib = 0x0F;

        /* A blank is defined as a space... we need to give it
        *  backcolor too */
        blank = 0x20 | (attrib << 8);

        /* Row 25 is the end, this means we need to scroll up */
        if(m_CursorY >= 25)
        {
            /* Move the current text chunk that makes up the screen
            *  back in the buffer by a line */
            temp = m_CursorY - 25 + 1;
            memcpy (VGA_MEMORY, VGA_MEMORY + temp * 80, (25 - temp) * 80 * 2);

            /* Finally, we set the chunk of memory that occupies
            *  the last line of text to our 'blank' character */
            memsetw (VGA_MEMORY + (25 - temp) * 80, blank, 80);
            m_CursorY = 25 - 1;
        }
    }


    void Terminal::moveCursor() {
        
        unsigned int temp;

        temp = m_CursorY * VGA_WIDTH + m_CursorX;

        HW_COMM::Port::outportb(0x3D4, 14);
        HW_COMM::Port::outportb(0x3D5, temp >> 8);
        HW_COMM::Port::outportb(0x3D4, 15);
        HW_COMM::Port::outportb(0x3D5, temp);

    }

    void Terminal::print(const char* str) {
        
        while (*str != 0)
        {
            putchar((*str));
            str++;
        }
    }

    void Terminal::print(char c) {
        putchar(c);
    }

    int Terminal::printf(const char* __restrict format, ...) {
        
    va_list parameters;
    va_start(parameters, format);


    int written = 0;
    char buffer[512];

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount) {
            // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int);
            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        }
        else if (*format == 's') {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        }
        else if (*format == 'd') {
            format++;
            int input = va_arg(parameters, int /* char promotes to int */);
            
            Util::itoa(input, buffer);
            
            if (!maxrem) 
                // TODO: Set errno to EOVERFLOW.
                return -1;
            
           
            
            if (!print(buffer, strlen(buffer)))
                return -1;
                
            written++;
        } else if (*format == 'x') {
            format++;
            int input = va_arg(parameters, int /* char promotes to int */);

            char buff[16];//enough for 64 bits integer
            int length;
            //convert
            length = Util::uintToHexStr(input,buff);

            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(buff, strlen(buff)))
                return -1;
            written++;
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;

    }

    void Terminal::cls() {

        unsigned char* _videoMemAddr = VGA_MEMORY;
        for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        {
            *_videoMemAddr = ' ';
            *(_videoMemAddr + 1) = m_Color;
            _videoMemAddr += 2;
        }

        m_CursorX = 0;
        m_CursorY = 0;
        moveCursor();
        
    }

}}