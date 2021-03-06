#include "../include/hw/vga.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    VGA* VGA::s_Instance = NULL;

    VGA::VGA() :
        miscPort(0x3C2),
        crtcIndexPort(0x3D4),
        crtcDataPort(0x3D5),
        sequencerIndexPort(0x3C4),
        sequencerDataPort(0x3C5),
        graphicsControllerIndexPort(0x3CE),
        graphicsControllerDataPort(0x3CF),
        attributeControllerIndexPort(0x3C0),
        attributeControllerReadPort(0x3C1),
        attributeControllerWritePort(0x3C0),
        attributeControllerResetPort(0x3DA) {
        
        m_VGA_Buffers = new uint8_t*[2];
        m_VGA_Buffers[0] = new uint8_t[VGA_320x200_MEM_SIZE];
        m_VGA_Active_Buffer = 0;
        initalFrameCopied = false;
        
    }

    VGA::~VGA() {

    }

    VGA* VGA::getInstance() {
            if(s_Instance == NULL) 
            s_Instance = new VGA();

        return s_Instance;
    }

    void VGA::writeregisters(uint8_t* registers) {
        //set vga mode 320x200x256
        //misc
        miscPort.write(*(registers++));

        //sequencer
        for (uint8_t i = 0; i < 5; i++) {
            sequencerIndexPort.write(i);
            sequencerDataPort.write(*(registers++));
        }

        //cathode ray tune ctrl
        crtcIndexPort.write(0x03);
        crtcIndexPort.write(crtcDataPort.read() | 0x80);
        crtcIndexPort.write(0x11);
        crtcDataPort.write(crtcDataPort.read() & ~0x80);

        registers[0x03] = registers[0x03] | 0x80;
        registers[0x11] = registers[0x11] & ~0x80;

        for (uint8_t i = 0; i < 25; i++) {
            crtcIndexPort.write(i);
            crtcDataPort.write(*(registers++));
        }

        //graphics controller
        for (uint8_t i = 0; i < 9; i++) {
            graphicsControllerIndexPort.write(i);
            graphicsControllerDataPort.write(*(registers++));
        }

        //attributes
        for (uint8_t i = 0; i < 5; i++) {

            attributeControllerResetPort.read();
            attributeControllerIndexPort.write(i);
            attributeControllerWritePort.write(*(registers++));
        }

        attributeControllerResetPort.read();
        attributeControllerIndexPort.write(0x20);

    }

    uint8_t* VGA::getFrameBufferSegment() {
        graphicsControllerIndexPort.write(0x06);
        uint8_t segmentNumber = ((graphicsControllerIndexPort.read() >> 2) & 0x03);
        switch (segmentNumber)
        {
            default:
            case 0:
                return (uint8_t*)0x00000;
            case 1:
                return (uint8_t*)0xA0000;
            case 2:
                return (uint8_t*)0xB0000;
            case 3:
                return (uint8_t*)0xB8000;
        }
    }

    uint8_t VGA::getColorIndex(RGB_Color color) {

        
        if(color.R == 0x00 && color.G == 0x00 && color.B == 0x00) return 0x00; // black
        if(color.R == 0x00 && color.G == 0x00 && color.B == 0xA8) return 0x01; // blue
        if(color.R == 0x00 && color.G == 0xA8 && color.B == 0x00) return 0x02; // green
        if(color.R == 0xA8 && color.G == 0x00 && color.B == 0x00) return 0x04; // red
        if(color.R == 0xFF && color.G == 0xFF && color.B == 0xFF) return 0x3F; // white
        

        //color = (r*6/256)*36 + (g*6/256)*6 + (b*6/256)
        //very approximate colour normalization
        uint8_t color_normalized = (color.R/256) * 36 + (color.G*6/256)*6 + (color.B*6/256);



        return color_normalized;
    }


    bool VGA::supportMode(uint32_t width, uint32_t height, uint32_t colorDepth) {
        return width == 320 && height == 200 && colorDepth == 8;
    }

    bool VGA::setMode(uint32_t width, uint32_t height, uint32_t colorDepth) {
        
        if(!supportMode(width, height, colorDepth))
        return false;
        unsigned char g_320x200x256[] =
        {
                /* MISC */
                0x63,
                /* SEQ */
                0x03, 0x01, 0x0F, 0x00, 0x0E,
                /* CRTC */
                0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
                0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
                0xFF,
                /* GC */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
                0xFF,
                /* AC */
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                0x41, 0x00, 0x0F, 0x00,	0x00
        };

        writeregisters(g_320x200x256);
        return true;
    }

   
    void VGA::putPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {

        if(x < 0 || 320 <= x || y < 0 || 200 <= y)
            return;
        
        //uint8_t* pixelAddress = getFrameBufferSegment() + 320*y + x;
        //*pixelAddress = getColorIndex(RGB_Color(r,g,b));
        
        uint8_t* bufferAddress = m_VGA_Buffers[m_VGA_Active_Buffer] + 320*y+x;
        *bufferAddress = getColorIndex(RGB_Color(r,g,b));

    }

    void VGA::putPixel(uint32_t x, uint32_t y, uint8_t color) {
        
        if(x < 0 || 320 <= x || y < 0 || 200 <= y)
                return;

            uint8_t* bufferAddress = m_VGA_Buffers[m_VGA_Active_Buffer] + 320*y+x;
            *bufferAddress = color;

    }

    void VGA::drawChar8(uint32_t x, uint32_t y, char c, uint8_t fgcolor) {
        int cx,cy;
        int mask[8]={128,64,32,16,8,4,2,1};
        unsigned char *glyph=GUI::g_8x8_font+(int)c*8;
    
        for(cy=0;cy<8;cy++){
            for(cx=0;cx<8;cx++){
                if(glyph[cy]&mask[cx]) putPixel(x+cx,y+cy-6, fgcolor);
            }
        }
    }

    void VGA::drawChar16(uint32_t x, uint32_t y, char c, int fgcolor, int bgcolor) {
        int cx,cy;
        int mask[8]={128,64,32,16,8,4,2,1};
        unsigned char *glyph=GUI::g_8x16_font+(int)c*16;
    
        for(cy=0;cy<16;cy++){
            for(cx=0;cx<8;cx++){
                if(glyph[cy]&mask[cx]) putPixel(x+cx,y+cy-12, fgcolor);
            }
        }
    }
    
    void VGA::fillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b) {
       
        for(int32_t Y = y; Y < y+h; Y++)
            for(int32_t X = x; X < x+w; X++)
                putPixel(X, Y, r);
    
    }

     void VGA::fillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color) {
       
        for(int32_t Y = y; Y < y+h; Y++)
            for(int32_t X = x; X < x+w; X++)
                putPixel(X, Y, color);
    
    }

    void fastmemcpy(void* src, void* dst, uint32_t size) {

        //64000 bytes
        if(src == dst)
            return;
    
        uint32_t roundsBytes4 = size /4;

        uint32_t* srcWORD = (uint32_t*)src;
        uint32_t* dstWORD = (uint32_t*)dst;
        
        for (size_t i = 0; i < roundsBytes4; i++)
        {

            dstWORD[i] = srcWORD[i];

        }
        

        

    }

    void VGA::swapBuffers() {
        
        //memcopy screen buffer to vga
        if(!initalFrameCopied) {
            memcpy(m_VGA_Buffers[0], m_VGA_Buffers[1], VGA_320x200_MEM_SIZE * sizeof(uint8_t));
            initalFrameCopied = true;
        }
        uint32_t* pixelAddress = (uint32_t*)getFrameBufferSegment();
        fastmemcpy(m_VGA_Buffers[m_VGA_Active_Buffer], pixelAddress, VGA_320x200_MEM_SIZE);

        if(m_VGA_Active_Buffer == 1)
            m_VGA_Active_Buffer = 0;
        else
            m_VGA_Active_Buffer = 0;
        
        

    }

}}}
