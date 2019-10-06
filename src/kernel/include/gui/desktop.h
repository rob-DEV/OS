#ifndef OS_KERNEL_GUI_DESKTOP_H
#define OS_KERNEL_GUI_DESKTOP_H

#include "window.h"
#include "textbox.h"
#include "../hw/vga.h"
#include "../hw/keyboard.h"

#include "../../../libc++/vector.h"
#include "../../../libc++/slow_deque.h"



namespace OS { namespace KERNEL { namespace GUI { 

    class Desktop : public Widget, public HW_COMM::KeyboardEventSubscriber {
    private:

        HW_COMM::VGA* m_VGA;
        

        std::slow_deque<Window*> m_Windows;
        
        Window* m_ActiveWindow;
        Window* m_LastActiveWindow;
    
        uint32_t m_renderDraws;
    public:

        Desktop();
        ~Desktop();

        void onKeyDown(unsigned char);

        void draw();

    };

}}}

#endif