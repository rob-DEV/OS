#ifndef OS_KERNEL_GUI_DESKTOP_H
#define OS_KERNEL_GUI_DESKTOP_H

#include "window.h"
#include "textbox.h"
#include "../hw/vga.h"
#include "../hw/keyboard.h"

#include "../../../libc++/vector.h"
#include "../../../libc++/slow_deque.h"

#define VERBOSE_VGA_DEBUG 0

namespace OS { namespace KERNEL { namespace GUI { 

    class Desktop : public Widget, public HW_COMM::KeyboardEventSubscriber {
    private:

        HW_COMM::VGA* m_VGA;
        

        std::slow_deque<Window*> m_Windows;
        
        Window* m_ActiveWindow;
        Window* m_LastActiveWindow;
    
        char m_FpsBuffer[30];


    public:

        Desktop();
        ~Desktop();

        void onKeyDown(const HW_COMM::keyboard_input_packet_t& packet);

        void draw();

    };

}}}

#endif