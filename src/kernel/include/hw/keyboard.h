#ifndef OS_KERNEL_HW_COMM_KEYBOARD_H
#define OS_KERNEL_HW_COMM_KEYBOARD_H

#include "../com/type.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"
#include "../io/terminal.h"
#include "../mem/memorymanagement.h"


#include "keyboardeventhandler.h"

extern "C" void keyboard_handler(regs* r);

#define KEYBOARD_IRQ_ID 1

namespace OS { namespace KERNEL { namespace HW_COMM {


    class Keyboard {
    private:
     const unsigned char KB_US[128] = {
                0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
            '9', '0', '-', '=', '\b',	/* Backspace */
            '\t',			/* Tab */
            'q', 'w', 'e', 'r',	/* 19 */
            't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
                0,			/* 29   - Control */
            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
            '\'', '`',   0,		/* Left shift */
            '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
            'm', ',', '.', '/',   0,				/* Right shift */
            '*',
                0,	/* Alt */
            ' ',	/* Space bar */
                0,	/* Caps lock */
                0,	/* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,	/* < ... F10 */
                0,	/* 69 - Num lock*/
                0,	/* Scroll Lock */
                0,	/* Home key */
                0,	/* Up Arrow */
                0,	/* Page Up */
            '-',
                0,	/* Left Arrow */
                0,
                0,	/* Right Arrow */
            '+',
                0,	/* 79 - End key*/
                0,	/* Down Arrow */
                0,	/* Page Down */
                0,	/* Insert Key */
                0,	/* Delete Key */
                0,   0,   0,
                0,	/* F11 Key */
                0,	/* F12 Key */
                0,	/* All other keys are undefined */
            };	
       
        static Keyboard* m_Instance;
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