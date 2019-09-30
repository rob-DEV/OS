#ifndef OS_KERNEL_IO_SHELL_H
#define OS_KERNEL_IO_SHELL_H


#include "../common/type.h"
#include "../common/string.h"
#include "../../../libc++/vector.h"
#include "shellcommand.h"
#include "../gui/widget.h"

namespace OS { namespace KERNEL { namespace SHELL {

    class Shell {
    
    private:
        static Shell* s_Instance;
        std::vector<ShellCommand*> m_Commands;

        char m_Buffer[256];
        uint16_t m_BufferLength;
        uint32_t nLines;
        GUI::Widget* focusedWindow;
        
    public:
        Shell();
        ~Shell();

        void putchar(char c);
        void addCommand(const char* cmdText, void(*callback)());
        void checkRegisteredCommands();

        inline void registerWidget(GUI::Widget* widget) { focusedWindow = widget; };

        static Shell* getInstance();

       


    };
}}}

#endif