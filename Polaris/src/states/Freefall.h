#pragma once
#include "State.h"
// #define MAX_STABALIZE_TIME 10  // need to be changed is placeholder
// #define ACC_THRESHOLD_STABALIZE 10 // need to be changed

class Freefall : public State {
	_STATE_CLASS_IMPLS_
	public:
		Freefall(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos);  
};
