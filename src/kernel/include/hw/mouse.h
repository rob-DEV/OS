#ifndef OS_KERNEL_HW_COMM_MOUSE_H
#define OS_KERNEL_HW_COMM_MOUSE_H

#include "../com/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../hw/port.h"
#include "vga.h"

extern "C" void mouse_handler(regs_t* r);

#define MOUSE_IRQ_ID 12

namespace OS { namespace KERNEL { namespace HW_COMM {

    class Mouse {
    private:
        static Mouse* s_Instance;
        

        uint8_t buffer[3];
        uint8_t offset;
        uint8_t buttons;
        

    public:
        Mouse();
        ~Mouse();
        
        int16_t m_MouseX = 0; 
        int16_t m_MouseY = 0;
        void OnMouseDown();
        void OnMouseUp();
        void OnMouseMove(int32_t x, int32_t y);

        static Mouse* getInstance();
        
        void handler(regs_t* registers);
        void install();
        void uninstall();


    };
    
    

}}}

#endif