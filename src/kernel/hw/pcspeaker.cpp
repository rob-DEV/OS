#include "../include/hw/pcspeaker.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    PcSpeaker* PcSpeaker::s_Instance = NULL;

    PcSpeaker::PcSpeaker() {

    }

    PcSpeaker::~PcSpeaker() {

    }

    PcSpeaker* PcSpeaker::getInstance() {
        
        if(s_Instance == NULL) 
            s_Instance = new PcSpeaker();

        return s_Instance;

    }

}}}
