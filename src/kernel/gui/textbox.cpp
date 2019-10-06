#include "../include/gui/textbox.h"
#include "../include/io/terminal.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    Textbox::Textbox() : Widget() {

    }
    
    Textbox::Textbox(const char* initial, uint32_t x, uint32_t y, uint32_t w, uint32_t h) : Widget(x,y,w,h, 0xA7, NULL) {
        m_strLen = strlen(initial);
        m_BufferLength = TEXTBOX_MAX_BUFFER_LENGTH;
        m_Buffer = new char[m_BufferLength];

        memcpy((void*)initial, m_Buffer, m_strLen * sizeof(char));
        m_Buffer[m_BufferLength - 1] = 0;
    }
    
    Textbox::~Textbox() {
        delete[] m_Buffer;
    }

    void Textbox::clear() {
        
    }

    void Textbox::appendText(unsigned char key) {
        
        //avoid buffer overflow
        if(m_strLen + 2 > m_BufferLength)
            return;

        if(key == '\b') {

                if(m_strLen == 0)
                    return;
                    
                --m_strLen;
                return;
            }

            m_Buffer[m_strLen] = key;
            m_strLen++;
    }
    
    void Textbox::draw() {

        if(m_strLen < 1)
            return;
            
        int a = 0;
        int b = 0;

        //OS::KERNEL::Terminal::getInstance()->printf("textbox size %d\n", m_strLen);
        for (size_t i = 0; i < m_strLen; i++)
        {

            //wrap around text
            if(((b+1)*8) > m_W) {
                b=0;
                a++;
            }

            if(m_Buffer[i] == '\n') {
                a++;
                b = 0;
                continue;
            }
            OS::KERNEL::HW_COMM::VGA::getInstance()->drawChar8(m_X+ (b * 8) +1 , m_Y + (a * 8), m_Buffer[i], 0);
            b++;
            
        }
        
        
    }


} } }
