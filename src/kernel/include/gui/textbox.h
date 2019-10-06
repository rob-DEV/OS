#ifndef OS_KERNEL_GUI_TEXTBOX_H
#define OS_KERNEL_GUI_TEXTBOX_H

#include "../com/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../hw/port.h"
#include "../hw/vga.h"
#include "widget.h"

#include "../../../libc++/vector.h"

#define TEXTBOX_MAX_BUFFER_LENGTH (m_W * m_H) / (float)8

namespace  OS { namespace KERNEL { namespace GUI {
 
    class Textbox : public Widget {
    
    private:
        char* m_Buffer;
        uint32_t m_strLen;
        uint32_t m_BufferLength;
        std::vector<Widget*> m_Widgets;
    public:
        Textbox();
        Textbox(const char* initalText, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Textbox();

        
        void clear();
        void appendText(unsigned char key);
        
        void draw();

    };


} } }

#endif