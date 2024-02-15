#pragma once
#include "State.h"
#define MAX_CONTROLLED_DESCENT_TIME 10  // need to be changed is placeholder
#define ALT_THRESHOLD_CONTROLLED 10 // need to be changed

class HoldLeft : public State {
	_STATE_CLASS_IMPLS_
	public:
		HoldLeft();
};
