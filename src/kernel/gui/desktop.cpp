#include "../include/gui/desktop.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    

    Desktop::Desktop() :Widget(0,0,320,200, 43, NULL){
       
        m_VGA = HW_COMM::VGA::getInstance();
        m_VGA->setMode(m_W, m_H, 8);

        m_Windows.push_back(new Window("Test window 1", 10, 10, 200,125, 56, this));
        m_Windows.push_back(new Window("Test window 2", 80, 100, 200,125, 34, this));

        m_ActiveWindow = m_Windows[1];

    }

    Desktop::~Desktop() {
        OS::KERNEL::Terminal::getInstance()->printf("Desktop: Destructor Called!\n");
    }


    void Desktop::OnKeyDown(char key) {


        OS::KERNEL::Terminal::getInstance()->print(key);
        if(key == '1')
            m_ActiveWindow = m_Windows[0];
        
        if(key == '2') 
            m_ActiveWindow = m_Windows[1];




    }

    void Desktop::draw() {
    
        m_VGA->fillRectangle(m_X,m_Y, m_W, m_H, 43);

        for (size_t i = 0; i < m_Windows.size(); i++)
        {
            m_Windows[i]->draw();
        }

        m_ActiveWindow->draw();
        

        m_VGA->swapBuffers();

    }

} } }

