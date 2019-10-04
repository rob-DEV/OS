#ifndef OS_KERNEL_SHELL_SHELL_H
#define OS_KERNEL_SHELL_SHELL_H


#include "shellcommand.h"
#include "../gui/desktop.h"
#include "../cpu/pit.h"


#include "../../../libc++/vector.h"

namespace OS { namespace KERNEL { namespace SHELL {


    #define SHELL_PRINT_HEADER OS::KERNEL::Terminal::getInstance()->printf("kernel>")
    class Shell : public HW_COMM::KeyboardEventSubscriber {
    
    private:
        static Shell* s_Instance;
        std::vector<ShellCommand*> m_Commands;

        char m_Buffer[256];
        uint16_t m_BufferLength;
        uint32_t nLines;
        bool m_GraphicsModeEntered;

        
        
    public:
        Shell();
        ~Shell();

        void onKeyDown(char c);
        void addCommand(const char* cmdText, void(*callback)());
        void checkRegisteredCommands();

        GUI::Desktop* m_Desktop;
        void enterGraphicsMode();

        static Shell* getInstance();

       


    };
}}}

#endif