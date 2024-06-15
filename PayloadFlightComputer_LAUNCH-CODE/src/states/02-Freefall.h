#pragma once
#include "State.h"
// #define MAX_STABALIZE_TIME 10  // need to be changed is placeholder
// #define ACC_THRESHOLD_STABALIZE 10 // need to be changed

class Freefall : public State {
	_STATE_CLASS_IMPLS_
	public:
		Freefall(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator); 
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
