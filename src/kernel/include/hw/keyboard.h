#ifndef OS_KERNEL_HW_COMM_KEYBOARD_H
#define OS_KERNEL_HW_COMM_KEYBOARD_H

#include "../com/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../io/terminal.h"
#include "../mm/memorymanagement.h"


#include "keymap.h"
#include "keyboardeventhandler.h"

extern "C" void keyboard_handler(regs* r);

#define KEYBOARD_IRQ_ID 1

namespace OS { namespace KERNEL { namespace HW_COMM {


    class Keyboard {
    private:
        static Keyboard* s_Instance;
        KeyboardEventHandler* m_KeyboardEventHandler;
    public:
        Keyboard();
        ~Keyboard();
        
        static Keyboard* getInstance();

        void handler(regs* registers);
        void install();
        void uninstall();
    };

    

}}}

#endif