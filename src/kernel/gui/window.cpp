#include "../include/gui/window.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    Window::Window() : Widget() {

    }
    
    Window::Window(const char* name, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color, Widget* parent) : Widget(x,y,w,h, color, parent), m_Name(name) {

    }
    
    Window::~Window() {
        
    }

    void Window::addWidget(Widget* component) {
        m_Widgets.push_back(component);
    }

    void Window::draw() {

        HW_COMM::VGA::getInstance()->fillRectangle(m_X, m_Y, m_W, m_H, m_Color,23,45);

        for (size_t i = 0; i < strlen(m_Name); i++)
        {
            HW_COMM::VGA::getInstance()->drawChar8(m_X + ( 8 * i),m_Y + 8, m_Name[i], 63);
        }

        for (size_t i = 0; i < m_Widgets.size(); i++)
        {
            m_Widgets[i]->draw();
        }
        
    }


} } }

