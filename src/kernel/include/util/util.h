#ifndef OS_KERNEL_UTIL_UTIL_H
#define OS_KERNEL_UTIL_UTIL_H

#include "../com/type.h"

namespace OS { namespace KERNEL {

    class Util { 
    public:
        static int atoi(const char *str);
        
        static void itoa(int n, char s[]);

        static void ftoa(float f, char s[]);

        static void reverse(char s[]);

        static uint32_t strlen(const char* c);

        static bool strcmp(const char* a, const char* b);

        static int uintToHexStr(uint32_t num,char* buff);

        static void memcpy(void* src, void* dst , size_t size);
        
        static void memset(void* dst, uint32_t size, uint8_t fill);
        
        static void memsetw(void* dst, uint32_t size, uint16_t fill);
        
        static void* memmove(void *dst_void, const void *src_void, size_t length);
        
        

    };

}}

#endif