#ifndef OS_KERNEL_GUI_DESKTOP_H
#define OS_KERNEL_GUI_DESKTOP_H

#include "window.h"
#include "../hardware/vga.h"
#include "../hardware/keyboard.h"

#include "../../../libc++/vector.h"


namespace OS { namespace KERNEL { namespace GUI { 

    class Desktop : public Widget {
    private:
        HW_COMM::VGA* m_VGA;
        std::vector<Window*> m_Windows;

        Window* m_ActiveWindow;
        
    public:

        Desktop();
        ~Desktop();

        void OnKeyDown(char key);

        void draw();

    };

}}}

#endif