#include "include/kernel.h"
#include "include/video.h"

namespace OS { namespace KERNEL {

    void Kernel::test_main() {
        Video video;
        video.clear();
        video.write("Hello World! from C++ Kernel");

        for(;;);
    }
}}

