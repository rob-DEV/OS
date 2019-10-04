#include "../include/gui/desktop.h"
#include "../include/cpu/pit.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    

    Desktop::Desktop() :Widget(0,0,320,200, 43, NULL){
       
        m_VGA = HW_COMM::VGA::getInstance();
        //m_VGA->setMode(m_W, m_H, 8);

        //register with keyboard
        HW_COMM::KeyboardEventHandler::getInstance()->subscribe(this);

        m_Windows.push_back(new Window("Test window 1", 10, 20, 200,125, 56, this));
        m_Windows.push_back(new Window("Test window 2", 80, 100, 200,125, 34, this));
        m_Windows.push_back(new Window("Test window 3", 180, 70, 200,125, 3, this));


        m_ActiveWindow = m_Windows[0];
        m_LastActiveWindow = NULL;

        for (size_t i = 0; i < m_Windows.size(); i++)
                m_RenderOrder.push_back(m_Windows[i]);

        


    }

    Desktop::~Desktop() {
        OS::KERNEL::Terminal::getInstance()->printf("Desktop: Destructor Called!\n");
    }


    void Desktop::onKeyDown(unsigned char key) {

        if(key == '1' || key == '2' || key == '3') {

            if(key == '1')
                m_ActiveWindow = m_Windows[0];
            if(key == '2') 
                m_ActiveWindow = m_Windows[1];

            if(key == '3') 
                m_ActiveWindow = m_Windows[2];

        }





    }

    void Desktop::draw() {
    
        m_VGA->fillRectangle(m_X,m_Y, m_W, m_H, 43);
        m_VGA->fillRectangle(0,0, m_W, 10, 27);
        
        /*
        const char* desktopHeader = "OS Desktop Test 320x200";
        uint8_t a = 0;
        for (size_t i = 0; i < strlen(desktopHeader); i++)
        {
            m_VGA->drawChar8((a * 8),7,desktopHeader[i],0);
            a++;
        }
        
        */
        drawing = true;
        
        

        if(m_LastActiveWindow != m_ActiveWindow){
            //lock active window to frame
            Window* currentActiveWindow = m_ActiveWindow;
            uint32_t windowToErase = 0;
            for (size_t i = 0; i < m_RenderOrder.size(); i++)
            {
                if(currentActiveWindow == m_RenderOrder[i]) {
                    windowToErase = i;
                    m_LastActiveWindow =currentActiveWindow;
                    break;
                }
            }

            m_RenderOrder.erase(windowToErase, 1);
            m_RenderOrder.push_front(currentActiveWindow);
            
        }

        for (size_t i = 0; i < m_RenderOrder.size(); i++)
        {
            OS::KERNEL::Terminal::getInstance()->printf("DRAWING WINDOW %s\n", m_RenderOrder[i]->m_Name);
            OS::KERNEL::CPU::PIT::getInstance()->waitForMilliSeconds(800);
            m_RenderOrder[i]->draw();

        }
        

        //OS::KERNEL::Terminal::getInstance()->printf("sIZE %d Top Window = %s\n", m_RenderOrder.size(), m_RenderOrder[0]->m_Name);

        drawing = false;
    
        m_VGA->swapBuffers();

    }

} } }

