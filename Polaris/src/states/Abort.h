#pragma once
#include "State.h"
#include <Controls/EKF/EKF.h>

class Abort : public State
{
    _STATE_CLASS_IMPLS_
    public:
        Abort(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV); 
};
