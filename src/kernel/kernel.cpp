#include "include/kernel.h"
#include "include/terminal.h"

namespace OS { namespace KERNEL {

    void Kernel::kernel_init(multiboot_info_t mbi, uint32_t magic) {
        
    }

    void Kernel::kernel_main(multiboot_info_t mbi, uint32_t magic) {

        Terminal term;
        term.init();
        term.print("OS Terminal >>");

        for(;;);
    }

    
}}

