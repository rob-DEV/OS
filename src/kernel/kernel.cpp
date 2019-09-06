#include "include/kernel.h"
#include "include/io/terminal.h"

class TestClass {
public:
    const char* test;
    int a;

    TestClass(const char * d) {
        test = d;
        a = 54634;
    }

};

namespace OS { namespace KERNEL {

    void Kernel::kernel_init(multiboot_info_t* mbi, uint32_t magic) {
 
        MEMORY::MemoryManager memoryManagment(mbi->mem_lower, mbi->mem_upper * 1024);
        
        m_Terminal = Terminal::getInstance();

        m_GDT = CPU::GDT::getInstance();
        m_IDT = CPU::IDT::getInstance();
        m_IRQ = CPU::IRQ::getInstance();
        m_ISRS = CPU::ISR::getInstance();
        m_PIT = CPU::PIT::getInstance();


        m_Terminal->printf("m_GDT Address: 0x%x\n", m_GDT);
        m_Terminal->printf("m_IDT Address: 0x%x\n", m_IDT);
        m_Terminal->printf("m_IRQ Address: 0x%x\n", m_IRQ);
        m_Terminal->printf("m_ISRS Address: 0x%x\n", m_ISRS);
        m_Terminal->printf("m_PIT Address: 0x%x\n", m_PIT);

                
        m_Terminal->print("LOG: Initalizing Kernel...\n");
        

        m_Terminal->print("Installing Global Descriptor Table\n");
        m_GDT->install();
        
        m_Terminal->print("Installing Interrupt Descriptor Table\n");
        m_IDT->install();

        m_Terminal->print("Installing Interrupt Service Routines\n");

        m_ISRS->install();

        m_Terminal->print("Installing Interrupt Request Handler\n");

        m_IRQ->install();

        m_Terminal->print("Installing Programmable Interval Timer\n");
        m_PIT->install();



        m_Terminal->setColor(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
        m_Terminal->print("LOG: Kernel Initalized\b\b\b\b\b\btest\n");
        m_Terminal->setColor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    }

    void Kernel::kernel_main(multiboot_info_t* mbi, uint32_t magic) {

        kernel_init(mbi, magic);
        
        for(;;);
    }

    //Entrypoint for the OS called from the assembly code
    extern "C" void kmain(multiboot_info_t* mbi, uint32_t magic) {
        
        KERNEL::Kernel kernel;
        kernel.kernel_main(mbi, magic);
        return;

    }
}}

