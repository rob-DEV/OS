#ifndef OS_KERNEL_HW_COMM_KEYBOARDEVENTHANDLER_H
#define OS_KERNEL_HW_COMM_KEYBOARDEVENTHANDLER_H

#include "../../../libc/stdint.h"
#include "keymap.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    typedef struct keyboard_input_packet {

        char keyPressed;
        
        char capsLockKeyPressed;
        char leftShiftKeyPressed;
        char leftCtrlKeyPressed;

    } keyboard_input_packet_t;


    class KeyboardEventSubscriber {
    public:
        inline virtual void onKeyDown(const keyboard_input_packet_t& keyPacket) { }

    };

     
    class KeyboardEventHandler
    {
    private:
        
        uint32_t m_KeyboardEVSubscribers[10];
        uint8_t m_KeyboardEVSubscribersCount = 0;

        static KeyboardEventHandler* s_Instance;
    public:
        KeyboardEventHandler();
        ~KeyboardEventHandler();

        static KeyboardEventHandler* getInstance();

        void subscribe(KeyboardEventSubscriber* subscriber);
        void onKeyUp(char key);
        void onKeyDown(const keyboard_input_packet_t& keyPacket);


    };

}}}

#endif