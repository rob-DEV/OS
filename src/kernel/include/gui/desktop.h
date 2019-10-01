#ifndef OS_KERNEL_GUI_DESKTOP_H
#define OS_KERNEL_GUI_DESKTOP_H

#include "widget.h"
#include "../hardware/vga.h"
#include "../hardware/keyboard.h"

//#include "../../../libc++/vector.h"


namespace OS { namespace KERNEL { namespace GUI { 

    class Desktop : public Widget {
    private:
        HW_COMM::VGA* m_VGA;
        //OS::KERNEL::HW_COMM::Keyboard* m_Keyboard;
    public:

        Desktop();
        ~Desktop();

        void OnKeyDown(char key);

        void draw();

    };

}}}

#endif