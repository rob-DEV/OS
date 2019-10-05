#ifndef OS_KERNEL_HW_PC_SPEAKER_H
#define OS_KERNEL_HW_PC_SPEAKER_H

#include "../com/type.h"
#include "port.h"


namespace OS { namespace KERNEL { namespace HW_COMM {

    class PcSpeaker {
    
    private:
        static PcSpeaker* m_Instance;

    public:
        PcSpeaker();
        ~PcSpeaker();

         static PcSpeaker* getInstance();

    };

}}}

#endif