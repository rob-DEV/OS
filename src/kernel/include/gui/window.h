#ifndef OS_KERNEL_GUI_WINDOW_H
#define OS_KERNEL_GUI_WINDOW_H

#include "widget.h"
#include "textbox.h"
#include "../hw/vga.h"

#include "../../../libc++/vector.h"

namespace  OS { namespace KERNEL { namespace GUI {
 
    class Window : public Widget {
    
    private:
        std::vector<Widget*> m_Widgets;
    public:

        Window();
        Window(const char* name, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color, Widget* parent);
        ~Window();

        Widget* m_FocusedWidget;

        const char* m_Name;
        void addWidget(Widget* component);

        void setPosition(const uint32_t x, const uint32_t y);
        void onKeyDown(unsigned char key);
        void draw();

    };


} } }

#endif