#ifndef OS_KERNEL_GUI_WIDGET_H
#define OS_KERNEL_GUI_WIDGET_H

#include "../com/type.h"

namespace OS { namespace KERNEL { namespace GUI { 

class Widget {
    public:
        uint32_t m_X, m_Y, m_W, m_H;
    protected:
        uint32_t m_ID;
        
        uint32_t m_XPrev, m_YPrev;
        uint8_t m_Color;

        Widget* m_Parent;

        static uint32_t s_WidgetCount;
    public:

        Widget();
        Widget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color, Widget* parent);
        inline virtual ~Widget();

        inline uint32_t ID() { return m_ID; };

        inline virtual void onKeyDown(unsigned char key) {  };

        inline void getPostion(uint32_t& x, uint32_t& y) { x = m_X; y = m_Y; };
        inline virtual void setPosition(const uint32_t x, const uint32_t y) { m_X = x; m_Y = y; }; 
        inline uint32_t width() { return m_W; };
        inline uint32_t height() { return m_H; };

        inline virtual void draw() {};

};


}}}

#endif