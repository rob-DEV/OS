#ifndef OS_KERNEL_IO_SHELLCOMMAND_H
#define OS_KERNEL_IO_SHELLCOMMAND_H

namespace OS { namespace KERNEL { namespace SHELL { 

    class ShellCommand {
    private:
        void (*callback)();
        int (*args_callback)(const char * args);

    public:
        const char * commandText;
          
        ShellCommand(const char * cmdText, void(*callback)()) {

            commandText = cmdText;
            this->callback = callback;
        
        };

        ShellCommand(const char * cmdText, int(*callback)(const char* args)) {

            commandText = cmdText;
            this->args_callback = callback;
        
        };
        
        ~ShellCommand() {};

        inline void execute() { callback(); };

    };

} } }

#endif