#ifndef OS_KERNEL_GUI_WINDOW_H
#define OS_KERNEL_GUI_WINDOW_H

#include "../common/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../hardware/port.h"
#include "../hardware/vga.h"
#include "widget.h"

namespace  OS { namespace KERNEL { namespace GUI {
 
    class Window : public Widget {
    private:
        uint32_t s_NWindows = 0;
        uint32_t m_ID;
    public:
        uint32_t xOldPos;
        uint32_t yOldPos;

        uint32_t xPos;
        uint32_t yPos;

        uint32_t width;
        uint32_t height;

        uint8_t color;

        Window();
        Window(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Window();

        const uint32_t getID() const;
        void draw();

    };


} } }

#endif