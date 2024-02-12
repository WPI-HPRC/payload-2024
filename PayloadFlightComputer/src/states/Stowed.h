// #pragma once
// #include "State.h"
// #include "Sensors.h"
// #define MAX_STOWED_TIME 10000
// #define ALT_THRESHOLD_STOWED 1300

// #define MIN_LAUNCH_TIME 3000 // TODO: check with OpenRocket sim

// class Stowed : public State
// {
//     _STATE_CLASS_IMPLS_
// public:
//     Stowed(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip);

// private:
//     bool motorBurnout = false;
//     float transitionBufAcc[10] = {0};
//     int transitionBufIndAcc = 0;
// };



#pragma once
#include "State.h"
//! @brief max number of milliseconds we can remain in the prelaunch (initialization) state
#define MAX_STOWED_TIME 10000
#define ALT_THRESHOLD_STOWED 1300  // currently feet

class Stowed : public State {
	_STATE_CLASS_IMPLS_
	public:
		Stowed(struct Sensors *sensors);
};
