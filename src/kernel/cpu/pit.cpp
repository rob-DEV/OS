#include "../include/cpu/pit.h"

void timer_handler(regs* registers){
    OS::KERNEL::CPU::PIT::getInstance()->handler(registers);
}

namespace OS { namespace KERNEL { namespace CPU {

    PIT* PIT::m_Instance = NULL;

    PIT::PIT() {

    }

    PIT::~PIT() {

    }
    
    PIT* PIT::getInstance() {
        if(m_Instance == NULL)
            m_Instance = new PIT();

        return m_Instance;
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

    void PIT::waitForMilliSeconds(uint32_t milliseconds) {
        
        unsigned int targetTicks = m_Ticks + (18 * (float)milliseconds / 1000);
        while(m_Ticks < targetTicks);
        //Terminal::getInstance()->printf("Waited for %d milliseconds!\n", milliseconds);
    }

}}}
