#ifndef OS_KERNEL_IO_SHELL_H
#define OS_KERNEL_IO_SHELL_H


#include "../common/type.h"


namespace OS { namespace KERNEL {

    class Shell {
    
    private:

        static Shell* m_Instance;

        
    public:
        Shell();
        ~Shell();

        static Shell* getInstance();

       


    };
}}

#endif