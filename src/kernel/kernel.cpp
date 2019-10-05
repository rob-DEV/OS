#include "include/kernel.h"


static void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	OS::KERNEL::HW_COMM::Port::outportb(0x43, 0xb6);
 	OS::KERNEL::HW_COMM::Port::outportb(0x42, (uint8_t) (Div) );
 	OS::KERNEL::HW_COMM::Port::outportb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = OS::KERNEL::HW_COMM::Port::inportb(0x61);
  	if (tmp != (tmp | 3)) {
 		OS::KERNEL::HW_COMM::Port::outportb(0x61, tmp | 3);
 	}
 }
 
 //make it shutup
 static void nosound() {
 	uint8_t tmp = OS::KERNEL::HW_COMM::Port::inportb(0x61) & 0xFC;
 
 	OS::KERNEL::HW_COMM::Port::outportb(0x61, tmp);
 }
 
 //Make a beep
 void beep() {
 	play_sound(349);
     OS::KERNEL::CPU::PIT::getInstance()->waitForMilliSeconds(300);
     nosound();
    play_sound(466);
    OS::KERNEL::CPU::PIT::getInstance()->waitForMilliSeconds(300);
     nosound();
    play_sound(587);
    OS::KERNEL::CPU::PIT::getInstance()->waitForMilliSeconds(300);
     nosound();
    play_sound(783);
    OS::KERNEL::CPU::PIT::getInstance()->waitForMilliSeconds(300);
     nosound();
    play_sound(698);
 	OS::KERNEL::CPU::PIT::getInstance()->waitForMilliSeconds(300);
     nosound();
    
 	nosound();
    //set_PIT_2(old_frequency);
 }


namespace OS { namespace KERNEL {

    void alphaCmd() {
        OS::KERNEL::Terminal::getInstance()->printf("alpha command executed\n");    
    }

    void reboot() {
         OS::KERNEL::Terminal::getInstance()->printf("Rebooting...\n"); 
         CPU::PIT::getInstance()->waitForMilliSeconds(300);   
    }

    void Kernel::kernel_init(multiboot_info_t* mbi, uint32_t magic) {
        
        
        
        //migrate stack managed memory to full heap based memory
        //small inital manage to allocate the actual manager onto the heap
        { //destroy stack mm after scope end - migrate to heap
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
        SHELL::Shell::getInstance()->addCommand("beep", beep);

        m_VGA = HW_COMM::VGA::getInstance();


        std::slow_deque<int> ints;

        ints.push_back(1);
        ints.push_back(2);
        ints.push_back(3);
        ints.push_back(4);

        ints.clear();

        ints.push_back(34);
        ints.push_back(37);
        ints.push_back(38);
        ints.push_front(100);

        for (size_t i = 0; i < ints.size(); i++)
        {
            m_Terminal->printf("ints[%d] = %d\n", i, ints[i]);
        }
        

        while(true) {
            beep();
        }

        while(1) {

            if(SHELL::Shell::getInstance()->m_Desktop) 
                SHELL::Shell::getInstance()->m_Desktop->draw();

            m_PIT->waitForMilliSeconds(1000/60);
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

