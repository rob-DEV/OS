#include "include/kernel.h"
#include "include/video.h"

namespace OS { namespace KERNEL {

    void Kernel::kernel_init(multiboot_info_t mbi, uint32_t magic) {
        
    }

    void Kernel::kernel_main(multiboot_info_t mbi, uint32_t magic) {

        Video video;
        video.clear();
        

        const char* a = "TEST";

        char b[5] = "jjjj";

        memcpy((void*)a, &b, 4);
        
        video.write((char*)a);
        video.write(b);
        video.put('a');
        video.write("Hello World! from C++ Kernel");

        for(;;);
    }
}}

