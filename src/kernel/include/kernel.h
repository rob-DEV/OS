#include "multiboot.h"
#include "string.h"

namespace OS { namespace KERNEL {

    class Kernel {

    private:
        void kernel_init(multiboot_info_t mbi, uint32_t magic);

    public:
        void kernel_main(multiboot_info_t mbi, uint32_t magic);

    };
}}