#include "include/kernel.h"

namespace OS { namespace KERNEL {

    void alphaCmd() {
        OS::KERNEL::Terminal::getInstance()->printf("alpha command executed\n");    
    }

    void reboot() {
         OS::KERNEL::Terminal::getInstance()->printf("Shutting down\n");    
    }

    void Kernel::kernel_init(multiboot_info_t* mbi, uint32_t magic) {
        
        
        
        //migrate stack managed memory to full heap based memory
        //small inital manage to allocate the actual manager onto the heap
        {
            MEMORY::MemoryManager stackMemoryVolatile(mbi->mem_lower, mbi->mem_lower + 500);

            //750 mb for heap
            uint32_t start = (mbi->mem_upper * 1024) - (MEM_SIZE);
            m_Memory = new MEMORY::MemoryManager(start, mbi->mem_upper * 1024);
            
            Terminal::getInstance()->print("LOG: Initalizing Kernel...\n");
            Terminal::getInstance()->printf("LOG: Memory Management Initialized! start : %x\n", start);


            Terminal::getInstance()->printf("Address STACK MM : 0x%x\n", &stackMemoryVolatile);
            Terminal::getInstance()->printf("Address STACK MM hs : 0x%x\n", stackMemoryVolatile.m_HeapStart);
            Terminal::getInstance()->printf("Address STACK MM he : 0x%x\n", stackMemoryVolatile.m_HeapEnd);
        
        }
        Terminal::getInstance()->printf("Memory Manager Heap Start: 0x%x\n", m_Memory->m_HeapStart);
        Terminal::getInstance()->printf("Memory Manager Heap End: 0x%x\n", m_Memory->m_HeapEnd);
        Terminal::getInstance()->printf("Memory Manager Heap Size: %d(BYTES), %d(MB)\n", m_Memory->m_SizeBytes, m_Memory->m_SizeBytes / (1024 * 1024));
        
        

        m_Terminal = Terminal::getInstance();
        m_Terminal->print("LOG: Heap Allocating core Kernel components...\n");
        //TODO: make it work
        m_GDT = CPU::GDT::getInstance();
        m_IDT = CPU::IDT::getInstance();
        m_IRQ = CPU::IRQ::getInstance();
        m_ISRS = CPU::ISR::getInstance();
        m_PIT = CPU::PIT::getInstance();
        m_Keyboard = HW_COMM::Keyboard::getInstance();
        

        m_Terminal->printf("m_GDT Address: 0x%x\n", m_GDT);
        m_Terminal->printf("m_IDT Address: 0x%x\n", m_IDT);
        m_Terminal->printf("m_IRQ Address: 0x%x\n", m_IRQ);
        m_Terminal->printf("m_ISRS Address: 0x%x\n", m_ISRS);
        m_Terminal->printf("m_PIT Address: 0x%x\n", m_PIT);
        m_Terminal->printf("m_Keyboard Address: 0x%x\n", m_Keyboard);
                

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

        m_Terminal->print("Installing Keyboard (US)\n");
        m_Keyboard->install();

        m_Terminal->setColor(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
        m_Terminal->print("LOG: Kernel Initalized!\n");
        m_Terminal->setColor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    
    }

    void enterVGAStub() {
        SHELL::Shell::getInstance()->enterGraphicsMode();
    }
    void Kernel::kernel_main(multiboot_info_t* mbi, uint32_t magic) {

        kernel_init(mbi, magic);

        SHELL::Shell::getInstance()->addCommand("alpha", alphaCmd);


        SHELL::Shell::getInstance()->addCommand("vga", enterVGAStub);
        SHELL::Shell::getInstance()->addCommand("reboot", reboot);

        m_VGA = HW_COMM::VGA::getInstance();
       
        
        HW_COMM::Mouse* mouse = HW_COMM::Mouse::getInstance();

        
        
        m_VGA->fillRectangle(0,0, 320, 200, 64,0xFF,0xFF);
        GUI::Window* bar = new GUI::Window("OS Kernel - VGA 320x200", 0,0,320,12, 24, NULL);
        GUI::Window* windowTest = new GUI::Window("Test Window", 50,40,150,100, 35, NULL);


        GUI::Window* windowTest1 = new GUI::Window("Second Window", 100, 130,150, 60,42, NULL);
        windowTest->addWidget(new GUI::Textbox("Inital text in the\ntext box\n", 10, 40, 100,100));
        windowTest->addWidget(new GUI::Textbox("Inital t box\n", 10, 60, 100,100));
        windowTest1->addWidget(new GUI::Textbox("NIGGER!\n", 100,148, 10,60));
        windowTest1->addWidget(new GUI::Textbox("NIGGER2!\n", 100,168, 10,60));
        
        for(;;);
    }

    //Entrypoint for the OS called from the assembly code
    extern "C" void kmain(multiboot_info_t* mbi, uint32_t magic) {
        
        KERNEL::Kernel kernel;
        kernel.kernel_main(mbi, magic);
        return;

    }

    
}}

