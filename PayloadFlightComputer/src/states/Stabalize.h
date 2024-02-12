// #pragma once
// #include "State.h"
// #include "Sensors.h"
// #define MAX_STABALIZE_TIME 10
// #define ACC_THRESHOLD_STABALIZE 10

// class Stabalize : public State
// {
//     _STATE_CLASS_IMPLS_
// public:
//     Stabalize(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip);

// private:
//     bool motorBurnout = false;
//     float transitionBufAcc[10] = {0};
//     int transitionBufIndAcc = 0;
// };

#pragma once
#include "State.h"
#define MAX_STABALIZE_TIME 10  // need to be changed is placeholder
#define ACC_THRESHOLD_STABALIZE 10 // need to be changed

class Stabalize : public State {
	_STATE_CLASS_IMPLS_
	public:
		Stabalize(struct Sensors *sensors);
};
