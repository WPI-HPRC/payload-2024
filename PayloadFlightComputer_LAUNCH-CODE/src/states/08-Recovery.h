#pragma once
#include "State.h"


class Recovery : public State {
	_STATE_CLASS_IMPLS_
	public:
		Recovery(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator); 
	private: 
		
};