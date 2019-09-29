#ifndef OS_KERNEL_GUI_WINDOW_H
#define OS_KERNEL_GUI_WINDOW_H

#include "../common/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../hardware/port.h"
#include "../hardware/vga.h"
#include "widget.h"

#include "../../../libc++/vector.h"

namespace  OS { namespace KERNEL { namespace GUI {
 
    class Window : public Widget {
    
    private:
        const char* m_Name;
        std::vector<Widget*> m_Widgets;
    public:
        Window();
        Window(const char* name, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Window();

        void addWidget(Widget* component);

        void draw();

    };


} } }

#endif