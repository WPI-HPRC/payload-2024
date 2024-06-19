#pragma once
#include "State.h"
#include "Debouncer.h"

class PreLaunch : public State {
	_STATE_CLASS_IMPLS_
	public:
		PreLaunch(struct Sensors *sensors, struct Servos *servos, AttitudeStateEstimator *attitudeStateEstimator);
	private:
		float accelReadingBuffer[10] = {0};
		uint8_t accelBuffIdx = 0;
		float avgAccelZ();
		float altitudeBuff[10] = {};
		size_t altitudeBuffIdx = 0;
		bool launched = false;
		Debouncer launchDebouncer = Debouncer(10);
};
