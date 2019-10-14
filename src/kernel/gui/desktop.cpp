#include "../include/gui/desktop.h"
#include "../include/cpu/pit.h"

namespace  OS { namespace KERNEL { namespace GUI {
 
    Desktop::Desktop() :Widget(0,0,320,200, 43, NULL){
       
        m_VGA = HW_COMM::VGA::getInstance();
        #if !VERBOSE_VGA_DEBUG
        m_VGA->setMode(m_W, m_H, 8);
        #endif
        //register with keyboard
        HW_COMM::KeyboardEventHandler::getInstance()->subscribe(this);

        m_Windows.push_back(new Window("0 Window with textbox", 20, 20, 200,125, 4, this));

        m_Windows[0]->addWidget(new Textbox("a",0,0, 200, 125));

                  
       
    
        m_ActiveWindow = new Window("9 Window with textbox", 10, 90, 200,125, 6, this);
        m_ActiveWindow->addWidget(new Textbox("TEST TEXT", 0,0, 200,125));


        m_LastActiveWindow = m_ActiveWindow;        
        m_Windows.push_back(m_ActiveWindow);
        
        #if VERBOSE_VGA_DEBUG
        OS::KERNEL::Terminal::getInstance()->printf("allocated window count %d \n", m_Windows.size());
        #endif
        
        m_FpsBuffer[30];
        for (size_t i = 0; i < 30; i++)
            m_FpsBuffer[i] = 0;
        


    }

    Desktop::~Desktop() {
        OS::KERNEL::Terminal::getInstance()->printf("Desktop: Destructor Called!\n");
    }


    void Desktop::onKeyDown(const HW_COMM::keyboard_input_packet_t& packet) {
        
        
        m_ActiveWindow->onKeyDown(packet.keyPressed);
        
        //used for switching windows
        if(packet.keyPressed == KEY_ESCAPE) {

            m_ActiveWindow = m_Windows[0];

        }





    }

    void Desktop::draw() {


        clock_t start = clock();
        #if VERBOSE_VGA_DEBUG
        //OS::KERNEL::Terminal::getInstance()->printf("Destop::draw() begin\n");
        #endif

        m_VGA->fillRectangle(m_X,m_Y, m_W, m_H, 43);
        m_VGA->fillRectangle(0,0, m_W, 10, 27);
        
                
        
        Window* topWindow = m_ActiveWindow;
        uint32_t windowToErase = NULL;
        if(m_LastActiveWindow != topWindow) {
            //find active window erase it and push back
            for (size_t i = 0; i < m_Windows.size(); i++)
            {
                if(m_Windows[i] == topWindow) {
                    windowToErase = i;
                    m_LastActiveWindow = topWindow;
                    break;
                }
            }

            m_Windows.erase(windowToErase, 0);
            m_Windows.push_back(topWindow);

        }

        //push window data to buffer
        for (size_t i = 0; i < m_Windows.size(); i++) {
            
            m_Windows[i]->draw();
            

        }

        const char* desktopHeader = "OS Kernel v0.1";
        uint8_t a = 0;
        for (size_t i = 0; i < strlen(desktopHeader); i++)
        {
            m_VGA->drawChar8((a * 8),7,desktopHeader[i],0);
            a++;
        }



        //TICKS IN ONE FRAME
        clock_t end = clock();

        uint32_t frameDurationTicks = end - start;
        uint32_t frames = 1000 / (float)frameDurationTicks;

        //FPS DEBUG HANDLER
        Util::itoa(frames, m_FpsBuffer);
        
        m_VGA->drawChar8(150,7,m_FpsBuffer[0] ,0);
        m_VGA->drawChar8(150 + 8,7,m_FpsBuffer[1] ,0);
        m_VGA->drawChar8(150 + 8,7,m_FpsBuffer[2] ,0);
        
        
        //buffers must be swapped las to render fps counter
        m_VGA->swapBuffers();
        
        //OS::KERNEL::Terminal::getInstance()->printf("Clock ticks %d\n", 1000 / (end - start));
        
    }

} } }

