#pragma once
#include "State.h"
#include "Debouncer.h"
//#define MAX_LAND_TIME 10  // need to be changed is placeholder

class LandPrep : public State {
	_STATE_CLASS_IMPLS_
	public:
		LandPrep(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee,struct Servos *servos, OpenMV *openMV); 
	private: 

		float verticalVelocityBuffer[10] = {0};
		int bufferIndex = 0;
		float lastAltitude = 0;
		bool landed = false;
		int count = 0; 
        Debouncer landedDebouncer = Debouncer(10);
};
