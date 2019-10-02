#include "../include/hw/mouse.h"
#include "../include/io/terminal.h"

void mouse_handler(regs* registers){
    OS::KERNEL::HW_COMM::Mouse::getInstance()->handler(registers);
}

unsigned char mouse_cycle=0;     //unsigned char
char mouse_byte[3];    //signed char
char mouse_x=0;         //signed char
char mouse_y=0;         //signed char


void mouse_wait(unsigned char a_type) //unsigned char
{
  uint32_t _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((OS::KERNEL::HW_COMM::Port::inportb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((OS::KERNEL::HW_COMM::Port::inportb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(unsigned char a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  OS::KERNEL::HW_COMM::Port::outportb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  OS::KERNEL::HW_COMM::Port::outportb(0x60, a_write);
}

unsigned char mouse_read()
{
  //Get's response from mouse
  mouse_wait(0);
  return OS::KERNEL::HW_COMM::Port::inportb(0x60);
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



    void Mouse::install() {
        char _status;  //unsigned char

        //Enable the auxiliary mouse device
        mouse_wait(1);
        OS::KERNEL::HW_COMM::Port::outportb(0x64, 0xA8);
        
        //Enable the interrupts
        mouse_wait(1);
        OS::KERNEL::HW_COMM::Port::outportb(0x64, 0x20);
        mouse_wait(0);
        _status=(OS::KERNEL::HW_COMM::Port::inportb(0x60) | 2);
        mouse_wait(1);
        OS::KERNEL::HW_COMM::Port::outportb(0x64, 0x60);
        mouse_wait(1);
        OS::KERNEL::HW_COMM::Port::outportb(0x60, _status);
        
        //Tell the mouse to use default settings
        mouse_write(0xF6);
        mouse_read();  //Acknowledge
        
        //Enable the mouse
        mouse_write(0xF4);
        mouse_read();  //Acknowledge

        //Setup the mouse handler
        OS::KERNEL::CPU::IRQ::getInstance()->irq_install(MOUSE_IRQ_ID, mouse_handler);  
    }

    void Mouse::handler(regs* registers) {

        switch(mouse_cycle)
        {
            case 0:
            mouse_byte[0]=OS::KERNEL::HW_COMM::Port::inportb(0x60);
            mouse_cycle++;
            break;
            case 1:
            mouse_byte[1]=OS::KERNEL::HW_COMM::Port::inportb(0x60);
            mouse_cycle++;
            break;
            case 2:
            mouse_byte[2]=OS::KERNEL::HW_COMM::Port::inportb(0x60);
            mouse_x=mouse_byte[1];
            mouse_y=mouse_byte[2];


            mouse_cycle=0;
            break;
        }

        OS::KERNEL::Terminal::getInstance()->printf("X: %d Y:%d\n", mouse_x, mouse_y);
        
    }
    

}}}