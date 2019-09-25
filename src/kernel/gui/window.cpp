#include "../include/gui/window.h"

namespace OS { namespace KERNEL { namespace GUI {


    Window::Window(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
        xOldPos = x;
        yOldPos = x;
        xPos = x;
        yPos = y;
        width = w;
        height = y;

    }

    Window::~Window() {

    }

    void Window::draw() {
        
        OS::KERNEL::HW_COMM::VGA* vga = OS::KERNEL::HW_COMM::VGA::getInstance();

        if(xPos > xOldPos || yPos > yOldPos) {
            //remove old window - moving to bottom right
            vga->fillRectangle(xOldPos, yOldPos, xPos-xOldPos, yPos + yOldPos, 255,255,255);
            vga->fillRectangle(xOldPos, yOldPos, yPos+yOldPos, xPos - xOldPos, 255,255,255);
        
        }

         if(xPos < xOldPos || yPos < yOldPos) {
            //remove old window - moving to bottom left

            vga->fillRectangle(xPos + height, yPos, xOldPos - xPos, yOldPos - yPos, 255,255,255);
            //vga->fillRectangle(xOldPos + , yPos, xOldPos - xPos, yOldPos - yPos, 255,255,255);
            //vga->fillRectangle(xOldPos + (xOldPos - xPos), yOldPos + (yOldPos -yPos), xOldPos - xPos, yOldPos - yPos,255,255,255);


            //int a = 4 /0;

          //XY--------w---------x + w
            //.                .
            //.                .
            //.                h    y + 
            //.                .
            //.                .
            //------------------
        
        }
        //draw new window
        vga->fillRectangle(xPos, yPos, width, height, 0, 0, 255);

        xOldPos = xPos;
        yOldPos = yPos;

    }


} } }