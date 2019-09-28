#include "../include/gui/window.h"
#include "../include/io/terminal.h"

namespace OS { namespace KERNEL { namespace GUI {


    Window::Window() {
        xOldPos = 0;
        yOldPos = 0;
        xPos = 0;
        yPos = 0;
        width = 0;
        height = 0;

    }
    Window::Window(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
        xOldPos = x;
        yOldPos = x;
        xPos = x;
        yPos = y;
        width = w;
        height = h;

    }

    Window::~Window() {

    }

    void Window::draw() {
        
        OS::KERNEL::HW_COMM::VGA* vga = OS::KERNEL::HW_COMM::VGA::getInstance();
        OS::KERNEL::Terminal::getInstance()->printf("Window: x,y,w,h - %d %d %d %d\n", xPos, yPos, width, height);
        
        /*if(xPos > xOldPos || yPos > yOldPos) {
            //remove old window - moving to bottom right
            vga->fillRectangle(xOldPos, yOldPos, xPos-xOldPos, yPos + yOldPos, 255,255,255);
            vga->fillRectangle(xOldPos, yOldPos, yPos+yOldPos, xPos - xOldPos, 255,255,255);
        
        }*/
        
        //draw new window
        vga->fillRectangle(xPos, yPos, width, height, 0, 0, 255);

        xOldPos = xPos;
        yOldPos = yPos;

    }


} } }