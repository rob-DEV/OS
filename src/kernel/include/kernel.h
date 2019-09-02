#include "common/multiboot.h"
#include "common/string.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "memory/memorymanagement.h"
#include "output/terminal.h"

namespace OS { namespace KERNEL {

    class Kernel {

    private:
        CPU::GDT m_GDT;
        CPU::IDT m_IDT;
        CPU::ISR m_ISRS;
        
        Terminal m_Terminal;
        void kernel_init(multiboot_info_t mbi, uint32_t magic);

    public:
        void kernel_main(multiboot_info_t mbi, uint32_t magic);

    };
}}