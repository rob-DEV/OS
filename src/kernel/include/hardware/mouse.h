#ifndef OS_KERNEL_HW_COMM_MOUSE_H
#define OS_KERNEL_HW_COMM_MOUSE_H

#include "../common/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../hardware/port.h"
#include "vga.h"

extern "C" void mouse_handler(regs* r);

#define MOUSE_IRQ_ID 12

namespace OS { namespace KERNEL { namespace HW_COMM {

    class Mouse {
    private:
        uint8_t m_MouseCursorW;
        uint8_t m_MouseCursorH;
        
        char m_MouseX = 0; 
        char m_MouseY = 0;
        
        unsigned char m_MouseCycle = 0;
        uint8_t m_MouseByte[3];
        
        static Mouse* m_Instance;

        void mouseWait(unsigned char a_type);
        char mouseRead();
        void mouseWrite(unsigned char byte);

    public:
        Mouse();
        ~Mouse();
        
        static Mouse* getInstance();

        void drawCursor();

        void handler(regs* registers);
        void install();
        void uninstall();
    };
    
    

}}}

#endif