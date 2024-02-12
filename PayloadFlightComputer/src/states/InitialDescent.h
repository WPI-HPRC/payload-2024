#pragma once
#include "State.h"
#define MAX_INITIALDESCENT_TIME 10  // need to be changed is placeholder

class InitialDescent : public State {
	_STATE_CLASS_IMPLS_
	public:
		InitialDescent(struct Sensors *sensors);
};
