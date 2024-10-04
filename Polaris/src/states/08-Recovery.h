#pragma once
#include "State.h"


class Recovery : public State {
	_STATE_CLASS_IMPLS_
	public:
		Recovery(FlashChip *flash, StateEstimator *stateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV); 
};
