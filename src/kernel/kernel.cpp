#include "include/kernel.h"
#include "include/io/terminal.h"

#include "../libc++/vector.h"



namespace OS { namespace KERNEL {

    void Kernel::kernel_init(multiboot_info_t* mbi, uint32_t magic) {
        
        
        
        //migrate stack managed memory to full heap based memory
        //small inital manage to allocate the actual manager onto the heap
        {
            MEMORY::MemoryManager stackMemoryVolatile(mbi->mem_lower, mbi->mem_lower + 500);

            //750 mb for heap
            uint32_t start = (mbi->mem_upper * 1024) - (MEM_SIZE);
            m_Memory = new MEMORY::MemoryManager(start, mbi->mem_upper * 1024);
            
            Terminal::getInstance()->print("LOG: Initalizing Kernel...\n");
            Terminal::getInstance()->print("LOG: Memory Management Initialized!\n");


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

        m_VGA = HW_COMM::VGA::getInstance();
        //m_VGA->setMode(320, 200, 8);
        //m_VGA->fillRectangle(0,0, 320, 200, 0xFF,0xFF,0xFF);
        
        //HW_COMM::Mouse* mouse = HW_COMM::Mouse::getInstance();
        
        //mouse->drawCursor();
        //mouse->install();
        
        //GUI::Window* window = new GUI::Window(45, 45, 10, 10);
        //GUI::Window* window2 = new GUI::Window(130, 90, 10, 10);

        //m_VGA->fillRectangle(150, 50, 10,10,120,20,80);
        //m_VGA->fillRectangle(160, 70, 10,10,120,20,80);

        GUI::WindowManager* windowManager = new GUI::WindowManager();
        //windowManager->addWindow(window); 
        //windowManager->addWindow(window2);

    
  
        std::vector<int*> asd;

        asd.push_back(new int(32));
        asd.push_back(new int(45));
        asd.push_back(new int(46));
        asd.push_back(new int(3772));
        asd.push_back(new int(333));
        //asd.push_back(new int(46));
        //asd.push_back(new int(56));
        //asd.push_back(new int(4756));
        //asd.push_back(new int(46));
        
        for (size_t i = 0; i < asd.size(); i++)
        {
            m_Terminal->printf("asd[%d] %d\n", i, *asd[i]);
        }
        

        for(;;);
        

        for (size_t i = 0; i < windowManager->m_Windows.size(); i++)
        {
            Terminal::getInstance()->printf("Window %d : 0x%x\n", i, windowManager->m_Windows[i]);
        }

        windowManager->addWindow(new GUI::Window(10,10,10,10));
        windowManager->addWindow(new GUI::Window(10,20,10,10));
        windowManager->addWindow(new GUI::Window(10,30,10,10));
        windowManager->addWindow(new GUI::Window(10,40,10,10));
        windowManager->addWindow(new GUI::Window(10,50,10,10));
        windowManager->addWindow(new GUI::Window(10,60,10,10));
        windowManager->addWindow(new GUI::Window(10,70,10,10));
        windowManager->addWindow(new GUI::Window(10,80,10,10));
        windowManager->addWindow(new GUI::Window(20,80,10,10));

        Terminal::getInstance()->printf("Window Count%d\n", windowManager->m_Windows.size());

        for (size_t i = 0; i < windowManager->m_Windows.size(); i++)
        {
            Terminal::getInstance()->printf("Window %d : 0x%x\n", i, windowManager->m_Windows[i]);
        }
        
        
        
        uint32_t a = 50;
        while(1) {

            //update VGA
            //update MOUSE
           
            //draw all graphics 
            //windowManager->draw();
    

            if(a > 1)
                a++;
            
            

            //mouse->drawCursor();
            
            
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

