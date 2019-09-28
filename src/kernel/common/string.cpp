#include "../include/common/string.h"

uint32_t strlen(const char* c) {
    char i;
    uint32_t length = 0;
    while((i = c[length]) != 0){
        length++;
    }
    return length;
}

bool strcmp(const char* a, const char* b) {
    if(strlen(a) != strlen(b))
        return false;

    while (*a) {
        if(*a != *b)
            return false;
    
        ++a;
        ++b;
    }
    
}

void memcpy(void* src, void* dst , size_t size) {
    
    if(src == dst)
        return;

    uint8_t* bsrc = (uint8_t*)src;
    uint8_t* bdst = (uint8_t*)dst;

    for (uint32_t i = 0; i < size; i++)
        bdst[i] = bsrc[i];
    
    
}

void memset(void* dst, uint32_t size, uint8_t fill){
    for (uint32_t i = 0; i < size; i++)
        ((uint8_t*)dst)[i] = fill;
}

void memsetw(void* dst, uint32_t size, uint16_t fill) {
    for (uint32_t i = 0; i < size; i++)
        ((uint16_t*)dst)[i] = fill;
}

void *memmove(void *dst_void, const void *src_void, size_t length) {
    char *dst = (char*)dst_void;
    const char *src = (const char*)src_void;

    if (src < dst && dst < src + length)
    {
        src += length;
        dst += length;
        while (length--)
        {
            *--dst = *--src;
        }
    }
    else
    {
        while (length--)
            *dst++ = *src++;
    }

    return dst_void;
}