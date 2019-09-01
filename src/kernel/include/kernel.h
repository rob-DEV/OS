#ifndef OS_ARCH_MULTIBOOT_H
#define OS_ARCH_MULTIBOOT_H

#include "multiboot.h"

namespace OS { namespace KERNEL {

    class Kernel {
        private:
        void kernel_init(multiboot_info_t* mbi, uint32_t magic);

        public:
        int kernel_main(multiboot_info_t* mbi, uint32_t magic); 


    };
}}

#endif