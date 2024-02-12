// #pragma once
// #include "State.h"
// #include "Sensors.h"
// #define MAX_CONTROLLED_DESCENT_TIME 10  // need to be changed is placeholder
// #define ALT_THRESHOLD_CONTROLLED 10 // need to be changed


// class ControlledDescent : public State
// {
//     _STATE_CLASS_IMPLS_
// public:
//     ControlledDescent(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip);

// private:
//     bool motorBurnout = false;
//     float transitionBufAcc[10] = {0};
//     int transitionBufIndAcc = 0;
// };


#pragma once
#include "State.h"
#define MAX_CONTROLLED_DESCENT_TIME 10  // need to be changed is placeholder
#define ALT_THRESHOLD_CONTROLLED 10 // need to be changed

class ControlledDescent : public State {
	_STATE_CLASS_IMPLS_
	public:
		ControlledDescent(struct Sensors *sensors);
};
