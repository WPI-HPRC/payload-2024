#pragma once
#include "State.h"
#include "Debouncer.h"
//! @brief max number of milliseconds we can remain in the prelaunch (initialization) state
// #define MAX_STOWED_TIME 10000
// #define ALT_THRESHOLD_STOWED 1300  // currently feet

class Stowed : public State {
	_STATE_CLASS_IMPLS_
	public:
		Stowed(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator); 

	private:
		float jerkBuffer[10] = {0};
        int bufferIndex = 0;
        float lastAcceleration = 0;
        bool released = false;
        Debouncer releasedDebouncer = Debouncer(10); //Will be quick, change if needed 
		long releaseTime = 0; 
};
		