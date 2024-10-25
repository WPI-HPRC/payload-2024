#pragma once
#include "State.h"
#include "Debouncer.h"

//! @brief max number of milliseconds we can remain in the prelaunch (initialization) state
#define MAX_PRELAUNCH_TIME 3000
class PreLaunch : public State {
	_STATE_CLASS_IMPLS_
	public:
		PreLaunch(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV); 
	private:
		float accelReadingBuffer[10] = {0};
		uint8_t accelBuffIdx = 0;
		float avgAccelZ();
		float altitudeBuff[10] = {};
		size_t altitudeBuffIdx = 0;
		bool launched = false;
		Debouncer launchDebouncer = Debouncer(10);
	
};
