#pragma once
#include "State.h"
#include "Debouncer.h"
//#define MAX_LAND_TIME 10  // need to be changed is placeholder

class LandPrep : public State {
	_STATE_CLASS_IMPLS_
	public:
		LandPrep(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator); 
	private: 
		float verticalVelocityBuffer[10] = {0};
        int bufferIndex = 0;
        float lastAltitude = 0;
        bool landed = false;
        Debouncer landedDebouncer = Debouncer(10);
};
