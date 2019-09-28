#include "common/multiboot.h"
#include "common/string.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/isr.h"
#include "cpu/irq.h"
#include "cpu/pit.h"
#include "memory/memorymanagement.h"
#include "io/terminal.h"
#include "shell/shell.h"
#include "hardware/keyboard.h"
#include "hardware/vga.h"
#include "hardware/mouse.h"
#include "gui/window.h"
#include "gui/windowmanager.h"

#define MEM_SIZE 750 * 1024 * 1024
#define KERNEL_PAUSE for(;;)


namespace OS { namespace KERNEL {
    using namespace SHELL;

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

    public:
        void kernel_main(multiboot_info_t* mbi, uint32_t magic);

    };
}}