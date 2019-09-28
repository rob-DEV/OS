#include "../include/gui/windowmanager.h"

namespace OS { namespace KERNEL { namespace GUI { 

   
        WindowManager::WindowManager() {
        
        }

        WindowManager::~WindowManager() {

        }

        void WindowManager::addWindow(Window* window) {
            m_Windows.push_back(window);
        }

        void WindowManager::removeWindow() {

        }

        void WindowManager::draw() {

            for (size_t i = 0; i < m_Windows.size(); i++) {
                if(m_Windows[i] != NULL)
                    m_Windows[i]->draw();
            }
            

        }

};


}}