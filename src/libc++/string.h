#pragma once

#ifndef LIB_CPP_STRING_H
#define LIB_CPP_STRING_H

#include "../kernel/include/com/string.h"
#include "../kernel/include/io/terminal.h"

namespace std {

	class string{
    private:
        char* m_CString;
        size_t m_Length;

    public:
        inline string() {};
        inline string(const char* str) {
            m_Length = strlen(str);
            m_CString = new char[m_Length + 1];

            for (size_t i = 0; i < m_Length; i++)
            {
                m_CString[i] = str[i];
            }
            m_CString[m_Length + 1] = '\0';

            

        };
        inline ~string() {};


        inline const char* c_str() const { return m_CString; };
        
        inline string append(const char* str) { 

            uint32_t addLen = strlen(str);
            char* cpy = new char[m_Length];
            memcpy(m_CString, cpy, m_Length);

            m_CString = new char[m_Length + addLen + 1];
            memcpy(cpy, m_CString, m_Length);
            
            for (size_t i = m_Length; i < m_Length + addLen; i++)
                m_CString[i] = str[i - m_Length];
            
            m_Length += addLen;
            
            m_CString[m_Length + 1] = '\0';
            
        };

        inline int32_t compare(const char* str) {
            return strcmp(this->m_CString, str);
        };
        
        inline const string& operator= (const char* str) { return string(str); };
        inline const string& operator+= (const char* str) { return append(str); };
        inline const int32_t operator == (const char* str) { return compare(str); };


        inline const string& operator= (const string& str) { return string(str.c_str()); };
        inline const string& operator+= (const string& str) { return append(str.c_str()); };
        inline const int32_t operator == (const string& str) { return compare(str.c_str()); };

        inline const char* operator[] (uint32_t i) { return &m_CString[i]; };
        
    };

}

#endif