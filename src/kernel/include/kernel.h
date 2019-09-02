#include "common/multiboot.h"
#include "common/string.h"
#include "memory/gdt.h"
#include "terminal/terminal.h"

namespace OS { namespace KERNEL {

    class Kernel {

    private:
        MEMORY::GDT m_GDT;
        Terminal m_Terminal;
        void kernel_init(multiboot_info_t mbi, uint32_t magic);

    public:
        void kernel_main(multiboot_info_t mbi, uint32_t magic);

    };
}}