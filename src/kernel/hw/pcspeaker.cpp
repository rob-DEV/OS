#include "../include/hw/pcspeaker.h"

namespace OS { namespace KERNEL { namespace HW_COMM {

    PcSpeaker* PcSpeaker::m_Instance = NULL;

    PcSpeaker::PcSpeaker() {

    }

    PcSpeaker::~PcSpeaker() {

    }

    PcSpeaker* PcSpeaker::getInstance() {
        
        if(m_Instance == NULL) 
            m_Instance = new PcSpeaker();

        return m_Instance;

    }

}}}
