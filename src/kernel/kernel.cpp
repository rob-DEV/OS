#include "include/kernel.h"
#include "include/io/terminal.h"

namespace OS { namespace KERNEL {

    void Kernel::kernel_init(multiboot_info_t mbi, uint32_t magic) {
 
        MEMORY::MemoryManager memoryManagment(mbi.mem_lower, mbi.mem_upper - mbi.mem_lower);
        
        m_Terminal.setColor(vga_color::VGA_COLOR_WHITE, vga_color::VGA_COLOR_BLACK);

        m_Terminal.print("LOG: Initalizing Kernel...\n");
        

        m_Terminal.print("Installing Global Descriptor Table\n");
        m_GDT.install();
        
        m_Terminal.print("Installing Interrupt Descriptor Table\n");
        m_IDT.install();

        m_Terminal.print("Installing Interrupt Service Routines\n");
        
        CPU::ISR::terminalAddress = (uint32_t)&m_Terminal;

        m_ISRS.idt = &m_IDT;
        m_ISRS.install();

        m_Terminal.print("Mem Test\n");
       
    

        //exception test
        //int a = a / 0;

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

