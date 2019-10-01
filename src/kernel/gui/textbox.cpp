#include "../include/gui/textbox.h"
#include "../include/io/terminal.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    Textbox::Textbox() : Widget() {

    }
    
    Textbox::Textbox(const char* initial, uint32_t x, uint32_t y, uint32_t w, uint32_t h) : Widget(x,y,w,h, 0xA7, NULL) {
        m_strLen = strlen(initial);
        m_BufferLength = m_strLen +1;
        m_Buffer = new char[m_BufferLength];

        memcpy((void*)initial, m_Buffer, m_BufferLength - 1);
        m_Buffer[m_BufferLength - 1] = 0;
    }
    
    Textbox::~Textbox() {
        
    }

    void Textbox::clear() {
        
    }

    void Textbox::draw() {

        int a = 0;
        int b = 0;


        for (size_t i = 0; i < m_strLen; i++)
        {
            if(m_Buffer[i] == '\n') {
                a++;
                b = 0;
                continue;
            }
            OS::KERNEL::HW_COMM::VGA::getInstance()->drawChar8(m_X+ (b * 8) +1 , m_Y + (a * 8), m_Buffer[i], 62);
            b++;
            
        }
        
        
    }


} } }

