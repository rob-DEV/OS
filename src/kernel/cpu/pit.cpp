#include "../include/cpu/pit.h"

void timer_handler(regs* registers){
    OS::KERNEL::CPU::PIT::getInstance()->handler(registers);
}
#define INPUT_CLOCK_FREQUENCY 1193180
#define TARGET_FREQUENCY 100
#define TIMER_COMMAND 0x43
#define TIMER_DATA 0x40
#define TIMER_ICW 0x36


clock_t clock() {

    OS::KERNEL::CPU::PIT::getInstance()->getTicks();

}



namespace OS { namespace KERNEL { namespace CPU {

    PIT* PIT::s_Instance = NULL;

    PIT::PIT() {
        //set PIT frequency
        uint16_t hz = 1000;
        uint16_t divisor = INPUT_CLOCK_FREQUENCY / hz;
        // Init, Square Wave Mode, non-BCD, first transfer LSB then MSB
        HW_COMM::Port::outportb(TIMER_COMMAND, TIMER_ICW);
        HW_COMM::Port::outportb(TIMER_DATA, divisor & 0xFF);
        HW_COMM::Port::outportb(TIMER_DATA, (divisor >> 8) & 0xFF);
    }

    PIT::~PIT() {

    }
    
    PIT* PIT::getInstance() {
        if(s_Instance == NULL)
            s_Instance = new PIT();

        return s_Instance;
    }

    void PIT::handler(regs* registers) {
        /* Increment our 'tick count' */
        m_Ticks++;

        /* Every 18 clocks (approximately 1 second), we will
        *  display a message on the screen */
        if (m_Ticks % 18 == 0)
        {
            //Terminal::getInstance()->printf("%d\n", m_Ticks);
        }
    }

    void PIT::install() {
        OS::KERNEL::CPU::IRQ::getInstance()->irq_install(0, timer_handler);
    }

    uint32_t PIT::getTicks() {
        return m_Ticks;
    }

    void PIT::waitForMilliSeconds(uint32_t milliseconds) {
        
        unsigned int targetTicks = m_Ticks + (18 * (float)milliseconds / 1000);
        while(m_Ticks < targetTicks);
        //Terminal::getInstance()->printf("Waited for %d milliseconds!\n", milliseconds);
    }

}}}
