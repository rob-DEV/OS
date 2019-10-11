#include <sys.h>

#include <vector.h>
#include <string.h>
#include <slow_deque.h>


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


    public:
        void kernel_main(multiboot_info_t* mbi, uint32_t magic);

    };
}}