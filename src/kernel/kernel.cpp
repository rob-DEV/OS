#include "include/kernel.h"


enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

namespace OS { namespace KERNEL {

    void alphaCmd() {
        OS::KERNEL::Terminal::getInstance()->printf("alpha command executed\n");    
    }

    void vga(){
         OS::KERNEL::HW_COMM::VGA::getInstance()->setMode(320, 200, 8);
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

    void Kernel::kernel_main(multiboot_info_t* mbi, uint32_t magic) {

        kernel_init(mbi, magic);

        Shell::getInstance()->addCommand("alpha", alphaCmd);
        Shell::getInstance()->addCommand("vga", vga);
        Shell::getInstance()->addCommand("reboot", reboot);

        m_VGA = HW_COMM::VGA::getInstance();
        //vga();

        m_Terminal->printf("m_VGA Address: 0x%x\n", m_VGA);
       
        
        HW_COMM::Mouse* mouse = HW_COMM::Mouse::getInstance();
        
        mouse->install();
        //mouse->drawCursor();

        m_VGA->fillRectangle(0,0, 320, 14, 4, 76, 9);

        //dodgy menu bar
        m_VGA->fillRectangle(0,0, 32, 14, 0xA8, 0, 0);
        m_VGA->fillRectangle(32,0, 32, 14, 0, 0, 0xA8);
        m_VGA->fillRectangle(64,0, 32, 14, 56, 76, 9);
        m_VGA->fillRectangle(96,0, 32, 14, 78, 5, 78);

        
        
        m_VGA->fillRectangle(0,0, 320, 200, 0xFF,0xFF,0xFF);
        GUI::Window* windowTest = new GUI::Window("Test", 10,20,150,100);

        GUI::Window* windowTest1 = new GUI::Window("PORN", 100, 130,150, 60);
        uint32_t a = 0;
        uint8_t s = 0;
        while(1) {
            //update VGA
            //update MOUSE
            

            /*
            m_VGA->fillRectangle(0,0, 320, 14, 4, 76, 9);

            //dodgy menu bar
            m_VGA->fillRectangle(0,0, 32, 14, 0xA8, 0, 0);
            m_VGA->fillRectangle(32,0, 32, 14, 0, 0, 0xA8);
            m_VGA->fillRectangle(64,0, 32, 14, 56, 76, 9);
            m_VGA->fillRectangle(96,0, 32, 14, 78, 5, 78);
            */
            
            windowTest->draw();
            windowTest1->draw();

            if(a < 255) {
                m_VGA->drawChar8(a+16,a+16,a,s);
                ++a;
                if(s < 64)
                    ++s;
                else
                    s = 0;
            }
            

            m_VGA->swapBuffers();
            
            
            
            //60hz
            m_PIT->waitForMilliSeconds(80);
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

