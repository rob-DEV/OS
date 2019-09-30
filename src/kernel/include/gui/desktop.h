#ifndef OS_KERNEL_GUI_DESKTOP_H
#define OS_KERNEL_GUI_DESKTOP_H

#include "window.h"
#include "../hardware/keyboard.h"

#include "../../../libc++/vector.h"


namespace OS { namespace KERNEL { namespace GUI { 

class Desktop : Widget {




    private:
        HW_COMM::Keyboard* m_Keyboard;
        std::vector<Window*> m_Windows;





    public:
        Desktop();
        ~Desktop();

};


}}}

#endif