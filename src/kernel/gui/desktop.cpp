#include "../include/gui/desktop.h"

namespace  OS { namespace KERNEL { namespace GUI {
 

    

    Desktop::Desktop() :Widget(0,0,320,200, 43, NULL){
       
        m_VGA = HW_COMM::VGA::getInstance();
        m_VGA->setMode(m_W, m_H, 8);

    }

    Desktop::~Desktop() {
        
    }


    void Desktop::OnKeyDown(char key) {
        m_VGA->drawChar8(10,10, key, 32);
    }

    void Desktop::draw() {
        m_VGA->fillRectangle(m_X,m_Y, m_W, m_H, 43);

        m_VGA->swapBuffers();
    }

} } }

