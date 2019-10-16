#include <stdio.h>
#include "../../kernel/include/io/terminal.h"
#include "../../kernel/include/util/util.h"
//printf putchar puts



void putchar(char c) {
    OS::KERNEL::Terminal::getInstance()->putchar(c);
}

void puts(const char* s) {
    OS::KERNEL::Terminal::getInstance()->puts(s);
}

int printf(const char* __restrict format, ...) {

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
            if (!OS::KERNEL::Terminal::getInstance()->puts(format, amount))
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
            if (!OS::KERNEL::Terminal::getInstance()->puts(&c, sizeof(c)))
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
            if (!OS::KERNEL::Terminal::getInstance()->puts(str, len))
                return -1;
            written += len;
        }
        else if (*format == 'd') {
            format++;
            int input = va_arg(parameters, int /* char promotes to int */);
            char buff[8];//enough for 64 bits integer
            int length;

            OS::KERNEL::Util::itoa(input, buff);
            
            if (!maxrem) 
                // TODO: Set errno to EOVERFLOW.
                return -1;
            
           
            
            if (!OS::KERNEL::Terminal::getInstance()->puts(buff, strlen(buff)))
                return -1;
                
            written++;
        } 
         else if (*format == 'f') {


            format++;
            double input = va_arg(parameters, double /* char promotes to int */);
            char buff[8];//enough for 64 bits integer
            int length;
            //convert
            OS::KERNEL::Util::ftoa(input,buff);

            
            if (!maxrem) 
                // TODO: Set errno to EOVERFLOW.
                return -1;
            
           
            
            if (!OS::KERNEL::Terminal::getInstance()->puts(buff, strlen(buff)))
                return -1;

            //weird bug fix with this zeroing 
            //check out
            memset(buff, 8 , 0);
            written++;
        } 
        else if (*format == 'x') {
            format++;
            int input = va_arg(parameters, int /* char promotes to int */);

            char buff[16];//enough for 64 bits integer
            int length;
            //convert
            length = OS::KERNEL::Util::uintToHexStr(input,buff);

            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!OS::KERNEL::Terminal::getInstance()->puts(buff, strlen(buff)))
                return -1;
            written++;
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!OS::KERNEL::Terminal::getInstance()->puts(format, len))
                return -1;
            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;

}