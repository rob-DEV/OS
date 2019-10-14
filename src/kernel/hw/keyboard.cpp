#include "../include/hw/keyboard.h"

uint8_t shift = 0;
uint8_t caps = 0;


void keyboard_handler(regs* registers){
    OS::KERNEL::HW_COMM::Keyboard::getInstance()->handler(registers);
}

namespace OS { namespace KERNEL { namespace HW_COMM {

    Keyboard* Keyboard::s_Instance = NULL;

    Keyboard::Keyboard() {
        m_KeyboardEventHandler = KeyboardEventHandler::getInstance();
    }
    
    Keyboard::~Keyboard() {
        delete m_KeyboardEventHandler;
    }
        
    Keyboard* Keyboard::getInstance() {
        if(s_Instance == NULL)
            s_Instance = new Keyboard();

        return s_Instance;
    }

    void Keyboard::handler(regs* registers) {
        char scancode;

        scancode = HW_COMM::Port::inportb(0x60);

        switch(scancode) {
            case KEY_SHIFT_LEFT:
                shift = 1;
                break;
            case KEY_SHIFT_RIGHT:
                shift = 1;
                break;
            case KEY_SHIFT_LEFT_RELEASE:
            case KEY_SHIFT_RIGHT_RELEASE:
                shift = 0;
                break;
            case KEY_CAPSLOCK:
                if(caps > 0)    caps = 0;
                else   caps = 1;
                break;
            default:
            
            if(scancode < 0) return;
            
            char ch;
            if(shift || caps)   ch = KB_US_UPPER[scancode];
            else    ch = KB_US_LOWER[scancode];
            

            if(!(scancode & 0x80)) {
                //build keyboard input packet
                keyboard_input_packet_t packet;
                packet.keyPressed = ch;
                packet.leftShiftKeyPressed = shift;

                //pass key packet to all event subscribers
                m_KeyboardEventHandler->onKeyDown(packet);
            }
        }
        
    }

    void Keyboard::install() {
        OS::KERNEL::CPU::IRQ::getInstance()->irq_install(KEYBOARD_IRQ_ID, keyboard_handler);
    }

    void Keyboard::uninstall() {
        OS::KERNEL::CPU::IRQ::getInstance()->irq_uninstall(1);
    }

}}}