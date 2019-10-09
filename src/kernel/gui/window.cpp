#include "../include/gui/window.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    Window::Window() : Widget() {

    }
    
    Window::Window(const char* name, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color, Widget* parent) : Widget(x,y,w,h, color, parent), m_Name(name) {

    }
    
    Window::~Window() {
        
    }

    void Window::addWidget(Widget* component) {
        component->m_X += m_X;
        component->m_Y += m_Y + 8;

        m_Widgets.push_back(component);

        if(m_Widgets.size() > 0)
            m_FocusedWidget = m_Widgets[0];

    }

    void Window::setPosition(const uint32_t x, const uint32_t y) { 

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
    void Window::onKeyDown(unsigned char key) {

        if(m_FocusedWidget != NULL)
            m_FocusedWidget->onKeyDown(key);

        }

    void Window::draw() {

        //draw window header above window
        uint8_t windowHeaderHeight = 10;

        HW_COMM::VGA::getInstance()->fillRectangle(m_X, m_Y - windowHeaderHeight, m_W, windowHeaderHeight, 0,23,45);

        for (size_t i = 0; i < strlen(m_Name); i++)
            HW_COMM::VGA::getInstance()->drawChar8(m_X + ( 8 * i),m_Y - 2, m_Name[i], 63);

        //draw window

        HW_COMM::VGA::getInstance()->fillRectangle(m_X, m_Y, m_W, m_H, m_Color,23,45);

        
        for (size_t i = 0; i < m_Widgets.size(); i++)
            m_Widgets[i]->draw();
        
        
    }


} } }

