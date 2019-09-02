//#include "include/kernel.h"
//#include <iostream>

#include "include/kernel.h"

namespace OS {


    //Entrypoint for the OS called from the assembly code
    //int kmain(multiboot_info_t*mbi, uint32_t magic_number) {
    extern "C" void kmain(multiboot_info_t mbi, uint32_t magic) {
        
        KERNEL::Kernel kernel;
        kernel.kernel_main(mbi, magic);
        return;

    }


}
