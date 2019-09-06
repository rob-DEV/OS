#include "../include/cpu/gdt.h"

struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern "C" void gdt_flush();

namespace OS { namespace KERNEL { namespace CPU {

    GDT* GDT::m_Instance = NULL;

    GDT::GDT() {
        
    }

    GDT::~GDT() {

    }
    
    GDT* GDT::getInstance() {
        if(m_Instance == NULL)
            m_Instance = new GDT();
        
        return m_Instance;
    }

    void GDT::setGDTEntry(uint32_t num, long base, long limit, unsigned char access, unsigned char gran) {
        /* Setup the descriptor base address */
        gdt[num].base_low = (base & 0xFFFF);
        gdt[num].base_middle = (base >> 16) & 0xFF;
        gdt[num].base_high = (base >> 24) & 0xFF;

        /* Setup the descriptor limits */
        gdt[num].limit_low = (limit & 0xFFFF);
        gdt[num].granularity = ((limit >> 16) & 0x0F);

        /* Finally, set up the granularity and access flags */
        gdt[num].granularity |= (gran & 0xF0);
        gdt[num].access = access;
    }

    void GDT::install() {

        /* Setup the GDT pointer and limit */
        gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
        gp.base = (uint32_t)&gdt;

        /* Our NULL descriptor */
        setGDTEntry(0, 0, 0, 0, 0);

        /* The second entry is our Code Segment. The base address
        *  is 0, the limit is 4GBytes, it uses 4KByte granularity,
        *  uses 32-bit opcodes, and is a Code Segment descriptor.
        *  Please check the table above in the tutorial in order
        *  to see exactly what each value means */
        setGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

        /* The third entry is our Data Segment. It's EXACTLY the
        *  same as our code segment, but the descriptor type in
        *  this entry's access byte says it's a Data Segment */
        setGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

        /* Flush out the old GDT and install the new changes! */
        gdt_flush();
    }

}}}