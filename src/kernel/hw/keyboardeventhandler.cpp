#include "../include/hw/keyboardeventhandler.h"
#include "../include/hw/keyboard.h"
#include "../include/shell/shell.h"


namespace OS { namespace KERNEL { namespace HW_COMM {

    KeyboardEventHandler* KeyboardEventHandler::m_Instance = NULL;
    
    KeyboardEventHandler::KeyboardEventHandler() { 
        m_KeyboardEVSubscribers[10];
        m_KeyboardEVSubscribersCount = 0;
    }

    KeyboardEventHandler::~KeyboardEventHandler() {

    }

    KeyboardEventHandler* KeyboardEventHandler::getInstance() {
        if(m_Instance == NULL)
            m_Instance = new KeyboardEventHandler();

        return m_Instance;
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

