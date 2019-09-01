//#include "include/kernel.h"
//#include <iostream>

#include "include/video.h"

namespace OS {

    //Entrypoint for the OS called from the assembly code
    int main() {
        //dummy main for vscode
        //TODO: Remove
        return 0;
    }
    //int kmain(multiboot_info_t*mbi, uint32_t magic_number) {
    extern "C" void kmain(void) {

        /*std::cout << "HELLO FROM KERNEL" << std::endl;

        KERNEL::Kernel kernel;

        kernel.kernel_main(mbi, magic_number);
        */
        Video video;
        video.clear();
        video.write("Hello World! from C++ Kernel");
        
        for(;;);

        return;
    }
}
