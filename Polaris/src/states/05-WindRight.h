#pragma once
#include "State.h"
//#define MAX_INITIALDESCENT_TIME 10  // need to be changed is placeholder

class WindRight : public State {
	_STATE_CLASS_IMPLS_
	public:
		WindRight(FlashChip *flash, AttitudeStateEstimator *attitudeStateEstimator, XbeeProSX *xbee, struct Servos *servos, OpenMV *openMV); 
};
