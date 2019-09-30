#ifndef OS_KERNEL_GUI_TEXTBOX_H
#define OS_KERNEL_GUI_TEXTBOX_H

#include "../common/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../hardware/port.h"
#include "../hardware/vga.h"
#include "widget.h"

#include "../../../libc++/vector.h"

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

        void draw();

    };


} } }

#endif