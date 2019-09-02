#ifndef OS_KERNEL_STRING_H
#define OS_KERNEL_STRING_H

#include "type.h"

uint32_t strlen(const char* c);
bool strcmp(const char* a, const char* b);
void memcpy(void* src, void* dst , size_t size);
void memset(void* dst, uint32_t size, uint8_t fill);
void memsetw(void* dst, uint32_t size, uint16_t fill);
void *memmove(void *dst_void, const void *src_void, size_t length);


#endif //OS_KERNEL_STRING_H