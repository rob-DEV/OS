#include "../include/gui/widget.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    uint32_t Widget::s_WidgetCount = 0;

    Widget::Widget() : m_ID(s_WidgetCount), m_X(0), m_Y(0), m_W(0), m_H(0), m_Parent(NULL) { 
        s_WidgetCount++; 
    }

    
    Widget::Widget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color, Widget* parent) 
        : m_ID(s_WidgetCount), m_X(x), m_Y(y), m_W(w), m_H(h), m_Color(color), m_Parent(parent) { 
            s_WidgetCount++; 
    }

    
    
    Widget::~Widget() {
        
    }


} } }

