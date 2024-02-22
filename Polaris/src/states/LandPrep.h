#pragma once
#include "State.h"
//#define MAX_LAND_TIME 10  // need to be changed is placeholder

class LandPrep : public State {
	_STATE_CLASS_IMPLS_
	public:
		LandPrep(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos); 
};
