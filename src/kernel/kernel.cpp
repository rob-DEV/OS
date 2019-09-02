#include "include/kernel.h"
#include "include/terminal/terminal.h"
#include "include/memory/gdt.h"

namespace OS { namespace KERNEL {

    void Kernel::kernel_init(multiboot_info_t mbi, uint32_t magic) {

        m_Terminal.setColor(vga_color::VGA_COLOR_WHITE, vga_color::VGA_COLOR_BLACK);
        m_Terminal.print("LOG: Initalizing Kernel...\n");
        

        m_Terminal.print("Installing Global Descriptor Table\n");
        m_GDT.install();

        m_Terminal.print("LOG: Kernel Initalized\n");
        

    }

    void Kernel::kernel_main(multiboot_info_t mbi, uint32_t magic) {

        kernel_init(mbi, magic);
        
        for(;;);
    }

    //Entrypoint for the OS called from the assembly code
    extern "C" void kmain(multiboot_info_t mbi, uint32_t magic) {
        
        KERNEL::Kernel kernel;
        kernel.kernel_main(mbi, magic);
        return;

    }
}}

