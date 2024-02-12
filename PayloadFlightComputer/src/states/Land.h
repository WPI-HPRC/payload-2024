// #pragma once
// #include "State.h"
// #include "Sensors.h"
// #define MAX_LAND_TIME 10  // need to be changed is placeholder

// class Land : public State
// {
//     _STATE_CLASS_IMPLS_
// public:
//     Land(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip);

// private:
//     boolean apogeePassed = false;
//     float transitionBufVelVert[10] = {0};
//     int transitionBufIndVelVert = 0;
//     float lastAltitude = 0;
// };



#pragma once
#include "State.h"
#define MAX_LAND_TIME 10  // need to be changed is placeholder

class Land : public State {
	_STATE_CLASS_IMPLS_
	public:
		Land(struct Sensors *sensors);
};
