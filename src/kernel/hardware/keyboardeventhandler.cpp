#include "../include/hardware/keyboardeventhandler.h"
#include "../include/hardware/keyboard.h"
#include "../include/shell/shell.h"


namespace OS { namespace KERNEL { namespace HW_COMM {

    KeyboardEventHandler* KeyboardEventHandler::m_Instance = NULL;
    
    KeyboardEventHandler::KeyboardEventHandler() {

    }

    KeyboardEventHandler::~KeyboardEventHandler() {

    }

    KeyboardEventHandler* KeyboardEventHandler::getInstance() {
        if(m_Instance == NULL)
            m_Instance = new KeyboardEventHandler();

        return m_Instance;
    }

    void KeyboardEventHandler::OnKeyUp(char key) {
    }
    
    void KeyboardEventHandler::OnKeyDown(char key) {
        SHELL::Shell::getInstance()->onKeyDown(KB_US[key]); 
    }



 }}}

