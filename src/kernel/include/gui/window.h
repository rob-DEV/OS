#ifndef OS_KERNEL_GUI_WINDOW_H
#define OS_KERNEL_GUI_WINDOW_H

#include "widget.h"
#include "../hw/vga.h"

#include "../../../libc++/vector.h"

namespace  OS { namespace KERNEL { namespace GUI {
 
    class Window : public Widget {
    
    private:
        const char* m_Name;
        std::vector<Widget*> m_Widgets;
    public:
        Window();
        Window(const char* name, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color, Widget* parent);
        ~Window();

        void addWidget(Widget* component);
        inline void setPosition(const uint32_t x, const uint32_t y) { 

            m_XPrev = m_X;
            m_YPrev = m_Y;
            m_X = x;
            m_Y = y;
            for (size_t i = 0; i < m_Widgets.size(); i++)
            {
                //title bar height
                uint32_t  yOffset = y + 16;
                m_Widgets[i]->setPosition((m_X - m_XPrev) + x, (m_Y - m_YPrev) + yOffset);
            }
            

        }

        void draw();

    };


} } }

#endif