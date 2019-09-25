#include "../hardware/vga.h"
#include "window.h"


namespace OS { namespace KERNEL { namespace GUI { 

struct RGB_Color{
    uint8_t R,G,B = 0;

    inline RGB_Color() : R(0), G(0), B(0) { };
    inline RGB_Color(uint8_t r, uint8_t g, uint8_t b) : R(r), G(g), B(b) { };
    inline ~RGB_Color() { }

};

class WindowManager {
    private: 
        uint8_t m_BackgroundColor = 255;
        Window* m_Windows[500];

    public:    
        WindowManager();
        ~WindowManager();

        void addWindow();
        void removeWindow();

};


}}}