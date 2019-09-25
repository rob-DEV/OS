#include "include/kernel.h"
#include "include/io/terminal.h"

namespace OS { namespace KERNEL {

    void Kernel::kernel_init(multiboot_info_t* mbi, uint32_t magic) {
        
        //migrate stack managed memory to full heap based memory
        MEMORY::MemoryManager stackMemoryVolatile(mbi->mem_lower, mbi->mem_upper * 1024);
        Terminal::getInstance()->printf("Address STACK MM : 0x%x\n", &stackMemoryVolatile);

        m_Memory = (MEMORY::MemoryManager*)stackMemoryVolatile.malloc(sizeof(MEMORY::MemoryManager));
        m_Memory = new MEMORY::MemoryManager(mbi->mem_lower + 100, mbi->mem_upper * 1024);
        

        Terminal::getInstance()->printf("Address HEAP MM : 0x%x\n", m_Memory);        


        m_Terminal = Terminal::getInstance();
        
        m_Terminal->printf("0x%x terminal\n", m_Terminal);

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

        m_Terminal->print("Installing Keyboard (US)\n");
        m_Keyboard->install();

        m_Terminal->setColor(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
        m_Terminal->print("LOG: Kernel Initalized\b\b\b\b\b\btest\n");
        m_Terminal->setColor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    
    }

    void Kernel::kernel_main(multiboot_info_t* mbi, uint32_t magic) {

        kernel_init(mbi, magic);
        
        m_VGA = HW_COMM::VGA::getInstance();
        m_VGA->setMode(320, 200, 8);
        m_VGA->fillRectangle(0,0, 320, 200, 0xFF,0xFF,0xFF);
        
        HW_COMM::Mouse* mouse = HW_COMM::Mouse::getInstance();
        
        mouse->drawCursor();
        mouse->install();
        
        GUI::Window* window = new GUI::Window(50, 50, 100, 70);

        uint32_t a = 50;
        while(1) {

            //update VGA
            //update MOUSE

            window->draw();

            window->xPos = a;
            window->yPos = a;
            
            if(a > 1)
                a--;
            

            mouse->drawCursor();
            
            
            //60hz
            m_PIT->waitForMilliSeconds(1000 / 60);

        }

        for(;;);
    }

    //Entrypoint for the OS called from the assembly code
    extern "C" void kmain(multiboot_info_t* mbi, uint32_t magic) {
        
        KERNEL::Kernel kernel;
        kernel.kernel_main(mbi, magic);
        return;

    }
}}

