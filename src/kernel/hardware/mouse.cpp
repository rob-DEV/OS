#include "../include/hardware/mouse.h"
#include "../include/io/terminal.h"

void mouse_handler(regs* registers){
    OS::KERNEL::HW_COMM::Mouse::getInstance()->handler(registers);
}


namespace OS { namespace KERNEL { namespace HW_COMM {

    Mouse* Mouse::m_Instance = NULL;

    Mouse::Mouse() {
        
    }
    
    Mouse::~Mouse() {

    }

    Mouse* Mouse::getInstance() {
        
         if(m_Instance == NULL) 
            m_Instance = new Mouse();
        
        //Terminal::getInstance()->printf("MOUSE ADDRESS: 0x%x\n", MEMORY::MemoryManager::Instance);

        return m_Instance;
    }

    void Mouse::mouseWait(unsigned char a_type) {
        uint32_t _time_out=100000; //unsigned int
        if(a_type==0)
        {
            while(_time_out--) //Data
                if((HW_COMM::Port::inportb(0x64) & 1)==1)
                    return;
            return;
        }
        else
        {
            while(_time_out--) //Signal
                if((HW_COMM::Port::inportb(0x64) & 2)==0)
                    return;
            return;
        }
    }

    char Mouse::mouseRead() {
        mouseWait(0);
        return HW_COMM::Port::inportb(0x60);
    }

    void Mouse::mouseWrite(unsigned char byte) {
        //Wait to be able to send a command
        mouseWait(1);
        //Tell the mouse we are sending a command
        HW_COMM::Port::outportb(0x64, 0xD4);
        //Wait for the final part
        mouseWait(1);
        //Finally write
        HW_COMM::Port::outportb(0x60, byte);
    }

    void Mouse::drawCursor() {
        

        uint32_t curW = 1;
        uint32_t curH = 8;

        Terminal::getInstance()->printf("Drawing Mouse(%d,%d)\n", m_MouseX, m_MouseY);

        //draw a simple cross at mouse x and y
        VGA* vga = VGA::getInstance();

        //vert
        vga->fillRectangle(m_MouseX, (m_MouseY-(curH / 2)), curW, curH, 18, 40, 80);

        //horizontal
        vga->fillRectangle((m_MouseX - (curH / 2) + curW), m_MouseY - curW, curH, curW, 18, 40, 80);
        
    }

    void Mouse::handler(regs* reg) { 
        switch(m_MouseCycle)
        {
            
            case 0:
            m_MouseByte[0] = HW_COMM::Port::inportb(0x60);
            m_MouseCycle++;
            break;
            case 1:
            m_MouseByte[1] = HW_COMM::Port::inportb(0x60);
            m_MouseCycle++;
            break;
            case 2:
            m_MouseByte[2]= HW_COMM::Port::inportb(0x60);
            m_MouseX += m_MouseByte[1] % 10;
            m_MouseY += m_MouseByte[2] % 10;
            m_MouseCycle = 0;
            break;
        }
    }

    void Mouse::install() {

        unsigned char _status;  //unsigned char

        /*
        //Enable the auxiliary mouse device
        mouseWait(1);
        HW_COMM::Port::outportb(0x64, 0xA8);
        
        //Enable the interrupts
        mouseWait(1);
        HW_COMM::Port::outportb(0x64, 0x20);
        mouseWait(0);
        _status=(HW_COMM::Port::inportb(0x60) | 2);
        mouseWait(1);
        HW_COMM::Port::outportb(0x64, 0x60);
        mouseWait(1);
        HW_COMM::Port::outportb(0x60, _status);
        
        //Tell the mouse to use default settings
        mouseWrite(0xF6);
        mouseRead();  //Acknowledge
        
        //Enable the mouse
        mouseWrite(0xF4);
        mouseRead();  //Acknowledge

        //Setup the mouse handler
        OS::KERNEL::CPU::IRQ::getInstance()->irq_install(MOUSE_IRQ_ID, mouse_handler);
        */
    }

    void Mouse::uninstall() {

    }

}}}