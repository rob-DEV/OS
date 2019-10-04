#include "../include/shell/shell.h"

namespace OS { namespace KERNEL { namespace SHELL {

    Shell* Shell::s_Instance = NULL;

    Shell::Shell() { 
        m_BufferLength = 0;
        m_GraphicsModeEntered = false;
        nLines = 1;

        m_Desktop = NULL;

        //subscribe to keyboard handler
        HW_COMM::KeyboardEventHandler::getInstance()->subscribe(this);

        OS::KERNEL::Terminal::getInstance()->printf("Shell Initialized!\n");
        SHELL_PRINT_HEADER;
    }

    Shell::~Shell() {

    }
    
    Shell* Shell::getInstance() { 
        if(s_Instance == NULL)
            s_Instance = new Shell();

        return s_Instance;
    }

    

    void Shell::onKeyDown(char c) {
        //only hold line for now
        //pass char to video memory if not in graphics mode
        
        if(m_GraphicsModeEntered) {
            m_Desktop->OnKeyDown(c);
            return;
        }       

        if(c != '\n') {
            Terminal::getInstance()->print(c);
        }
        else {

            Terminal::getInstance()->print("\n");
            SHELL_PRINT_HEADER;
            nLines++;

        }
        if(c != '\n') {
            m_Buffer[m_BufferLength] = c;
            m_BufferLength++;
            return;
        }else if(c == '\b') {
            if(m_BufferLength != 0)
                m_BufferLength--;
        }
        else {
            m_Buffer[m_BufferLength] = '\0';

            //check the commands
            
            checkRegisteredCommands();

            //reset the buffer length for a new line
            m_BufferLength = 0;
        }

        

    }

    void Shell::addCommand(const char* cmdText, void(*callback)()) {
        m_Commands.push_back(new ShellCommand(cmdText, callback));
    }

    void Shell::checkRegisteredCommands() {

        for (size_t i = 0; i < m_Commands.size(); i++)
            if(strcmp(m_Commands[i]->commandText, m_Buffer))
                m_Commands[i]->execute();
        
    }

    void Shell::enterGraphicsMode() {

        //create desktop and pass shell input to it
        m_Desktop = new GUI::Desktop();

        OS::KERNEL::Terminal::getInstance()->printf("Desktop 0x%x\n", m_Desktop);

        m_GraphicsModeEntered = true;
        

    }
    

    };
}}
