#include "../include/util/util.h"

namespace OS { namespace KERNEL {

    int Util::atoi(const char *str) {
        int res =  0;
        int sign = 1; //positive default
        int i = 0;

        if(str[0] == '-') {
            sign = -1;
            i++;
        }

        for(; str[i] != '\0'; i++)
            res = res*10 + str[i] - '0';

        return sign*res;
    }

    void Util::reverse(char s[])
    {
        int i, j;
        char c;

        for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
            c = s[i];
            s[i] = s[j];
            s[j] = c;
        }
    }

    void Util::itoa(int n, char s[])
    {
        int i, sign;

        if ((sign = n) < 0)  /* record sign */
            n = -n;          /* make n positive */
        i = 0;
        do {       /* generate digits in reverse order */
            s[i++] = n % 10 + '0';   /* get next digit */
        } while ((n /= 10) > 0);     /* delete it */
        if (sign < 0)
            s[i++] = '-';
        s[i] = '\0';
        reverse(s);

    }

    uint32_t Util::strlen(const char* c) {
         char i;
        uint16_t length = 0;
        while((i = c[length]) != 0){
            length++;
        }
        return length;
    }

    bool Util::strcmp(const char* a, const char* b) {
        if(strlen(a) != strlen(b))
            return false;

        while (*a) {
            if(*a != *b)
                return false;
        
            ++a;
            ++b;
        }
        
    }

    static char hex [] = { '0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9' ,'A', 'B', 'C', 'D', 'E', 'F' };
                        
    int Util::uintToHexStr(uint32_t num, char* buffer) {
        
            int len=0,k=0;
        do//for every 4 bits
        {
            //get the equivalent hex digit
            buffer[len] = hex[num&0xF];
            len++;
            num>>=4;
        }while(num!=0);
        //since we get the digits in the wrong order reverse the digits in the buffer
        for(;k<len/2;k++)
        {//xor swapping
            buffer[k]^=buffer[len-k-1];
            buffer[len-k-1]^=buffer[k];
            buffer[k]^=buffer[len-k-1];
        }
        //null terminate the buffer and return the length in digits
        buffer[len]='\0';
        return len;
    }

    void Util::memcpy(void* src, void* dst , size_t size) {
        if(src == dst)
            return;

        uint8_t* bsrc = (uint8_t*)src;
        uint8_t* bdst = (uint8_t*)dst;

        for (uint32_t i = 0; i < size; i++)
            bdst[i] = bsrc[i];
        
        
    }

    void Util::memset(void* dst, uint32_t size, uint8_t fill){
        for (uint32_t i = 0; i < size; i++)
            ((uint8_t*)dst)[i] = fill;
    }

    void Util::memsetw(void* dst, uint32_t size, uint16_t fill) {
        for (uint32_t i = 0; i < size; i++)
            ((uint16_t*)dst)[i] = fill;
    }

    void* Util::memmove(void *dst_void, const void *src_void, size_t length) {
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
    }

}}