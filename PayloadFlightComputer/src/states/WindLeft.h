#pragma once
#include "State.h"
//#define MAX_INITIALDESCENT_TIME 10  // need to be changed is placeholder

class WindLeft : public State {
	_STATE_CLASS_IMPLS_
	public:
		WindLeft(struct Sensors *sensors, StateEstimator *stateEstimator); 
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
