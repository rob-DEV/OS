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

        //set cursor to intially flash
        m_CursorFlash = 0;
    }
    
    Textbox::~Textbox() {
        delete[] m_Buffer;
    }

    void Textbox::clear() {
        m_strLen = 0;
    }

    void Textbox::onKeyDown(unsigned char key) {
        //validate if character is printable
        printable_string_t outPrint;
        
        GuiUtils::validatePrintableCharacter(key, outPrint);
        
        appendText(outPrint);

    }

    void Textbox::appendText(const printable_string_t& key) {
        
        //avoid buffer overflow
        if(m_strLen + 2 > m_BufferLength)
            return;

        for (size_t i = 0; i < key.stream_len; i++)
        {
            if(key.stream[i] == KEY_BACKSPACE) {

                //test
                //remove four spaces in one go
                if(m_Buffer[m_strLen -1] == ' ' &&m_Buffer[m_strLen - 2] == ' ' && m_Buffer[m_strLen - 3] == ' ' &&m_Buffer[m_strLen - 4] == ' ' ) {
                    m_strLen -= 4;
                    return;
                }

                if(m_strLen == 0)
                    continue;
                    
                --m_strLen;
                continue;
            }


            m_Buffer[m_strLen] = key.stream[i];
            m_strLen++;
        }
        
        
    }
    
    void Textbox::draw() {

        if(m_strLen < 1)
            return;

        int a = 0;
        int b = 0;

        
        //make a copy of strlen to avoid it updating during the frame
        uint32_t strlenToDraw = m_strLen;
        
        for (size_t i = 0; i < strlenToDraw; i++)
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

        if(m_CursorFlash % 8 == 0)
            OS::KERNEL::HW_COMM::VGA::getInstance()->fillRectangle(m_X+ (b * 8) +1 , m_Y - 6 + (a * 8), 1, 8, 0);     
        
        m_CursorFlash++;
    }


} } }
