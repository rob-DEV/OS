#include "../include/hw/keyboardeventhandler.h"
#include "../include/hw/keyboard.h"
#include "../include/shell/shell.h"


namespace OS { namespace KERNEL { namespace HW_COMM {

    KeyboardEventHandler* KeyboardEventHandler::s_Instance = NULL;
    
    KeyboardEventHandler::KeyboardEventHandler() { 
        m_KeyboardEVSubscribers[10];
        m_KeyboardEVSubscribersCount = 0;
    }

    KeyboardEventHandler::~KeyboardEventHandler() {

    }

    KeyboardEventHandler* KeyboardEventHandler::getInstance() {
        if(s_Instance == NULL)
            s_Instance = new KeyboardEventHandler();

        return s_Instance;
    }

    void KeyboardEventHandler::subscribe(KeyboardEventSubscriber* subscriber) {

        m_KeyboardEVSubscribers[m_KeyboardEVSubscribersCount] = (uint32_t)subscriber;
        ++m_KeyboardEVSubscribersCount;
    }

    void KeyboardEventHandler::onKeyUp(char key) {

    }
    
    void KeyboardEventHandler::onKeyDown(unsigned char key) {
        
        for (size_t i = 0; i < m_KeyboardEVSubscribersCount; i++)
        {
            KeyboardEventSubscriber* kb_sub_ptr = (KeyboardEventSubscriber*)m_KeyboardEVSubscribers[i];
            kb_sub_ptr->onKeyDown(key);
        }
        
    }



 }}}

