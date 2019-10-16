#ifndef LIB_C_STDIO_H
#define LIB_C_STDIO_H


/// WRAPPER FOR UNDERLYING KERNEL FUNCTIONS

//putchar 
//puts
//printf

void putchar(char c);
void puts(const char* s);

int printf(const char* __restrict format, ...);

#endif