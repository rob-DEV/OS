#include "include/kernel.h"
#include <stdio.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void parse_multiboot_info(uint32_t magic, multiboot_info_t* mbi)
{
    OS::KERNEL::Terminal::getInstance()->printf("Processing Multiboot Information\n");
    //multiboot_info_t* mbi;
    // Am I booted by a Multiboot-compliant boot loader?
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        OS::KERNEL::Terminal::getInstance()->printf("Invalid magic number: %x\n", (unsigned)magic);
        return;
    }
    // Set MBI to the address of the Multiboot information structure.
    //mbi = (multiboot_info_t *)addr;
    // Print out the flags.
    OS::KERNEL::Terminal::getInstance()->printf("Flags = 0x%d\n", (unsigned)mbi->flags);
    // Are mem_* valid?
    if (CHECK_FLAG(mbi->flags, 0))
    {
        OS::KERNEL::Terminal::getInstance()->printf("mem_lower = %d KB, mem_upper = %d KB\n",
                   (unsigned)mbi->mem_lower, (unsigned)mbi->mem_upper);
    }
    // Bits 4 and 5 are mutually exclusive!
    if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5))
    {
        OS::KERNEL::Terminal::getInstance()->printf("Both bits 4 and 5 are set.\n");
        return;
    }
    // Is the symbol table of a.out valid?
    if (CHECK_FLAG(mbi->flags, 4))
    {
        multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);
        OS::KERNEL::Terminal::getInstance()->printf("multiboot_aout_symbol_table: tabsize = 0x%0x, strsize = 0x%x, addr = 0x%x\n",
                   (unsigned)multiboot_aout_sym->tabsize,
                   (unsigned)multiboot_aout_sym->strsize,
                   (unsigned)multiboot_aout_sym->addr);
    }
    // Is the section header table of ELF valid?
    if (CHECK_FLAG(mbi->flags, 5))
    {
        multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);
        OS::KERNEL::Terminal::getInstance()->printf("multiboot_elf_sec: num = %u, size = 0x%x, addr = 0x%x, shndx = 0x%x\n",
                   (unsigned)multiboot_elf_sec->num, (unsigned)multiboot_elf_sec->size,
                   (unsigned)multiboot_elf_sec->addr, (unsigned)multiboot_elf_sec->shndx);
    }
    // Are mmap_* valid?
    if (CHECK_FLAG(mbi->flags, 6))
    {
        multiboot_memory_map_t *mmap;
        OS::KERNEL::Terminal::getInstance()->printf("mmap_addr = 0x%x, mmap_length = 0x%x\n",
                   (unsigned)mbi->mmap_addr, (unsigned)mbi->mmap_length);
        for (mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
             (unsigned long)mmap < mbi->mmap_addr + mbi->mmap_length;
             mmap = (multiboot_memory_map_t *)((unsigned long)mmap + mmap->size + sizeof(mmap->size)))
            OS::KERNEL::Terminal::getInstance()->printf("size = 0x%x, base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
                       (unsigned)mmap->size,
                       (unsigned)(mmap->addr >> 32),
                       (unsigned)(mmap->addr & 0xffffffff),
                       (unsigned)(mmap->len >> 32),
                       (unsigned)(mmap->len & 0xffffffff),
                       (unsigned)mmap->type);
    }
    
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
        //small inital manager to allocate the actual manager onto the heap
        { //destroy stack mm after scope end - migrate to heap
            MEMORY::MemoryManager stackMemoryVolatile(mbi->mem_lower, mbi->mem_lower + 500);

            //750 mb for heap
            uint32_t start = (mbi->mem_upper * 1024) - (MEM_SIZE);
            m_Memory = new MEMORY::MemoryManager(start, mbi->mem_upper * 1024);
            
            kputs("LOG: Initalizing Kernel...\n");
            kprintf("LOG: Memory Management Initialized! start : %x\n", start);


            kprintf("Address STACK MM : 0x%x\n", &stackMemoryVolatile);
            kprintf("Address STACK MM hs : 0x%x\n", stackMemoryVolatile.m_HeapStart);
            kprintf("Address STACK MM he : 0x%x\n", stackMemoryVolatile.m_HeapEnd);
        
        }
        kprintf("Memory Manager Heap Start: 0x%x\n", m_Memory->m_HeapStart);
        kprintf("Memory Manager Heap End: 0x%x\n", m_Memory->m_HeapEnd);
        kprintf("Memory Manager Heap Size: %d(BYTES), %d(MB)\n", m_Memory->m_SizeBytes, m_Memory->m_SizeBytes / (1024 * 1024));
        

        kputs("LOG: Heap Allocating core Kernel components...\n");
        m_GDT = CPU::GDT::getInstance();
        m_IDT = CPU::IDT::getInstance();
        m_IRQ = CPU::IRQ::getInstance();
        m_ISRS = CPU::ISR::getInstance();
        m_PIT = CPU::PIT::getInstance();
        m_Keyboard = HW_COMM::Keyboard::getInstance();
                

        kputs("Installing Global Descriptor Table\n");
        m_GDT->install();
        
        kputs("Installing Interrupt Descriptor Table\n");
        m_IDT->install();

        kputs("Installing Interrupt Service Routines\n");

        m_ISRS->install();

        kputs("Installing Interrupt Request Handler\n");

        m_IRQ->install();

        kputs("Installing Programmable Interval Timer\n");
        m_PIT->install();

        kputs("Waiting...\n");
        m_PIT->waitForMilliSeconds(5000);

        kputs("Installing Keyboard (US)\n");
        m_Keyboard->install();

        ktermsetcolor(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
        kputs("LOG: Kernel Initalized!\n");
        ktermsetcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);


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

        printf("Test apples %f\n", 34.245);
        printf("Test apples %f\n", 34.245);
        kprintf("Macro test %f\n", 34.245);


        printf("Test apples %d\n", 33);
        printf("Test apples %d\n", 32);
        kprintf("Macro test %d\n", 32);

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

