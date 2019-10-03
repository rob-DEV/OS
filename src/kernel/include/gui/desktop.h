#ifndef OS_KERNEL_GUI_DESKTOP_H
#define OS_KERNEL_GUI_DESKTOP_H

#include "window.h"
#include "../hw/vga.h"
#include "../hw/keyboard.h"

#include "../../../libc++/vector.h"
#include "../../../libc++/slow_deque.h"



namespace OS { namespace KERNEL { namespace GUI { 

    class Desktop : public Widget {
    private:

        HW_COMM::VGA* m_VGA;


        std::vector<Window*> m_Windows;
        std::slow_deque<Window*> m_RenderOrder;
        
        Window* m_ActiveWindow;
        Window* m_LastActiveWindow;
        
    public:

        Desktop();
        ~Desktop();

        void OnKeyDown(char key);

        void draw();

    };

}}}

#endif