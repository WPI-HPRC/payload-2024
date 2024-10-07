#pragma once
#include "State.h"
#include "Freefall.h"
//! @brief max number of milliseconds we can remain in the prelaunch (initialization) state
// #define MAX_STOWED_TIME 10000
// #define ALT_THRESHOLD_STOWED 1300  // currently feet

class Stowed : public State {
	_STATE_CLASS_IMPLS_
	public:
		Stowed(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV); 

	private:
		// for z acceleration //I need to clarify why these are here 
		float transitionBufAcc[10]; 
		uint8_t transitionBufIndAcc = 0;
		
		// for vertical velocity
		int16_t transitionBufVelVert[10];
		uint8_t transitionBufIndVelVert = 0;

		// Altitude buffer
		int16_t transitionBufAlt[10];
		uint8_t transitionBufIndAlt = 0;
		int16_t altitudePreviousAvg;
};
