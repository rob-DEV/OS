#include "../include/hw/keyboard.h"

void keyboard_handler(regs* registers){
    OS::KERNEL::HW_COMM::Keyboard::getInstance()->handler(registers);
}

namespace OS { namespace KERNEL { namespace HW_COMM {

    Keyboard* Keyboard::m_Instance = NULL;

    Keyboard::Keyboard() {
        m_KeyboardEventHandler = KeyboardEventHandler::getInstance();
    }
    
    Keyboard::~Keyboard() {
        delete m_KeyboardEventHandler;
    }
        
    Keyboard* Keyboard::getInstance() {
        if(m_Instance == NULL)
            m_Instance = new Keyboard();

        return m_Instance;
    }

    void Keyboard::handler(regs* registers) {
        unsigned char scancode;

        scancode = HW_COMM::Port::inportb(0x60);

        if (scancode & 0x80)
        {
            /* You can use this one to see if the user released the
            *  shift, alt, or control keys... */
        }
        else
        {
            m_KeyboardEventHandler->onKeyDown(scancode);
        }
    }

    void Keyboard::install() {
        OS::KERNEL::CPU::IRQ::getInstance()->irq_install(KEYBOARD_IRQ_ID, keyboard_handler);
    }

    void Keyboard::uninstall() {
        OS::KERNEL::CPU::IRQ::getInstance()->irq_uninstall(1);
    }

}}}