#pragma once
#include "State.h"
#include "Sensors.h"

//! @brief max number of milliseconds we can remain in the prelaunch (initialization) state
#define MAX_PRELAUNCH_TIME 3000
class PreLaunch : public State {
	_STATE_CLASS_IMPLS_
	public:
		PreLaunch(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, Utility::Servos *servos, OpenMV *openMV); 
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
