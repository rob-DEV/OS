#include "com/multiboot.h"
#include "com/string.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/irq.h"
#include "cpu/pit.h"
#include "mem/memorymanagement.h"
#include "io/terminal.h"
#include "shell/shell.h"
#include "gui/window.h"
#include "gui/textbox.h"
#include "hw/keyboard.h"
#include "hw/vga.h"
#include "hw/mouse.h"


#include "../../libc++/vector.h"
#include "../../libc++/string.h"


#define MEM_SIZE 750 * 1024 * 1024
#define KERNEL_PAUSE for(;;)



namespace OS { namespace KERNEL {

    class Kernel {

    private:
        MEMORY::MemoryManager* m_Memory;
        CPU::GDT* m_GDT;
        CPU::IDT* m_IDT;
        CPU::ISR* m_ISRS;
        CPU::IRQ* m_IRQ;
        CPU::PIT* m_PIT;

        HW_COMM::VGA* m_VGA;

        HW_COMM::Keyboard* m_Keyboard;

        Terminal* m_Terminal;

        void kernel_init(multiboot_info_t* mbi, uint32_t magic);
        void vga();

    public:
        void kernel_main(multiboot_info_t* mbi, uint32_t magic);

    };
}}