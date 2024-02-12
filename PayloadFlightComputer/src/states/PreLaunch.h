// #pragma once
// #include "State.h"
// #include "Sensors.h"
// #define LAUNCH_ACCEL_THRESHOLD 0 // change in future

// class PreLaunch : public State {
// 	_STATE_CLASS_IMPLS_
// 	public:
// 		PreLaunch(struct Sensors *sensors, StateEstimator *stateEstimator, FlashChip *flashChip);
// 	private:
// 		bool stateEstimatorInitialized = false;
// 		float accelReadingBuffer[10];
// 		uint8_t buffIdx = 0;
// 		float avgAccelZ();
// };


#pragma once
#include "State.h"
#include "Sensors.h"

//! @brief max number of milliseconds we can remain in the prelaunch (initialization) state
#define MAX_PRELAUNCH_TIME 3000
class PreLaunch : public State {
	_STATE_CLASS_IMPLS_
	public:
		PreLaunch(struct Sensors *sensors);
	private:
		StateEstimator * ekf;
	
};
