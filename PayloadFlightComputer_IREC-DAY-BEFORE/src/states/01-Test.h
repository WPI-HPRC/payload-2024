#pragma once
#include "State.h"
#include "Debouncer.h"

class Test : public State
{
    _STATE_CLASS_IMPLS_
public:
    Test(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator);
    
};
