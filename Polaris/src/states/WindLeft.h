#pragma once
#include "State.h"
//#define MAX_INITIALDESCENT_TIME 10  // need to be changed is placeholder

class WindLeft : public State {
	_STATE_CLASS_IMPLS_
	public:
		WindLeft(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos); 
};
